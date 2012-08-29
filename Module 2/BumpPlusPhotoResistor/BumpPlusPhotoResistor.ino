// Use servo library
#include <Servo.h> 
 
// Create variables to hold the servo connections
Servo servoL;
Servo servoR;

// YOU NEED TO UNCOMMENT ONE OF THESE LINES FOR THE SKETCH TO WORK
//int switchPin = 2; // Uncomment if using Arduino Uno, Duemilanove, or Diecemila board
//int switchPin = 3; // Uncomment if using LeOlympia or other Leonardo-based board

// Keep track of if we are in a "bumped" state
bool isBumped = true;

// Photoresistor
int photoPin = A0;
int photoThreshold = 800;

void setup() 
{ 
  // Initialize our inputs
  pinMode(switchPin, INPUT);
  pinMode(photoPin, INPUT);

  // Init serial and print startup message
  Serial.begin(9600);
  Serial.println("hello");

  // Connect to Servos on pins 9 and 10
  servoL.attach(9);
  servoR.attach(10);

  // When the button on interrupt 0 (pin 2) is pressed, run the bumpInterrupt function
  // (voltage goes low because it's normally pulled-up to 5v)
  // NOTE: DO NOT UNCOMMENT THE FOLLOWING LINE UNLESS A SWITCH IS ATTACHED!  
  attachInterrupt(1, bumpInterrupt, FALLING);
} 

 
void loop() 
{
  digitalWrite(13, isBumped);
  
  if (isBumped) 
  { 
    // If we've been bumped, run the "back up and turn" ruotine, then
    // reset the variable so we're not "bumped" anymore
    doBump();
    isBumped = false;
  }
  else 
  {
    // Read a value from the photoresistor
    int photoVal = analogRead(photoPin);    

    // If we exceeded our threshold, go forward. Otherwise, stop.
    if (photoVal > photoThreshold)
    {
      forward();   
    } else {
      stop();
    }    
    
    delay(1);
  }
} 


// Back up for a second, then turn for a second.
void doBump()
{
  back();
  delay(1000);
  
  turnR();
  delay(1000);
  isBumped = !isBumped;
}


// When interrupt is triggered, just set "isBumped" to true so that
// the loop will run doBump(). We want to do as little work as
// possible inside an interrupt, and get back to loop() quickly.
void bumpInterrupt()
{
  isBumped = true;
  Serial.println(isBumped);
//  isBumped = true;
}


// Remap servo movement.
// Raw range: 0=full reverse, 90=stop, 180=full forward
// After remap: -90=full reverse, 0=stop, 90=full forward
// This also reverses the direction of one of the servos.
void move(int l, int r)
{
  // Throw out any inputs that aren't in the correct range
  if (l < -90 || l > 90 || r < -90 || r > 90)
  {
    return;
  }
  
  // ReMap left servo
  servoL.write(90+l);

  // ReMap and reverse right servo
  servoR.write(180-(90+r)); // -90 = 180-90-90 = 0
}

// Helpful shortcuts
void forward() { move(90,90);}
void back() { move(-90,-90); }
void turnL() { move(90,-90); }
void turnR() { move(-90,90); }
void stop() { move(0,0); }
