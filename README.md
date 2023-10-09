# homesecurityproject
This project is a password activated security system. It is an Arduino project that uses one wire and I2C communication protocol for communication between the microcontroller and sensor DHT11 and LCD. It uses DHT11, PIR, flame sensor, reedswtich,photoresistor to implement the scheme connection and code development


The project titled home security system was created using the Arduino uno board consisting of a set of sensors, 
buttons, display, controls and functions necessary to manage the data coming from the sensors to actuate an output. 
The prototype includes an alarm system and LED indicators that buzz and lights up whenever the security system is violated.
Majorly, it consists of a photoresistor that turns a LED4 up whenever it is dark in the home, a flame sensor that turns on
LED3 and activates the passive buzzer whenever it detects the presence of smoke (infrared radiation). 
Two reed switches (KY-025 and KY-021) placed at the doors to detect whenever the doors are open, and
when they are open LED5 turns on and the alarm begins to sound. Furthermore, a temperature and humidity sensor (DHT11) 
that uses a one wire protocol is used to check the level of temperature and humidity, and if the temperature and 
humidity surpasses the threshold set in the code (temperature=40 and humidity=160), the alarm system and overtemperature 
and overhumidity LED2 is turned activated. Lastly, a motion sensor is included in the project that activates the alarm 
whenever an intrusion into the home occurs. Most importantly, the ALARM system can be enabled and disabled using a 
4-button password (UP, DWN, OK, PSW). The button PSW is pressed to enable the password, OK to confirm the password and 
either the UP or DOWN button is pressed in the following count: press UP or DOWN (2 times & OK, 3 times & OK, 4 times & 
OK, 1 time and OK). If the password is correct, the alarm is activated if any of the security functions is violated, 
the same password sequence can also be used to disable the alarm. When the alarm is activated, 
the buzzer turns on and vice versa. Moreso, There is also a 16 x 02 LCD display which displays the current 
temperature and humidity level so the real time measurement can be monitored. The software serial monitor was 
initialized to displays some status like the door status, 
light statuses, flame status, motion status and the current bit status of the four buttons. Version 3 is the working code of the project. Version 1 is the working code of the sensor, version 2 is the working version of the passwordcounter implemented.
