#include "LPD8806.h"
#include "SPI.h"

int numLights = 10;

LPD8806 strip = LPD8806(numLights, 3, 2);  

void setupLights()
{
  strip.begin();
  randomSeed(analogRead(A0));
  
  for (int i=0; i<numLights; i++)
  {
    strip.setPixelColor(i, 255, 0, 255);  
  }
  
  
  strip.show();  
}


unsigned long lastChangeTime;
int changeInterval = 500;

uint32_t colors[6] = { strip.Color(127, 0, 0), strip.Color(64,64,0), strip.Color(0,127,0), strip.Color(0, 64, 64), strip.Color(0,0,127), strip.Color(64, 0, 64) };

int currentColor = 0;

void loopLights()
{
  unsigned long now = millis();
  
  if (now - lastChangeTime > changeInterval) {
    
    if (currentColor < 5) {
      currentColor++; 
    } else {
      currentColor = 0;
    }
    
    for (int i=0; i<numLights; i++)
    {
      strip.setPixelColor(i, colors[currentColor]);  
    }
   
    lastChangeTime = now;
    strip.show();  
  } 
}

