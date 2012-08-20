int sensorPin = A0;
int ledPin = 13;

int ledValue = 0;

void setup() 
{
  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);  
}

void loop() 
{
  // read the value from the sensor:
  int sensorValue = analogRead(sensorPin);    

  // Convert from analogRead scale (0-1023) to analogWrite scale (0-255)
  int newLedValue = map(sensorValue, 0, 1023, 0, 255);

  // If value has changed
  if (ledValue != newLedValue) 
  {
    // Update stored value, and led brightness
    ledValue = newLedValue;
    analogWrite(ledPin, ledValue);

    Serial.print("Sensor value: ");
    Serial.print(sensorValue);
    Serial.print(" Output Value: ");
    Serial.println(ledValue);
  }

  // Let ADC settle
  delay(1);                  
}