# ENVIROCLOCK-MULTIFUNCTION-ALARM-CLOCK-WITH-ROOM-TEMPERATURE-DISPLAY
EnviroClock An embedded c project on LPC2148 featuring real time clock display,date/day editing through keypad,interrupts,alarm setting with buzzer control,and room temperature monitoring using LM35 sensor
HardWare Used:
LPC2148 Microcontroller,
16x2 LCD Display,
Lm35 Temperature Sensor,
4x4 Keypad,
Buzzer,
Switches,
Features:
Real-Time Clock Display
shows hour,minute,second,day,date,month,year on a16x2 lcd.
Temperature Display:
Uses LM35 sensor to measure and display room temperature
Interrupt:
external interrupt for editing and setting alarm
Menu Driven using keypad
1:RTC EDIT
2:SET ALARM
3:EXIT
Alarm Functinality:
user enter alarm hour and minute,compare with RTC registers ifequal Buzzer ON and alarm Symbol ON on LCD
Alarm runs for 1 minute or can be stopped manually with a switch
