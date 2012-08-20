int ledPin1 = 13;
int ledPin2 = 9;

void setup()
{
	Serial.begin(9600);
	pinMode(ledPin1, OUTPUT);     
	pinMode(ledPin2, OUTPUT);     
}


void loop() 
{
	Serial.println("Going High");
	digitalWrite(ledPin1, HIGH);
	digitalWrite(ledPin2, HIGH);
	delay(1000);

	Serial.println("Going Low");
	digitalWrite(ledPin1, LOW);
	digitalWrite(ledPin2, LOW);
	delay(1000);
}