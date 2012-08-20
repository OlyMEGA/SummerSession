int redSensorPin   = A0;
int greenSensorPin = A1;
int blueSensorPin  = A2;

int redPin   = 9;
int greenPin = 10;
int bluePin  = 11;

int redValue   = 0;
int greenValue = 0;
int blueValue  = 0;

int minChangeThreshold = 3;

void setup() 
{
    Serial.begin(9600);

    pinMode(redPin,   OUTPUT);  
    pinMode(greenPin, OUTPUT);  
    pinMode(bluePin,  OUTPUT);  
}

void loop() 
{
    // read the value from the sensors:
    int redSensorValue   = analogRead(redSensorPin);    
    int greenSensorValue = analogRead(greenSensorPin);    
    int blueSensorValue  = analogRead(blueSensorPin);    

    // Convert from analogRead scale (0-1023) to analogWrite scale (0-255)
    int newRedValue   = map(redSensorValue,  0, 1023, 0, 255);
    int newGreenValue = map(greenSensorValue, 0, 1023, 0, 255);
    int newBlueValue  = map(blueSensorValue,  0, 1023, 0, 255);

    int redDiff = abs(newRedValue - redValue);
    int greenDiff = abs(newGreenValue - greenValue);
    int blueDiff = abs(newBlueValue - blueValue);

    // If value has changed, Update stored value, and led brightness
    if (redDiff >= minChangeThreshold || greenDiff >= minChangeThreshold || blueDiff >= minChangeThreshold)
    {
        Serial.print("RGB: ");
        
        Serial.print(redValue);
        Serial.print("/");
        Serial.print(greenValue);
        Serial.print("/");
        Serial.println(blueValue);
    }


    if (redDiff >= minChangeThreshold)
    {
        redValue = newRedValue;
        analogWrite(redPin, redValue);

        Serial.print("Changed Red: ");
        Serial.println(redValue);
    }

    if (greenDiff >= minChangeThreshold)
    {
        greenValue = newGreenValue;
        analogWrite(greenPin, greenValue);

        Serial.print("Changed Green: ");
        Serial.println(greenValue);
    }

    if (blueDiff >= minChangeThreshold)
    {
        blueValue = newBlueValue;
        analogWrite(bluePin, blueValue);

        Serial.print("Changed Blue: ");
        Serial.println(blueValue);
    }

    // Let ADC settle
    delay(1);                  
}