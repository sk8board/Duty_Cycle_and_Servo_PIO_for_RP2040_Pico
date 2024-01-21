[Duty_Cycle_and_Servo_PIO_for_RP2040_Pico](src/main.cpp) demonstrates how to use the [Raspberry Pi Pico C-SDK](https://www.raspberrypi.com/documentation/pico-sdk/hardware.html#hardware_pwm) for Duty Cycle and Servo function (PWM). This work uses standard PIO functions without the custom PIO assembly language (pioasm) that many custom servo libraries typically implement.

This demonstration will work with or without [earlephilhower's arduino-pico](https://github.com/earlephilhower/arduino-pico) base code as well as the standard [Raspberry Pi pico-sdk](https://github.com/raspberrypi/pico-sdk).

NOTE: This is experimental software and there is no guarantee of stability or reliability. USE AT YOUR OWN RISK.