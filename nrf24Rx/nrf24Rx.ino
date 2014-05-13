#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>
 
int val;
int ledPin = 13;
int statePin = LOW;
int THRESHOLD = 95;

void setup(){
 
  Serial.begin(9600);
 
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"serv1");
  Mirf.payload = sizeof(val);
  Mirf.config();
}
 
void loop(){
 
  while(!Mirf.dataReady()){
  }
  Mirf.getData((byte *) &val);
  
  if(val >= THRESHOLD){
    statePin = !statePin;
    digitalWrite(ledPin, statePin);
    Serial.print("Knock!");
    Serial.print("  ");
  }
  Serial.println(val);
  delay(100);
}
