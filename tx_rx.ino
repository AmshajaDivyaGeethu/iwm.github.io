
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>

int msg[1];

RF24 radio(9,10);

const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };
String theMessage = "";
String theMsg = "";
int st=0;
char a11;

void setup()
{
 Serial.begin(9600);
 radio.begin();
 radio.openReadingPipe(1,pipes[0]);
 radio.startListening();
 delay(500);
}

void loop()
{
 //while(st==0)
 //{
  if (radio.available())
  {
   Serial.print("RX");
   bool done = false;  
   done = radio.read(msg, 1); 
   char theChar = msg[0];
   if (msg[0] != 2)
   {
    theMessage.concat(theChar);
   }
   else 
   {
    Serial.println(theMessage.toInt());
    theMsg=theMessage;
    theMessage= ""; 
   }
  //}
  //a11=theMsg[0];
  //if(a11=='#')
  //st=1;
 }
 delay(1000);
 Serial.println("TX");
 radio.stopListening();
 delay(1000);
 radio.openWritingPipe(pipes[1]);

 int messageSize = theMsg.length();
 for (int i = -1; i < messageSize; i++) 
 {
  int charToSend[1];
  charToSend[0] = theMsg.charAt(i);
  radio.write(charToSend,1);
 }   
 msg[0] = 2; 
 radio.write(msg,1);
 delay(1000);
}
