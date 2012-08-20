int  ledPin1 = 13;
bool ledState1 = LOW;
int  ledInterval1 = 1000;
long ledLastTime1 = 0;

int  ledPin2 = 9;
bool ledState2 = HIGH;
int  ledInterval2 = 300;
long ledLastTime2 = 0;


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

	if (now - ledLastTime1 > ledInterval1)
	{
		ledState1 = !ledState1;		
		digitalWrite(ledPin1, ledState1);
		ledLastTime1 = now;

		Serial.print("LED 1: ");
		Serial.println(ledState1);
	}	

	if (now - ledLastTime2 > ledInterval2)
	{
		ledState2 = !ledState2;
		digitalWrite(ledPin2, ledState2);
		ledLastTime2 = now;

		Serial.print("LED 2: ");
		Serial.println(ledState2);
	}	
}