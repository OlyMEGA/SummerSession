void setupController()
{
  // using the PinChangeInt library, attach the interrupts used to read the channels
//  PCintPort::attachInterrupt(THROTTLE_IN_PIN, calcThrottle,CHANGE); 
//  PCintPort::attachInterrupt(STEERING_IN_PIN, calcSteering,CHANGE); 



//// Leonardo settings - Channel3=>D2, Channel1=>D3
//  attachInterrupt(0, calcSteering, CHANGE); 
//  attachInterrupt(1, calcThrottle, CHANGE); 

// Arduino settings - Channel3=>D2, Channel1=>D3.
  attachInterrupt(0, calcThrottle, CHANGE); 
  attachInterrupt(1, calcSteering, CHANGE); 

//  PCintPort::attachInterrupt(AUX_IN_PIN, calcAux,CHANGE); 
}

void loopController()
{
  // check shared update flags to see if any channels have a new signal
  if(bUpdateFlagsShared)
  {
    noInterrupts(); // turn interrupts off quickly while we take local copies of the shared variables

    // take a local copy of which channels were updated in case we need to use this in the rest of loop
    bUpdateFlags = bUpdateFlagsShared;
    
    // In the current code, the shared values are always populated so we could copy them
    // without testing the flags however in the future this could change, so lets
    // only copy when the flags tell us we can.    
    if(bUpdateFlags & THROTTLE_FLAG) { 
        unThrottleIn = unThrottleInShared; 
    }
    
    if(bUpdateFlags & STEERING_FLAG) { 
      unSteeringIn = unSteeringInShared; 
    }
    
    if(bUpdateFlags & AUX_FLAG) { 
      unAuxIn = unAuxInShared; 
    }  
     
    // clear shared copy of updated flags as we have already taken the updates
    // we still have a local copy if we need to use it in bUpdateFlags
      bUpdateFlagsShared = 0;

    // as soon as interrupts are back on, we can no longer use the shared copies, the interrupt
    // service routines own these and could update them at any time. During the update, the 
    // shared copies may contain junk. Luckily we have our local copies to work with :-)

    interrupts(); // we have local copies of the inputs, so now we can turn interrupts back on
    
    Serial.print(" unthrottle: ");
    Serial.print(unThrottleIn);      
    Serial.print(" | unsteering: ");
    Serial.print(unSteeringIn);
    Serial.println("");

  }
  delay(1);
}

// simple interrupt service routine
void calcThrottle()
{
  // if the pin is high, its a rising edge of the signal pulse, so lets record its value
  if(digitalRead(THROTTLE_IN_PIN) == HIGH) { 
    ulThrottleStart = micros();
  } else {
    // else it must be a falling edge, so lets get the time and subtract the time of the rising edge
    // this gives use the time between the rising and falling edges i.e. the pulse duration.
    unThrottleInShared = (uint16_t)(micros() - ulThrottleStart);
    // use set the throttle flag to indicate that a new throttle signal has been received
    bUpdateFlagsShared |= THROTTLE_FLAG;
  }
}

void calcSteering()
{
  if(digitalRead(STEERING_IN_PIN) == HIGH) { 
    ulSteeringStart = micros();
  } else {
    unSteeringInShared = (uint16_t)(micros() - ulSteeringStart);
    bUpdateFlagsShared |= STEERING_FLAG;
  }
}

void calcAux()
{
  if(digitalRead(AUX_IN_PIN) == HIGH) { 
    ulAuxStart = micros();
  } else {
    unAuxInShared = (uint16_t)(micros() - ulAuxStart);
    bUpdateFlagsShared |= AUX_FLAG;
  }
}


