// SerialResponder.ino
#include "globalAutostageVars.h"

int serialResponder(int responce)
{
	switch(responce)
	{
		case HB:
		{
			Serial.write("<HB>");
			Serial.write('\n');
			break;
		}	
		case GOTOACK:
		{
			Serial.write("<btgoto ack>");
			Serial.write('\n');
			break;
		}
		case GOTOSWERR:
		{
			Serial.write("<btgoto swerr>");
			Serial.write('\n');
			break;
		}
		case READYACK:
		{
			Serial.write("<btredy ack>");
			Serial.write('\n');
			break;
		}
		case READYSWERR:
		{
			Serial.write("<btredy swerr>");
			Serial.write('\n');
			break;
		}
		case HOMEACK:
		{
			Serial.write("<bthome ack>");
			Serial.write('\n');
			break;
		}
		case EXTENDACK:
		{
			Serial.write("<btextd ack>");
			Serial.write('\n');
			break;
		}
		case EXTENDSWERR:
		{
			Serial.write("<btextd swerr>");
			Serial.write('\n');
			break;
		}
		case NORESPONCE_CLEAR:
		{
			Serial.write("<btnotcl>");//ie not clear...
			Serial.write('\n');
			break;
		}
		case SNACK ://Serial number written to EEPROM
		{
			Serial.write("<btwtsn ack>");
			Serial.write('\n');
			break;
		}
		case HELP:
		{
			helpPrint();
			break;
		}
		case GOTOBSY:
		{
			Serial.write("<btgoto bsy>");
			Serial.write('\n');
			break;
		}
		case INFO:
		{
			printInfo();
			break;
		}
		case COMMANDERROR:
		{
			Serial.write("<btcomd err>");
			Serial.write('\n');
			break;
		}
		default :
		{
			Serial.write("<?>");
			Serial.write('\n');
			break;
		}
		
	}
}


void helpPrint()
{
	Serial.write("Full list of commands");// Define list of comands to be printed.......
	Serial.write('\n');
}

void printInfo()
{
	Serial.write("<bt info ");
	Serial.write("hw:xxxx ");
	Serial.write("fw:0.0.1 ");
	Serial.write("sn ");
	Serial.write((char)EEPROM.read(0));
	Serial.write((char)EEPROM.read(1));
	Serial.write((char)EEPROM.read(2));
	Serial.write((char)EEPROM.read(3));
	Serial.write((char)EEPROM.read(4));
	Serial.write((char)EEPROM.read(5));
	Serial.write(" wa:0650");
	Serial.write(" sc:0000");  //Error code storage to be defined.
	Serial.write(">");
	Serial.write('\n');
}
