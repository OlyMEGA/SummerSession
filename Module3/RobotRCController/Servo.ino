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
//  if(bUpdateFlags & AUX_FLAG) {
//    if(servoAux.readMicroseconds() != unAuxIn) {
//      servoAux.writeMicroseconds(unAuxIn);
//    }
//  }
}

