#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>
 
int rate1;
int rate2;
int sendVal;
const int THRESHOLD = 95;

void setup(){
 
  Serial.begin(9600);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"clie1");
  
   // we use channel 90 as it is outside of WLAN bands 
  // or channels used by wireless surveillance cameras 
  Mirf.channel = 90; 
  
  Mirf.payload = sizeof(sendVal);
  Mirf.config();
}
 
void loop(){
  rate1 = analogRead(A0);
  rate2 = analogRead(A1);

  if(rate1 >= THRESHOLD || rate2 >= THRESHOLD){
    sendVal = 100;
    Mirf.setTADDR((byte *)"serv1");
    Mirf.send((byte *) &sendVal);
    while(Mirf.isSending()){
    }
  }
  else{
    sendVal = 0;
    Mirf.setTADDR((byte *)"serv1");
    Mirf.send((byte *) &sendVal);
    while(Mirf.isSending()){
    }
  }
}
