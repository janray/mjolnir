#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>
 
int rate;
const int soundPin = 3;

void setup(){
 
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(soundPin, OUTPUT);
  digitalWrite(soundPin, HIGH);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"serv1");
  
  // we use channel 90 as it is outside of WLAN bands 
  // or channels used by wireless surveillance cameras 
  Mirf.channel = 90;
  
  Mirf.payload = sizeof(rate);
  Mirf.config();
}
 
void loop(){
    while(!Mirf.dataReady()){
    }
    Mirf.getData((byte *) &rate);
   
    Serial.println(rate); 
    if(rate == 100){
      digitalWrite(soundPin, LOW);
      delay(15);
      digitalWrite(soundPin, HIGH);
    }
    delay(15);
}
