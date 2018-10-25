#define NORESPONCE 0
#define HB 1
#define GOTOACK 2
#define GOTOSWERR 3
#define READYACK 4
#define READYSWERR 5
#define HOMEACK 6
#define HOMESWERR 7
#define EXTENDACK 8
#define EXTENDSWERR 9
#define NORESPONCE_CLEAR 10
#define SNACK 11  //serial number acknowlege
#define COMMANDERROR 12
#define HELP 13
#define GOTOBSY 14
#define INFO 15

int serialResponder(int responce)
	{
		switch(responce)
			{
				case HB:
					serial.println("<HB>");
				case GOTOACK:
					serial.println("<btgoto ack>");
				case GOTOSWERR:
					serial.println("<btgoto swerr>");
				case READYACK:
					serial.println("<btredy ack>");
				case READYSWERR:
					serial.println("<btredy swerr>");
				case HOMEACK:
					serial.println("<bthome ack>");
				case EXTENDACK:
					serial.println("<btextd ack>");
				case EXTENDSWERR:
					serial.println("<btextd swerr>");
				case NORESPONCE_CLEAR:
					serial.println("<btnotcl>");//ie not clear...
				case SNACK//Serial number written to EEPROM
					serial.println("<btwtsn ack>");
				case HELP:
					helpPrint();
				case GOTOBSY:
					serial.println("<btgoto bsy>");
				case INFO:
					printInfo();
				case COMMANDERROR:
					serial.println("<btcomd err>");
				default :
					serial.println("?");
			}
	}
void helpPrint()
	{
		println("Full list of ocmmands");// Define list of comands to be printed.......
	}

void printInfo()
	{
		println("<bt info");
		println("hw:xxxx");
		println("fw:0.0.1");
		print("sn ");
		print(EEPROM.read(0));
		print(EEPROM.read(1));
		print(EEPROM.read(2));
		println(EEPROM.read(3));
		println("wa:0650");
		print("sc:0000");  //Error code storage to be defined.
		println(">");
	}
				
				
				
			}
	}