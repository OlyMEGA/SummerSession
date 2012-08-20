int  ledPin1 = 13;
bool ledState1 = LOW;
int  ledInterval1 = 1000;
long ledLastTime1 = 0;

int  ledPin2 = 9;
bool ledState2 = HIGH;
int  ledInterval2 = 1000;
long ledLastTime2 = 0;

int sensorPin = A0;
int sensorValue = 0;

int minBlinkSpeed = 100;
int maxBlinkSpeed = 3000;

void setup()
{
	Serial.begin(9600);

	pinMode(ledPin1, OUTPUT);     
	pinMode(ledPin2, OUTPUT);     

	// Initialize times
	long now = millis();
	ledLastTime1 = now;
	ledLastTime2 = now;
}


void loop() 
{
	// Get current time
	long now = millis();
	int newSensorValue = analogRead(A0);

	if (newSensorValue != sensorValue)
	{
		sensorValue = newSensorValue;

		ledInterval1 = map(sensorValue, 0, 1023, minBlinkSpeed, maxBlinkSpeed);
		ledInterval2 = map(sensorValue, 0, 1023, maxBlinkSpeed, minBlinkSpeed);

		Serial.print("Set interval1 to: ");
		Serial.println(ledInterval1);

		Serial.print("Set interval2 to: ");
		Serial.println(ledInterval2);
	}


	if (now - ledLastTime1 > ledInterval1)
	{
		ledState1 = !ledState1;
		digitalWrite(ledPin1, ledState1);
		ledLastTime1 = now;

		Serial.print("Set LED1 to: ");
		Serial.print(ledState1);
		Serial.print(" at ");
		Serial.print(ledLastTime1);
		Serial.print(" with blinkInterval: ");
		Serial.println(ledInterval1);

	}	

	if (now - ledLastTime2 > ledInterval2)
	{
		ledState2 = !ledState2;
		digitalWrite(ledPin2, ledState2);
		ledLastTime2 = now;

		Serial.print("Set LED2 to: ");
		Serial.print(ledState2);
		Serial.print(" at ");
		Serial.print(ledLastTime2);
		Serial.print(" with blinkInterval: ");
		Serial.println(ledInterval2);
	}	
}