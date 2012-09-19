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
    throttleFactor = map(unThrottleIn, 1052, 1784, 0, 180);

    if ( abs(throttleFactor - lastThrottleFactor) > 20) {
      lastThrottleFactor = throttleFactor;
      doit = true;    
    }
  }  

  if(bUpdateFlags & THROTTLE_FLAG)
  {
    steeringBias = map(unSteeringIn, 1272, 1632, -100, 100);    

    if ( abs(steeringBias - lastSteeringBias) > 2) {
      lastSteeringBias = steeringBias;
      doit = true;    
    }
  }


  if(doit)
  {
      int leftSpeed, rightSpeed;
      if (steeringBias > 10) {
         rightSpeed = (float)throttleFactor * ((float)steeringBias / 100.0f);
         leftSpeed = (throttleFactor < 0) ? -(-rightSpeed) : -(180-rightSpeed);
      } else if (steeringBias < 4) {
         leftSpeed = -( (float)throttleFactor * ((float)steeringBias / 100.0f) );
         rightSpeed = (throttleFactor < 0) ? -(0-leftSpeed) : -(180-leftSpeed);
      } else {
         leftSpeed = throttleFactor;
         rightSpeed = throttleFactor; 
      }

      leftServo.write(leftSpeed);
      rightServo.write(rightSpeed);
  }
}
