void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  int sensorValue = analogRead(A0);

  Serial.print("Value of sensor is: ");
  Serial.println(sensorValue);
  
  delay(1); // Allow ADC to "settle" between readings
}
