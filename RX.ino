#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>

int msg[1];
RF24 radio(9,53);
const uint64_t pipe = 0xF0F0F0F0E2LL;
String theMessage = "";

void setup(void)
{
 Serial.begin(9600);
 Serial3.begin(9600);
 delay(5000);
 radio.begin();                                
 radio.openReadingPipe(1,pipe);
 radio.startListening();
}

void loop(void)
{
 if (radio.available())
 {
  //Serial.print("RX");
  bool done = false;  
  done = radio.read(msg,1); 
  char theChar = msg[0];
  if (msg[0] != 2)
  {
   theMessage.concat(theChar);
  }
  else
  {
   //Serial.println(theMessage);
   //Serial.println(theMessage.toInt());
   if (Serial3.available())
    Serial.write(Serial3.read());
   if (Serial.available())
    Serial3.write(Serial.read());
   theMessage= ""; 
  }
 }
}
