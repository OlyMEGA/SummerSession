#include <Servo.h> 
 
Servo myServo1;
Servo myServo2;
 
void setup() 
{ 
  Serial.begin(9600);
  Serial.println("hello");

  myServo1.attach(9);
  myServo2.attach(10);
} 
 
void loop() 
{
  myServo1.write(180);
  myServo2.write(180);
}
