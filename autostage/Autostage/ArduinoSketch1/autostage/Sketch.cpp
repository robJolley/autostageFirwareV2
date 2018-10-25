/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>

/*End of auto generated code by Atmel studio */

//autostage.cpp//
#include <SPI.h>
#include "motiontmc2130stepper.h"
//#include "intepretCommand.h"
#include "globalAutostageVars.h"
#include <EEPROM.h>
//Beginning of Auto generated function prototypes by Atmel Studio
void serialEvent();
//End of Auto generated function prototypes by Atmel Studio


serialReturn returnedData;
int responceToSend = 0;

angularTMC2130Stepper TMC2130_TT = angularTMC2130Stepper(EN_PIN_TT, DIR_PIN_TT, STEP_PIN_TT, CS_PIN_TT, TTLS);
linearTMC2130Stepper TMC2130_LS = linearTMC2130Stepper(EN_PIN_LS, DIR_PIN_LS, STEP_PIN_LS, CS_PIN_LS, LST1, LST2);

String inputString = "";         // a String to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup()
	{
		Serial.begin(9600);
		Serial.setTimeout(50);// Set the minimum timeout to 50ms to slow hangups,,  may be ideal to decrease this further.....
		inputString.reserve(16);
		TMC2130_TT.initilise();//Initilise with default settings
		TMC2130_LS.initilise();//Initilise with default settings
		TMC2130_LS.microsteps(COURSE);//  Increasing speed to move to home position.
		TMC2130_TT.microsteps(COURSE);
		delay(50);
		TMC2130_LS.home();//Sets position to move to home to
		TMC2130_TT.home();
		while(TMC2130_LS.move() && TMC2130_TT.move())//Continue to move to home untill 1 is returned from both steppers
			{
				delayMicroseconds(3);
			}
		TMC2130_LS.microsteps(SUPERFINE);//Return microsteps to highest available/May require redefinition......
		TMC2130_TT.microsteps(SUPERFINE);
	}

void loop()
	{	
		 
		
		if (TMC2130_LS.move() || TMC2130_TT.move())//Each return 1 if moving, also will move single step/microstep if steps available to take to desired position
			{
				inmove = true;
				
			}
		else
			{
				inmove = false;
			}
		if (stringComplete) 
			{
				returnedData = interpretCommand(inputString);
					if((returnedData.move == true) && (returnedData.responce == GOTOACK) && (inmove == false))//Valid command to move
						{
							TMC2130_LS.moveAbsolute(returnedData.lin);
							TMC2130_TT.moveAbsolute(returnedData.ang);
							responceToSend = GOTOACK;
						}
					else if ((returnedData.move == true) && (returnedData.responce == GOTOACK) && (inmove == true))//Cannot move as aleady moving
						{
							responceToSend = GOTOBSY;
						}
					else
						{
							responceToSend = returnedData.responce;
						}
					
				inputString = "";
				returnedData.move = false;
				stringComplete = false;
			}
		if(responceToSend > 0)
			{
				serialResponder(responceToSend);//Sets what to send back to Eyepass.
				responceToSend = 0;
			}
		
	}
	
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    char inputChar[4];
    inputString.toCharArray(inputChar,4);
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
  if ((inChar == '}') or (inputChar =="help")) {//Assuming 'find' works in adruino land,  should work for serial.find if not......
      stringComplete = true;
    }
  }
}

