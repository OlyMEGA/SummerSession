#include <Servo.h> 
 
Servo myServo1;
Servo myServo2;
 
void setup() 
{ 
  Serial.begin(9600);
  Serial.println("hello");

  myServo1.attach(9);
  myServo2.attach(10);
  
  myServo1.write(90);
  myServo2.write(90);
  
} 
 
void loop() 
{
  
} 
