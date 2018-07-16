

#include "RAK811.h"
#include <CayenneLPP.h>
#define WORK_MODE LoRaWAN   //  LoRaWAN or LoRaP2P
#define JOIN_MODE OTAA    //  OTAA or ABP
String DevEui = "3530353064375B16";
String AppEui = "70B3D57ED000D398";
String AppKey = "28672DED58AE65387A24F18C54044F72";
#define ATSerial Serial3
#define DebugSerial Serial
float temp=0;
int resetPin = A8;


RAK811 RAKLoRa(ATSerial);
CayenneLPP lpp(51);

void reset(){
  DebugSerial.println("conexion no exitosa, reintentando");
  digitalWrite(resetPin, LOW);
  }

void setup() {
 DebugSerial.begin(115200);
 while(DebugSerial.read()>= 0) {}
 while(!DebugSerial);
 DebugSerial.println("StartUP");
 ATSerial.begin(115200);
 pinMode(resetPin, OUTPUT);
 digitalWrite(resetPin,HIGH);
  DebugSerial.println(RAKLoRa.rk_getVersion());
 delay(600);
 DebugSerial.println(RAKLoRa.rk_getBand());
 delay(600);
 if(RAKLoRa.rk_setWorkingMode(WORK_MODE)){
  delay(4000);
  DebugSerial.println("you set Working mode is OK!");
  if (RAKLoRa.rk_initOTAA(DevEui,AppEui,AppKey)){
    delay(4000);
      DebugSerial.println("you init OTAA parameter is OK!");
      DebugSerial.println(RAKLoRa.sendRawCommand("at+join=otaa\r\n"));
      DebugSerial.println("you join Network is OK!");
     }
 }
 
 lpp.addTemperature(1, 24.5);
 RAKLoRa.rk_sendData(1,1,lpp.getBuffer());
 }
 


void loop() {
 /*lpp.addTemperature(1, temp);
 temp+=0.5;
 lpp.addTemperature(1, 24.5);
 RAKLoRa.rk_sendData(1,1,lpp.getBuffer());*/
 DebugSerial.println(RAKLoRa.rk_recvData());
 
 //delay(30000);
}



