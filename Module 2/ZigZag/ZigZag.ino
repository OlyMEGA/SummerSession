#include <Servo.h> 
 
Servo myServo1;
Servo myServo2;
 
void setup() 
{ 
  Serial.begin(9600);
  Serial.println("hello");

  myServo1.attach(10);
  myServo2.attach(9);
} 
 
void loop() 
{
  forward(); 
  delay(2000);  
  turnL();
  delay(500);  
} 




void move(int l, int r)
{
  if (l < -90 || l > 90 || r < -90 || r > 90)
  {
    return;
  }
  
  myServo1.write(90+l);
  myServo2.write(180-(90+r)); // -90 = 180-90-90 = 0
}


void forward()
{
  move(90,90);
}

void back()
{
  move(-90,-90);
}

void turnL()
{
  move(90,-90);
}

void turnR()
{
  move(-90,90);
}

void stop()
{
  move(0,0); 
}
