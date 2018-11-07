//autostage.cpp//   
#include <SPI.h>
#include "motiontmc2130stepper.h"
//#include "intepretCommand.h"
#include "globalAutostageVars.h"
#include <EEPROM.h>
serialReturn returnedData;
int responceToSend = 0;
int charCount = 0;
boolean LS_Moving = false;
boolean TT_Moving = false;

angularTMC2130Stepper TMC2130_TT = angularTMC2130Stepper(EN_PIN_TT, DIR_PIN_TT, STEP_PIN_TT, CS_PIN_TT, TTLS);
linearTMC2130Stepper TMC2130_LS = linearTMC2130Stepper(EN_PIN_LS, DIR_PIN_LS, STEP_PIN_LS, CS_PIN_LS, LST1, LST2);

String inputString = "";         // a String to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup()
{
	Serial.begin(9600);
	Serial.setTimeout(50);// Set the minimum timeout to 50ms to slow hangups,,  may be ideal to decrease this further.....
	DDRC = DDRC & B11110011;// Mask to set pin A2 and A3 to input,  ignoring others used.
	PORTC = PORTC & B11110011;
	PORTC = PORTC | B00001100;
	inputString.reserve(16);
	TMC2130_TT.initilise();//Initilise with default settings
	TMC2130_LS.initilise();//Initilise with default settings
	delay(50);
	TMC2130_LS.microsteps(255);//  Increasing speed to move to home position.
	TMC2130_TT.microsteps(255);
	delay(50);
	digitalWrite(EN_PIN_TT, LOW);
    digitalWrite(EN_PIN_LS, LOW);
	TMC2130_LS.home();//Sets position to move to home to
	Serial.println("Out of home");
	TMC2130_TT.home();
	digitalWrite(EN_PIN_TT, HIGH);
    digitalWrite(EN_PIN_LS, HIGH);
	delayMicroseconds(50);
	//while(TMC2130_LS.move() || TMC2130_TT.move())//Continue to move to home untill 1 is returned from both steppers
	//{
	//	//delayMicroseconds(10);
	//}
	TMC2130_LS.microsteps(SUPERFINE);//Return microsteps to highest available/May require redefinition......
	TMC2130_TT.microsteps(SUPERFINE);
	delayMicroseconds(50);
    digitalWrite(EN_PIN_TT, LOW);
    digitalWrite(EN_PIN_LS, LOW);
	delayMicroseconds(50);
}

void loop()
{	
	
	LS_Moving = TMC2130_LS.move();
    TT_Moving = TMC2130_TT.move();
//	Serial.println(" LS_Moving::");
//	Serial.println(LS_Moving);
//	Serial.println(" TT_Moving::");
//	Serial.println(TT_Moving);
	if (LS_Moving || TT_Moving)//Each return 1 if moving, also will move single step/microstep if steps available to take to desired position
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
	if(!inmove)// to accomidate timimg requirments of steppers.
	{
		while (Serial.available()) {
			// get the new byte:
			char inChar = (char)Serial.read();
			//	Serial.println("Here");
			
			// add it to the inputString:
			inputString+=inChar;
			// if the incoming character is a newline, set a flag so the main loop can
			// do something about it:
			if ((inChar == '}') or (inputString =="help")) 
			{
				stringComplete = true;
				//  Serial.println("Recived Signal");
			}
			else
			{
				stringComplete = false;
				//	Serial.println("False");
			}
			
			
			if((!(inputString.startsWith("{")) && (!(inputString.startsWith("h")))))
			{
				inputString = "";
			}
			
		}
	}

}

