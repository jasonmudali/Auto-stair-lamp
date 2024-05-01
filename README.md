As the name suggests, this project is designed to automatically turn on staircase lights when someone passes by. There are 7 lights used in this project, and they will illuminate sequentially from bottom to top or top to bottom.
This project utilizes 2 ultrasonic sensors to detect if someone is passing by, and then whether the person passes from the top or bottom.
When triggered by someone passing by, all lights will turn on and will remain illuminated for a standard duration of 15 seconds. During this 15-second duration, if another person passes by, the duration will be extended for another 15 seconds. If no one passes by within the 15-second duration, the lights will turn off.

I use Arduino UNO as the microcontroller and Arduino IDE for this project. But, you can also use VS Code as the IDE for this project.

