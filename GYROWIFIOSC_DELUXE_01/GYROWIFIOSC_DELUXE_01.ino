
#include <WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>    
//#include "LSM6DS3.h"
#include "Wire.h"
#include <LSM6.h>

LSM6 imu;

// WiFi network name and password:
const char * networkName = "YOUR NETWORK";
const char * networkPswd = "YOUR PASS";

const char * udpAddress = "192.168.1.131";
const int udpPort = 6666;

//Are we currently connected?
boolean connected = false;

//The udp library class
WiFiUDP udp;


//Create a instance of class LSM6DS3
//LSM6DS3 myIMU( I2C_MODE, 0x6A );  //I2C device address 0x6A

void setup(){
  Serial.begin(115200);
  Wire.begin();
  if (!imu.init())
  {
    Serial.println("Failed to detect and initialize IMU!");
    while (1);
  }
  imu.enableDefault();

  //Serial.println(imu.a.x);
  //Serial.println(imu.a.y);
  //Serial.println(imu.a.z);
  
  //Connect to the WiFi network
  connectToWiFi(networkName, networkPswd);
}

void loop(){
  imu.read();
  //only send data when connected
  if(connected){
    int sensorValue = analogRead(36);
    
    OSCMessage msg("/");
    msg.add(imu.a.x);
    msg.add(imu.a.y);
    msg.add(imu.a.z);
    msg.add(imu.g.x);
    msg.add(imu.g.y);
    msg.add(imu.a.z);
    //msg.add(sensorValue);

    
    //msg.add(imu.a.x);
    //msg.add(imu.a.y);
    //msg.add(imu.a.z);
    
    udp.beginPacket(udpAddress, udpPort);
    msg.send(udp);
    udp.endPacket();
    msg.empty();
  }
  //Wait
  delay(2);
}

void connectToWiFi(const char * ssid, const char * pwd){
  Serial.println("Connecting to WiFi network: " + String(ssid));

  // delete old config
  WiFi.disconnect(true);
  //register event handler
  WiFi.onEvent(WiFiEvent);

  //Initiate connection
  WiFi.begin(ssid, pwd);
  Serial.println("Waiting for WIFI connection...");
}

//wifi event handler
void WiFiEvent(WiFiEvent_t event){
  switch(event) {
  case SYSTEM_EVENT_STA_GOT_IP:
  //When connected set
  Serial.print("WiFi connected! IP address: ");
  Serial.println(WiFi.localIP());
  //initializes the UDP state
  //This initializes the transfer buffer
  udp.begin(WiFi.localIP(),udpPort);
  connected = true;
  break;
  case SYSTEM_EVENT_STA_DISCONNECTED:
  Serial.println("WiFi lost connection");
  connected = false;
  break;
  }
}
