#import <Servo.h>

Servo leftServo;
Servo rightServo;

void setupServo()
{
  leftServo.attach(leftServoPin);
  rightServo.attach(rightServoPin); 
}

void loopServo()
{
  boolean newDataDetected = false;
  
  
  if(bUpdateFlags & THROTTLE_FLAG)
  {
    newDataDetected = true;    

    throttleFactor = map(unThrottleIn, 1052, 1784, -255, 255);
    if (throttleFactor > 255) throttleFactor = 255;
    if (throttleFactor < -255) throttleFactor = -255;

    lastThrottleFactor = throttleFactor;
  }  

  if(bUpdateFlags & THROTTLE_FLAG)
  {
    newDataDetected = true;    

    steeringBias = map(unSteeringIn, 1272, 1632, -100, 100);    
//    if (steeringBias > -100) steeringBias = 100;
//    if (steeringBias < -100) steeringBias = -100;    
    
    lastSteeringBias = steeringBias;
  }
  
  
  if(newDataDetected)
  {
      int leftSpeed, rightSpeed;

      if (steeringBias > 15) {
         rightSpeed = (float)throttleFactor * ((float)steeringBias / 100.0f);
         leftSpeed = (throttleFactor < 0) ? (255-rightSpeed) : (255-rightSpeed);
      } else if (steeringBias < 5) {
         leftSpeed = -( (float)throttleFactor * ((float)steeringBias / 100.0f) );
         rightSpeed = (throttleFactor < 0) ? (255-leftSpeed) : (255-leftSpeed);
      } else {
         leftSpeed = throttleFactor;
         rightSpeed = throttleFactor; 
      }

      rightSpeed = map(rightSpeed, -255, 255, 180, 0);
      leftSpeed = map(leftSpeed, -255, 255, 0, 180);
      
      if (rightSpeed < 0) rightSpeed = 0;
      if (rightSpeed > 180) rightSpeed = 180;
      if (rightSpeed >= 85 && rightSpeed <= 95) rightSpeed = 90;
      
      if (leftSpeed < 0) leftSpeed = 0;
      if (leftSpeed > 180) leftSpeed = 180;
      if (leftSpeed >= 85 && leftSpeed <= 95) leftSpeed = 90;
      
      leftServo.write(leftSpeed);
      rightServo.write(rightSpeed);
          
//      Serial.print(" | throttle: ");
//      Serial.print(throttleFactor);
//      Serial.print(" | steering: ");
//      Serial.print(steeringBias);
//      Serial.print(" | leftSpeed: ");
//      Serial.print(leftSpeed);
//      Serial.print(" | right: ");
//      Serial.println(rightSpeed);
  }
}
