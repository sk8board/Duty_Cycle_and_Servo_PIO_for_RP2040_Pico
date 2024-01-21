// Servo and Duty Cycle PIO use without a Servo library

#include <Arduino.h> 
#include "hardware/pwm.h"

#define UART_SELECT Serial2
#define CRSF_TX 21  // (UART1 == Serial2)
#define CRSF_RX 22  // (UART1 == Serial2)

#define Number_of_Channel_Outputs 16  // NOTE: PWM Channels must be set in Slice Pairs
int Servo_Value;
int j;  // for loop incrementor
int i;  // for loop incrementor
uint slice_num[Number_of_Channel_Outputs]; //

// Failsafe values, 1000 to 2000
uint16_t Failsafe_Channel_Value [Number_of_Channel_Outputs] = {
    1500,    // Channel 1 Failsafe value           
    1500,    // Channel 2 Failsafe value                 
    1500,    // Channel 3 Failsafe value                
    1500,    // Channel 4 Failsafe value                 
    1500,    // Channel 5 Failsafe value                 
    1500,    // Channel 6 Failsafe value                 
    1500,    // Channel 7 Failsafe value                 
    1500,    // Channel 8 Failsafe value                 
    1500,    // Channel 9 Failsafe value                  
    1500,    // Channel 10 Failsafe value                 
    1500,    // Channel 11 Failsafe value                
    1500,    // Channel 12 Failsafe value
    1500,    // Channel 13 Failsafe value                  
    1500,    // Channel 14 Failsafe value                 
    1500,    // Channel 15 Failsafe value                
    1500     // Channel 16 Failsafe value    
};            


// NOTE: PWM Channels must be set in Slice Pairs
// Please reference the website below to understand Slice Pairs
// https://www.codrey.com/raspberry-pi/raspberry-pi-pico-pwm-primer/

uint16_t Channel_GPIO_Mapping[Number_of_Channel_Outputs] ={
    0, //GPIO 0, ELRS Channel 1
    1, //GPIO 1, ELRS Channel 2
    2, //GPIO 2, ELRS Channel 3
    3, //GPIO 3, ELRS Channel 4
    4, //GPIO 4, ELRS Channel 5
    5, //GPIO 5, ELRS Channel 6
    6, //GPIO 6, ELRS Channel 7
    7, //GPIO 7, ELRS Channel 8
    8, //GPIO 8, ELRS Channel 9
    9, //GPIO 9, ELRS Channel 10
    10, //GPIO 10, ELRS Channel 11
    11, //GPIO 11, ELRS Channel 12
    12, //GPIO 12, ELRS Channel 13
    13, //GPIO 13, ELRS Channel 14
    14, //GPIO 14, ELRS Channel 15
    15  //GPIO 15, ELRS Channel 16
};



void setup(){

    // initialize 'config' with the default PMW config
    pwm_config config = pwm_get_default_config();

    // Modify PWM config timing,
    pwm_config_set_clkdiv(&config, 124.f);   // set PWM clock to 1/125 of CPU clock speed,  (125,000,000 / 125 = 1,000,000hz) May need to adjust when using earlephilhower base code
    pwm_config_set_wrap(&config, 20000);     // set PWM period to 20,000 cycles of PWM clock,  (1,000,000 / 20,000 = 50hz)

    for(i=0; i<Number_of_Channel_Outputs; ++i){
        // Set GPIO pins to be allocated to the PWM by using the Channel_GPIO_Mapping array
        gpio_set_function(Channel_GPIO_Mapping[i], GPIO_FUNC_PWM);
        
        // Find out which PWM slice is connected to GPIO and store the slice number in an array that is aligned with Channel_GPIO_Mapping array
        slice_num[i] = {pwm_gpio_to_slice_num(Channel_GPIO_Mapping[i])};

        // initialize the slice withOUT earlephilhower core
        pwm_init(slice_num[i], Channel_GPIO_Mapping[i], &config, true);

        // initialize the slice WITH earlephilhower core
        //pwm_init(slice_num[i], &config, true);


        // Set initial PWM of channel
        pwm_set_chan_level(slice_num[i], Channel_GPIO_Mapping[i], Failsafe_Channel_Value[i]);

        // Set PWM running by slice
        if(i % 2 == 0){
            pwm_set_enabled(slice_num[i], true);
        }
    }
}

void loop(){
    for(j=0; j<10; ++j){
        Servo_Value = 1000 + (j * 100);
        delay(1000);
        for(i=0; i<Number_of_Channel_Outputs; ++i){
                pwm_set_gpio_level(Channel_GPIO_Mapping[i], Servo_Value); // update PWM output value
        }
    }
}