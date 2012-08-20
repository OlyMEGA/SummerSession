int ledPin = 9;    // LED connected to digital pin 9
int brightness;

void setup()  
{
	Serial.begin(9600);
	pinMode(ledPin, OUTPUT); 
} 

void loop()  
{    
  for(brightness = 0 ; brightness <= 255; brightness++) 
  { 
    analogWrite(ledPin, brightness);
    
    Serial.print("Brightness: ");
    Serial.println(brightness);

    delay(5);                            
  } 

  for(brightness = 255 ; brightness >= 0; brightness--) { 
    analogWrite(ledPin, brightness);         

    Serial.print("Brightness: ");
    Serial.println(brightness);

    delay(5);                            
  } 
}