#pragma once
#include <Arduino.h>
#include "Led.h"

class Buzzer 
{
public:
	Buzzer(int pin);
	~Buzzer();
	void playOkTone();
	void playFalseTone();
	void playIntro(Led &led);
	void playTone(int toneHz, int durationTime);
  void beQuiet();


private:
	int buzzer;

};

Buzzer::Buzzer(int pin)
{
	buzzer = pin;
}

Buzzer::~Buzzer()
{
}

void Buzzer::playIntro(Led &led)
{
  led.setState(true);
	playTone(2700, 200);
	led.setState(false);
	delay(25);
	led.setState(true);
	playTone(2700, 200);
	led.setState(false);
	delay(25);
	led.setState(true);
	playTone(2700, 200);
	led.setState(false);
	delay(25);
	led.setState(true);
	playTone(2000, 1000);
}


void Buzzer::playFalseTone()
{
	playTone(500, 500);
}

void Buzzer::playOkTone()
{
	playTone(3300, 200);
	delay(50);
	playTone(3300, 200);
}

void Buzzer::playTone(int toneHz, int durationTime)
{
	tone(buzzer, toneHz);
	delay(durationTime);
	noTone(buzzer);
}

void Buzzer::beQuiet()
{
    noTone(buzzer);
}


