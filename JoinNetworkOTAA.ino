

#include "RAK811.h"
#define WORK_MODE LoRaWAN   //  LoRaWAN or LoRaP2P
#define JOIN_MODE OTAA    //  OTAA or ABP
#if JOIN_MODE == OTAA
String DevEui = "3530353064375B16";
String AppEui = "70B3D57ED000D398";
String AppKey = "28672DED58AE65387A24F18C54044F72";
#else JOIN_MODE == ABP
String NwkSKey = "3432567afde4525e7890cfea234a5821";
String AppSKey = "a48adfc393a0de458319236537a11d90";
String DevAddr = "00112233";
#endif
/*#define TXpin 11   // Set the virtual serial port pins
#define RXpin 10*/
#define ATSerial Serial3
#define DebugSerial Serial
//SoftwareSerial DebugSerial(RXpin,TXpin);    // Declare a virtual serial port
char* buffer = "72616B776972656C657373";

RAK811 RAKLoRa(ATSerial);



void setup() {
 DebugSerial.begin(115200);
 while(DebugSerial.read()>= 0) {}
 while(!DebugSerial);
 DebugSerial.println("StartUP");

 ATSerial.begin(115200);

}

void loop() {
 
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
  /*if (RAKLoRa.rk_joinLoRaNetwork(JOIN_MODE)){
           DebugSerial.println("you join Network is OK!");
           ATSerial.setTimeout(8000);
           String ver = ATSerial.readStringUntil('\n');
           DebugSerial.println(ver);
           ATSerial.setTimeout(2000);
           if (ver == STATUS_JOINED_SUCCESS){
            while (RAKLoRa.rk_sendData(1,1,buffer)){
              DebugSerial.println(RAKLoRa.rk_recvData());
            }
           }
        }*/
     }
 }
 delay(5000);
}


