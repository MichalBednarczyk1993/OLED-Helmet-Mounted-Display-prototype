#pragma once
#include <Arduino.h>

class Button
{
public:
	Button(int pinNumber);
	~Button();
	bool readState();

private:
	int btn;
	int btnState = 0;

};

Button::Button(int pinNumber)
{
	btn = pinNumber;
	pinMode(btn, INPUT);
}

Button::~Button()
{

}

bool Button::readState()
{
	return digitalRead(btn);
}



