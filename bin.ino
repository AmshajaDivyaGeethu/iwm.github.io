#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <dht.h>

#define dht_apin 7 // sensor is connected to 7

#define trigPin1 5//Fill-level sensor trigger pin
#define echoPin1 6//Fill-level sensor echo pin

#define trigPin2 3//Proximity sensor trigger pin
#define echoPin2 4//Proximity sensor echo pin

dht DHT;
RF24 radio(9, 53);

int msg[1];
int messageSize;
int messageSize1;
int messageSize2;
const uint64_t pipe = 0xF0F0F0F0E1LL;
int charToSend[1];
int charToSend1[1];
int charToSend2[1];

int bo = 0;

Servo myservo;  // create servo object to control a servo

int pos = 0;    // variable to store the servo position
long distance1; // Duration used to calculate distance
long distance2;

void setup()
{
  Serial.begin(9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  myservo.attach(2);  // attaches the servo on pin 9 to the servo object
  delay(1000);
  radio.begin();// NRF
  radio.openWritingPipe(pipe);
}

void loop()
{
 String s1 = "M";
 DHT.read11(dht_apin);
 int humidity = DHT.humidity;
 int temperature = DHT.temperature;
 String s2 = "H";
 String s3 = "T";
 String hum = s2 + String(humidity);
 String temp = s3 + String(temperature);
 messageSize = hum.length();
 messageSize1 = temp.length();

 Serial.print(s2);
 Serial.println(humidity);
 Serial.print(s3);
 Serial.println(temperature); 
 //delay(5000);

 for (int i = -1; i < messageSize; i++)
 {
  charToSend[0] = hum.charAt(i);
  radio.write(charToSend, 1);
 }
 msg[0] = 2;
 radio.write(msg, 1);
 //delay(1000);

 for (int i = -1; i < messageSize1; i++)
 {
  charToSend1[0] = temp.charAt(i);
  radio.write(charToSend1, 1);
 }
 msg[0] = 2;
 radio.write(msg, 1);
 //delay(1000);
 
 long a2 = dist2();//returns the value of proximity sensor
 long a1 = dist1();//returns the value of fill-level sensor
 //Opens the lid
 if(a2<15 && bo==0 && a1>10)
 {
  openb();
  bo=1;
 }
 //Closes the lid
 if(a2>15 && bo==1)
 {
  closeb();
  bo=0;
 }
 
  //long val = map(a2,0,1023,0,180);
  String s4 = "F";
  String dist = s2 + String(a1);
  messageSize2 = dist.length();
  Serial.print(s4);
  Serial.println(a1);
  //Serial.println(a2);
  //delay(2000);

 for (int i = -1; i < messageSize2; i++)
 {
  charToSend2[0] = dist.charAt(i);
  radio.write(charToSend2, 1);
 }
 msg[0] = 2;
 radio.write(msg, 1);
 delay(1000);
}

void closeb()
{
 for (pos = 60; pos < 120; pos++)
  {
   delay(100);
   myservo.write(pos);
  }
}

void openb()
{
  for (pos = 120; pos > 60; pos--)
  {
   myservo.write(pos);
   delay(100);
  }
}

long dist1()
{
 digitalWrite(trigPin1, LOW);
 delayMicroseconds(2);

 digitalWrite(trigPin1, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin1, LOW);

 long distance1 = pulseIn(echoPin1, HIGH);
 //distance = distance/58;
 distance1 = distance1*0.034/2;
 return(distance1);
}

long dist2()
{
 digitalWrite(trigPin2, LOW);
 delayMicroseconds(2);

 digitalWrite(trigPin2, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin2, LOW);

 long distance2 = pulseIn(echoPin2, HIGH);
 //distance = distance/58;
 distance2 = distance2*0.034/2;
 return(distance2);
}
