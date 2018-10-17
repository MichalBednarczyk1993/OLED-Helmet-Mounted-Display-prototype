#include "Led.h"
#include "Button.h"
#include "Buzzer.h"
#include "Displays.h"
#include "Task.h"

#define greenLedPin A5
#define redLedPin A4
#define statusLedPin 10 // yellow
#define btn1Pin 2 // Button Accept
#define btn2Pin 3 // Button Failure
#define powerPin 8 
#define buzzerPin 9
#define sclk 13 // (CL) 
#define mosi 11// (SI) 
#define rst  6 // (R)  
#define cs   5 // (SS)
#define dc   4 // (DC)   
#define cs2  7 // (SS) 
#define rst2  1 // (R) 


// GLOBAL parameters
bool powerState = true;
bool lastPowerState = false;
int iteration = 0;

Led greenLed(greenLedPin);
Led redLed(redLedPin);
Led statusLed(statusLedPin);
Buzzer buzz(buzzerPin);
Button btnAccept(btn1Pin);
Button btnFailure(btn2Pin);
Button powerSwitch(powerPin);
Displays disps(sclk, mosi, dc, cs, cs2, rst, rst2);


void setup() 
{
  disps.initDisps();
}

void loop() 
{
  powerState == powerSwitch.readState(); 

  /*if (powerState == true)
  {
    statusLed.setState(true);
  }
  else if (powerState == false)
  {
    statusLed.setState(false);
  }*/

  
  if (powerState == true)
  {
    if (powerState != lastPowerState)
    {
      programIntro();
    }
    else
    {
      programIteration();
    }
  }
  else if (powerState == false)
  {
    turnProgrammOff(); 
  }
  
  lastPowerState = powerState; 
}



void programIteration()
{
  // If it is pressed, the buttonState is false
  
  if (false == btnAccept.readState() && 
      true == btnFailure.readState())
  {
    btnAcceptAction();
    iteration++;
  }
  else if (true  == btnAccept.readState()  && 
           false == btnFailure.readState())
  {
    btnFailureAction();
    iteration++;
  }
  else if (true  == btnAccept.readState()   && 
           true  == btnFailure.readState()  && 
           iteration == 0)
 {
    disps.beforeStartView();           
 }
  
}

void btnAcceptAction()
{
  greenLed.setState(true);
  buzz.playOkTone();
  disps.taskView(iteration);
  greenLed.setState(false);
}


void btnFailureAction()
{
  redLed.setState(true);
  buzz.playFalseTone();
  disps.taskView(iteration);
  redLed.setState(false); 
}

void turnProgrammOff()
{
  greenLed.setState(false);
  redLed.setState(false);
  statusLed.setState(false);
  buzz.beQuiet();
  iteration = 0;
}

void programIntro()
{
  buzz.playIntro(statusLed); 
  disps.intro();  
}













