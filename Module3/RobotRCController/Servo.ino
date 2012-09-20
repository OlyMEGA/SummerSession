#import <Servo.h>

Servo leftServo;
Servo rightServo;

void setupServo()
{
  leftServo.attach(leftServoPin);
  rightServo.attach(rightServoPin);
  
}

void loopServo_old()
{
  if(bUpdateFlags & THROTTLE_FLAG) {
    if(leftServo.readMicroseconds() != unThrottleIn) { 
      leftServo.writeMicroseconds(unThrottleIn); 
    }
  }
  if(bUpdateFlags & STEERING_FLAG) { 
    if(rightServo.readMicroseconds() != unSteeringIn) {
      rightServo.writeMicroseconds(unSteeringIn);
    }
  }
}


void loopServo()
{
  boolean doit = false;
  
  if(bUpdateFlags & THROTTLE_FLAG)
  {
    throttleFactor = map(unThrottleIn, 1052, 1784, -255, 255);
    if (throttleFactor > 255) throttleFactor = 255;
    if (throttleFactor < -255) throttleFactor = -255;

//    if ( abs(throttleFactor - lastThrottleFactor) > 50) {
      lastThrottleFactor = throttleFactor;
      doit = true;    
//    }
  }  

  if(bUpdateFlags & THROTTLE_FLAG)
  {
    steeringBias = map(unSteeringIn, 1272, 1632, -100, 100);    

//    if ( abs(steeringBias - lastSteeringBias) > 2) {
      lastSteeringBias = steeringBias;
      doit = true;    
//    }
  }
//
//PLUG IN TEH ROBOTZ!!!!!
//Hello there...
//would you like to play a game?
//
//how about global thermonuclear strip chess
//

  if(doit)
  {
      int leftSpeed, rightSpeed;
      if (steeringBias > 15) {
         rightSpeed = (float)throttleFactor * ((float)steeringBias / 100.0f);
         leftSpeed = (throttleFactor < 0) ? -(255-rightSpeed) : -(255-rightSpeed);
      } else if (steeringBias < 5) {
         leftSpeed = -( (float)throttleFactor * ((float)steeringBias / 100.0f) );
         rightSpeed = (throttleFactor < 0) ? -(255-leftSpeed) : -(255-leftSpeed);
      } else {
         leftSpeed = throttleFactor;
         rightSpeed = throttleFactor; 
      }

      rightSpeed = map(rightSpeed, -255, 255, 0, 180), 0, 180;
      leftSpeed = map(leftSpeed, -255, 255, 0, 180), 0, 180;
      
      if (rightSpeed < 0) rightSpeed = 0;
      if (rightSpeed > 180) rightSpeed = 180;
      if (rightSpeed >= 85 && rightSpeed <= 95) rightSpeed = 90;
      
      if (leftSpeed < 0) leftSpeed = 0;
      if (leftSpeed > 180) leftSpeed = 180;
      if (leftSpeed >= 85 && leftSpeed <= 95) leftSpeed = 90;
      
      
      leftServo.write(leftSpeed);
      rightServo.write(rightSpeed);
      
      
      Serial.print(" unthrottle: ");
      Serial.print(unThrottleIn);
      
      Serial.print("unsteering: ");
      Serial.print(unSteeringIn);
      
      
      Serial.print(" throttle: ");
      Serial.print(throttleFactor);
      
      Serial.print(" steering: ");
      Serial.print(steeringBias);
      
      Serial.print(" leftSpeed: ");
      Serial.print(leftSpeed);
      
      Serial.print(" right: ");
      Serial.println(rightSpeed);
      
      
  }
}
