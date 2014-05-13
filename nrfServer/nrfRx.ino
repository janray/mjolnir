#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>
 
int rate;
boolean ledState = false;
int buttonState = 0;
const int switchPin = 4; //connect the switch on digital pin 4
const int ledPin = 5;

void setup(){
 
  Serial.begin(9600);
  pinMode(switchPin, INPUT);
  pinMode(ledPin, OUTPUT);
  
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
  buttonState = digitalRead(switchPin);
  
  if(buttonState == LOW){
    digitalWrite(ledPin, HIGH);
    while(!Mirf.dataReady()){
    }
    Mirf.getData((byte *) &rate);
   
    Serial.println(rate);
    delay(21);
  }
  else{
    delay(100);
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
  }
}
