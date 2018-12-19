# Gyroscope to OSC Data

Use the NodeMCU ESP32 prototyping Board to read a LSM6 6-Axis Gyroscope and send data wireless via OSC to another device , in this case Touchdesigner099 on a Windows PC.

## Getting Started


01 -  Go to Arduino IDE preferences and copy this " https://dl.espressif.com/dl/package_esp32_index.json " to additional boards URLs.

![Prefs](https://github.com/circat/GYRO-to-OSC-DATA/blob/master/img/arduinp_prefs.PNG)

02 -  Install Node MCU Drivers : https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers

03 - select NODE32s from Boards :

![Prefs](https://github.com/circat/GYRO-to-OSC-DATA/blob/master/img/Arduino_nodeMCU.PNG)

04 - Download ARDOSC Arduino Library and extract to your Arduino Librarys Folder.
https://www.arduinolibraries.info/libraries/ard-osc

About OSC : 
http://opensoundcontrol.org/spec-1_0

05 - in Arduino set Wifi settings to your network settings and host Computer IP and upload to NodeMCU :

// WiFi network name and password:
const char * networkName = "your Network";
const char * networkPswd = "Your Network Pass";

const char * udpAddress = "xxx.xxx.x.xxx";
const int udpPort = 6666;

05 - connect gyroscope to 3.3V + GND and SCL to NodeMCU pin D22 and SDA to pin D21
![Prefs](https://github.com/circat/GYRO-to-OSC-DATA/blob/master/img/pinout.PNG)




