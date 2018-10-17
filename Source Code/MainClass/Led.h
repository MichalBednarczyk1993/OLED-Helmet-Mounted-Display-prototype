#pragma once
#include <Arduino.h>

class Led 
{
	private: 
		int led;

	public:

		Led(int pinNum);
		~Led();

		void setState(bool setHigh);
		void initialBlinking();
		
		 

};

Led::Led(int pinNum)
{
	led = pinNum;
	pinMode(led, OUTPUT);
}

Led::~Led()
{
	digitalWrite(led, LOW);
}

void Led::setState(bool setHigh)
{
	setHigh ? digitalWrite(led, HIGH) : digitalWrite(led, LOW);
}

void Led::initialBlinking()
{
	for (int i = 0; i < 5; i++)
	{
		setState(true);
		delay(500);
		setState(false);
		delay(500);
	}
}

