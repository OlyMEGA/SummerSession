int  ledPin1 = 13;
bool ledState1 = LOW;
int  ledInterval1 = 1000;
long ledLastTime1 = 0;

int ledPin2 = 9;
int ledValue2 = 0;

int sensorPin = A0;
int sensorValue = 0;

int minBlinkSpeed = 100;
int maxBlinkSpeed = 3000;

int minChangeThreshold = 5;

void setup()
{
	Serial.begin(9600);
	pinMode(ledPin1, OUTPUT);     
	pinMode(ledPin2, OUTPUT);     

	// Initialize time
	ledLastTime1 = millis();
}


void loop() 
{
	// Get current time
	long now = millis();
	int newSensorValue = analogRead(A0);

	int valueDifference = abs(newSensorValue - sensorValue);

	if (valueDifference >= minChangeThreshold)
	{
		sensorValue = newSensorValue;
		ledInterval1 = map(sensorValue, 0, 1023, minBlinkSpeed, maxBlinkSpeed);

		ledValue2 = map(sensorValue, 0, 1023, 0, 255);
		analogWrite(ledPin2, ledValue2);


		Serial.print("Set LED2 to: ");
		Serial.println(ledValue2);
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
}