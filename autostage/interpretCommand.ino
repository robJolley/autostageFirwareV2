#include "globalAutostageVars.h"

serialReturn interpretCommand(String inputString)
{
	serialReturn returnData;//Struct to return comand respone including movement
	int linearMove, angularMove;
	char inputChar[4];
//	Serial.println(inputString);
	
	
	
    if(inputString == "{HB}")//  Heatbeat
	
	{
		returnData.move = false;
		returnData.responce = HB;
		returnData.lin = 0;
		returnData.ang = 0;
//		Serial.println("Got into HB");
	}
	if(inputString =="help" || inputString =="Help")
	{
		returnData.move = false;
		returnData.responce = HELP;
		returnData.lin = 0;
		returnData.ang = 0;
	}
	
    if(inputString.substring(0,8) == "{btgoto ")
	{
//		Serial.println("4-4 substring_____");
//		Serial.println(inputString.substring(0,8));
		if(inputString.endsWith("}"))
		{
			linearMove = (inputString.substring(8,11).toInt());
			angularMove =(inputString.substring(12,15).toInt());
//			Serial.print("Linear move: ");
//			Serial.print(linearMove);
//			Serial.print("  Angular move: ");
//			Serial.println(angularMove);
			
			if ((linearMove >= 100) && (angularMove >= 100) && linearMove !=800 && angularMove !=800)//Add 100 to desired value in order to ensure numeric value sent
			{
				returnData.move = false;
				returnData.responce = GOTOACK;
				returnData.lin = linearMove;
				returnData.ang = angularMove;
			}
			else
			{
				returnData.move = false;
				returnData.responce = GOTOSWERR;
				returnData.lin = 0;
				returnData.ang = 0;
			}
		}
		else
		{
			returnData.move = false;
			returnData.responce = GOTOSWERR;
			returnData.lin = 0;
			returnData.ang = 0;
		}
	}
	
	if(inputString == "{btredy}")//Ready??
	{
		returnData.move = false;
		returnData.responce = READYACK;
		returnData.lin = 0;
		returnData.ang = 0;
	}
    if(inputString == "{bthome}")//HOME
	
	{
		returnData.move = false;
		returnData.responce = HOMEACK;
		returnData.lin = 0;
		returnData.ang = 0;
	}
	
    if(inputString  == "{btextd}")//Extend
	{
		returnData.move = false;
		returnData.responce = EXTENDACK;
		returnData.lin = 0;
		returnData.ang = 0;
	}
	
    if(inputString == "{btinfo}")//INFO
	{
		returnData.move = false;
		returnData.responce = INFO;
//		Serial.println("Got to BTINFO");
		returnData.lin = 0;
		returnData.ang = 0;
	}
	
	if(inputString.substring(0,8) == "{btwtsn ")//Serial number write
	
	{
	if (inputString.endsWith("}"))
		{
			EEPROM.write(0, inputString[8]);//Write directy to EEPROM here rather than exit as it is a very infrequent activity
			EEPROM.write(1, inputString[9]);
			EEPROM.write(2, inputString[10]);
			EEPROM.write(3, inputString[11]);
			EEPROM.write(4, inputString[12]);
			EEPROM.write(5, inputString[13]);
			returnData.move = false;
			returnData.responce = SNACK;
			returnData.lin = 0;
			returnData.ang = 0;
		}
		else
		{
			returnData.move = false;
			returnData.responce = NORESPONCE_CLEAR;
			returnData.lin = 0;
			returnData.ang = 0;
		}
	}
	else //Default case dealing with bad commands
	{
		if(inputString[0] == "{")
		{
			for(int x = 1;x<16;x++)
			{
				if(inputString[x] =="}")
				{
					returnData.responce = COMMANDERROR;
				}
				else
				{
					returnData.responce = NORESPONCE;
				}
			}
			
			returnData.move = false;
			returnData.lin = 0;
			returnData.ang = 0;
			
		}
	}
	
	return returnData;
	
}
