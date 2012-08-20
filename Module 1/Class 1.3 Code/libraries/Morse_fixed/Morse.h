//
// Arduino Morse Library
// Written by Erik Linder SM0RVV and Mark VandeWettering K6HX
//
// Released 2011 under GPLv3
//
// Version 0.2
//

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


#ifndef Morse_h
#define Morse_h

class Morse
{
	public:
		Morse(byte pin, byte speed, byte beep);
		void sendmsg(char *str);
		void send(char c);
	private:
		void dash();
		void dit();
		void bdash();
		void bdit();
};
#endif
