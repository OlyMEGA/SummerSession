int throttleFactor;
int steeringBias;

int lastThrottleFactor;
int lastSteeringBias;

void loopMotor()
{
  boolean doit = false;
  
  if(bUpdateFlags & THROTTLE_FLAG)
  {
    throttleFactor = map(unThrottleIn, 1052, 1784, 255, -255);

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
         leftSpeed = (throttleFactor < 0) ? -(-255-rightSpeed) : -(255-rightSpeed);
      } else if (steeringBias < 4) {
         leftSpeed = -( (float)throttleFactor * ((float)steeringBias / 100.0f) );
         rightSpeed = (throttleFactor < 0) ? -(-255-leftSpeed) : -(255-leftSpeed);
      } else {
         leftSpeed = throttleFactor;
         rightSpeed = throttleFactor; 
      }

      setSpeed(leftSpeed, rightSpeed);    
  }
}



// Set Motor Speed (-255 to 255)
void setSpeed(int leftSpeed, int rightSpeed)
{
  analogWrite(RIGHT_MOTOR_PIN, abs(rightSpeed));
  analogWrite(LEFT_MOTOR_PIN, abs(leftSpeed));

  if      (rightSpeed > 0) digitalWrite(RIGHT_MOTOR_DIR_PIN, HIGH);
  else if (rightSpeed < 0) digitalWrite(RIGHT_MOTOR_DIR_PIN, LOW);
  else                     digitalWrite(RIGHT_MOTOR_PIN, LOW);    

  if      (leftSpeed > 0) digitalWrite(LEFT_MOTOR_DIR_PIN, LOW);
  else if (leftSpeed < 0) digitalWrite(LEFT_MOTOR_DIR_PIN, HIGH);
  else                    digitalWrite(LEFT_MOTOR_PIN, LOW);        
}

