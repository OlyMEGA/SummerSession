#include <Servo.h> 
 
Servo myServo1;  // create servo object to control a servo 
Servo myServo2;  // create servo object to control a servo 
 
void setup() 
{ 
  Serial.begin(9600);
  Serial.println("hello");

  myServo1.attach(9);  // attaches the servo on pin 9 to the servo object 
  myServo2.attach(11);  // attaches the servo on pin 9 to the servo object 

  initWithLights();
} 
 
void loop() 
{ 
  myServo1.write(0);                  // sets the servo position according to the scaled value 
  myServo2.write(180);                  // sets the servo position according to the scaled value 
  delay(5000);                           // waits for the servo to get there 

  myServo1.write(90);                  // sets the servo position according to the scaled value 
  myServo2.write(90);                  // sets the servo position according to the scaled value 
  delay(1000);                           // waits for the servo to get there 

  myServo1.write(180);                  // sets the servo position according to the scaled value 
  myServo2.write(0);                  // sets the servo position according to the scaled value 
  delay(5000);                           // waits for the servo to get there 
} 

void initWithLights()
{
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);

  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);

  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);
}
