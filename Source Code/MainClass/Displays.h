#pragma once
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <SPI.h>
#include "Task.h"

// Color definitions
#define BLACK           0x0000
#define BLUE            0x001F
#define RED             0xF800
#define GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0 
#define WHITE           0xFFFF


class Displays 
{
public:
  Displays(int sclk, int mosi, int dc, int cs, int cs2, int rst, int rst2);
  ~Displays();
  void initDisps(); // 21 znaków poziomo
  void beforeStartView();
  void intro();
  void taskView(int taskNum);
  void correctAnsView();
  void wrongAnsView();
  void testView();


private:
  Adafruit_SSD1351 disp1;
  Adafruit_SSD1351 disp2;
  int numOf;
 
  bool printTextLine(String text, int line, int totalLines);
  int getNumOfLines(String task);
  int Displays::getYpos(int line, int totalLines);
  int Displays::getXpos(int stringLen);
  
};

Displays::Displays(int sclk, int mosi, int dc, int cs, int cs2, int rst, int rst2)
: disp1(cs, dc, mosi, sclk, rst), disp2(cs2, dc, mosi, sclk, rst2)
{
  numOf = 0;
}

Displays::~Displays()
{
}


void Displays::initDisps()
{
 Serial.begin(9600);
    disp1.begin();
    disp2.begin();
}


void Displays::beforeStartView()
{
  if (numOf == 0)
  {
	  disp1.fillScreen(BLACK);
    disp2.fillScreen(BLACK);
    disp1.setTextColor(GREEN);
    disp2.setTextColor(GREEN);
	disp1.setCursor(15, 64); 
    disp2.setCursor(15, 64); 
	disp1.print("Press any button");
    disp2.print("Press any button");
	disp1.setCursor(35, 74); 
    disp2.setCursor(35, 74); 
	disp1.print("to start");
    disp2.print("to start");
	numOf++;
  }
  else if (numOf > 3)
  {
    delay(1000);
    numOf = 0;
    beforeStartView();
  }
  else 
  {
    disp1.print(".");
    disp2.print(".");
    numOf++;
  }

  delay(250);
}


void Displays::intro()
{
  disp1.fillScreen(BLUE);
  disp1.setCursor(34, 84); // X, Y
  disp1.setTextColor(RED);
  disp1.print(" Ada_Disp ");
  disp1.fillRect(54, 54, 20, 20, RED);
  
  disp2.fillScreen(BLUE);
  disp2.setCursor(34, 84); // X, Y
  disp2.setTextColor(RED);
  disp2.print(" Ada_Disp ");
  disp2.fillRect(54, 54, 20, 20, RED);

  delay(500);
}



void Displays::taskView(int taskNum)
{
  int index = 0;
  int lastIndex = 0;
  int line = 1;
  int numOfLines;
  String task;
  String subString;

  printTextLine("", 0, 0);
  task = tasksN[taskNum];
  numOfLines = getNumOfLines(task);

  while (lastIndex < task.length())
  {
    index = task.indexOf("\n", lastIndex);
    subString = task.substring(lastIndex, index);  
    lastIndex += subString.length() + 2;

    printTextLine(subString, line, numOfLines);
    line++;
  } 
   
}


void Displays::correctAnsView()
{
  disp1.fillRect(0, 32, 128, 5, GREEN);
  disp2.fillRect(0, 32, 128, 5, GREEN);
  
  disp1.fillRect(0, 123, 128, 5, GREEN);
  disp2.fillRect(0, 123, 128, 5, GREEN);
}


void Displays::wrongAnsView()
{
  disp1.fillRect(0, 32, 128, 5, RED);
  disp2.fillRect(0, 32, 128, 5, RED);
  
  disp1.fillRect(0, 123, 128, 5, RED);
  disp2.fillRect(0, 123, 128, 5, RED);
}


void Displays::testView()
{
	String text;

	if (numOf == 0)
	{
		text = "Are you ready?";
		printTextLine(text, 1, 1);
	}
	else if (numOf == 1)
	{
		text = "Press wrong\nanswer button.";
		printTextLine(text, 1, 2);
		printTextLine(text, 2, 2);
		// student should see red screen elements
	}
	else if (numOf == 2)
	{
		text = "Press good\nanswer button.";
		printTextLine(text, 1, 2);
		printTextLine(text, 2, 2);
		// student should see green screen elements
	}

}


/**This method print text line in the center, of the display 120x120px.
Return false and pring communicate in case of error.*/
bool Displays::printTextLine(String text, int line, int totalLines)
{
  // ilosc liter
  // oblicz pozycje x
  // oblicz pozycje y jezeli to n-linia/x-linii

  
	int textSize  = text.length();
	int yPos = (4 + ((15 - totalLines) * 4)) + ((line - 1) * 8);
  int xPos = 4 + (((20 - textSize) * 5) / 2);

  if(line == 0)
  {
    disp1.fillScreen(BLACK);
    disp2.fillScreen(BLACK);
    disp1.setTextColor(GREEN);
    disp2.setTextColor(GREEN);
  }
  else 
  {
    if (textSize < 21)
    {
      disp1.setCursor(xPos, yPos);
      disp1.print(text);
      disp2.setCursor(xPos, yPos);
      disp2.print(text);
    }
    else
    {
      xPos = 54;
      yPos = 4 + (7 * 8);
      disp1.setCursor(xPos, yPos);
      disp1.print("error");
      disp2.setCursor(xPos, yPos);
      disp2.print("error");
    }  
  }
}

int Displays::getNumOfLines(String task)
{
  int line = 0;
  int index = 0;
  int lastIndex = 0;
  String subString;
  
  for (int i = 0; i < task.length(); i++)
  {
    index = task.indexOf("\n", lastIndex);
    subString = task.substring(lastIndex, index);  
    i += subString.length() + 2;
    lastIndex = index + 2;
    line++;
  }

  return line;
}



/*
 * Remember to count from 0 !
 * 
 * Zatem pierwsza linijka powinna się zaczynac na wysokosci Y = 34
 * Kazda nastepna powinna byc o 10 pxl nizej
 * Lacznie jest 8 linii poziomych
 * 
 * Pierwszy znak powinien byc na punkcie X = 1
 * Kazdy nastepny powinien byc 5 pxl dalej
 * Lacznie sa 24 punkty
 */
int Displays::getXpos(int stringLen)
{
  return ((24 - stringLen) / 2) * 5; 
}


int Displays::getYpos(int line, int totalLines)
{
  int totalPos = 24 + (((8 - totalLines) / 2) * 10);
  int linePos = totalPos + (line - 1) * 10;

  return linePos;
}















