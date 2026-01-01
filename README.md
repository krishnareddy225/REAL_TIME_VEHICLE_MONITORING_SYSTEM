# CAN Based Real-Time Vehicle Monitoring System 
This project implements a CAN-based system to monitor vehicle parameters in real-time. 
It uses LPC21xx microcontroller, LCD display, keypad input, ADC sensors, and UART communication to log data to a PC. 
 
## Features 
- Temperature monitoring using LM35 sensor 
- Keypad-based time editing mode using external interrupt 
- Real-time logging to PC via UART 
- Fault alerts with LED/Buzzer 
 
## Files / Modules 
- adc.c / adc.h / adc_defines.h 
- can.c / can.h / can_defines.h 
- lcd.c / lcd.h / lcd_defines.h 
- interrupt.c / interrupt.h / interrupt_defines.h 
- main_node.c (main program) 
 
## How to Run 
1. Open the project in Keil uVision. 
2. Compile the code for LPC21xx microcontroller. 
3. Flash the HEX file to the microcontroller. 
4. Connect sensors (LM35), LCD, keypad, and UART to the PC. 
5. Observe temperature readings and fault alerts. 
 
## Notes 
- Only source code files are included in GitHub. Compiled files are ignored. 
