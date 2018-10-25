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
#define SNACK 11
#define COMMANDERROR 12
serialReturn interperetCommand(String inputString)
	{
		serialReturn returnData;//Struct to return comand respone including movement
		int linearMove, angularMove;
		
		switch(inputString[0:3])
	{
		case "{HB}"://  Heatbeat
			{
							returnData.move = false;
							returnData.responce = HB;
							returnData.lin = linearMove;
							returnData.ang = angularMove;
							break;
			}
		case "{btg":// GOTO
			{
			if((inputString[4:8] =="oto ") && (inputString[15] == "}")
					{
						linearMove = convertToInt(inputString[9:11]);
						angularMove = convertToInt(inputString[13:15]);
				
						if ((linearMove != 800) || (angularMove != 800))
							{
								returnData.move = false;
								returnData.responce = GOTOACK;
								returnData.lin = linearMove;
								returnData.ang = angularMove;
								break;
							}
						else
							{
								returnData.move = false;
								returnData.responce = GOTOACK;
								returnData.lin = 0;
								returnData.ang = 0;
								break;
							}
					}
				else
					{
							returnData.move = false;
							returnData.responce = GOTOSWERR;
							returnData.lin = 0;
							returnData.ang = 0;
							break;
					}
			}
		case "{btr":// Ready??
			{
			if (inputString[4:7] =="edy}")
				{
							returnData.move = false;
							returnData.responce = READYACK;
							returnData.lin = 0;
							returnData.ang = 0;
							break;
				}
			else
				{
							returnData.move = false;
							returnData.responce = READYSWERR
							returnData.lin = 0;
							returnData.ang = 0;
							break;
				}
			}
		case "{bth":// HOME
		{
		if (inputString[4:7] =="ome}"
				{
							returnData.move = false;
							returnData.responce = HOMEACK;
							returnData.lin = 0;
							returnData.ang = 0;
							break;
				}
			else
				{
							returnData.move = false;
							returnData.responce = HOMESWERR;
							returnData.lin = 0;
							returnData.ang = 0;
							break;
				}
			}
		case "{bte": //Extend
			{
			if (inputString[4:7] =="xtd}"
				{
							returnData.move = false;
							returnData.responce = EXTENDACK;
							returnData.lin = 0;
							returnData.ang = 0;
							break;
				}
			else
				{
							returnData.move = false;
							returnData.responce = EXTENDSWERR;
							returnData.lin = 0;
							returnData.ang = 0;
							break;
				}
			}
		case "{bti"://INFO
			{
			if (inputString[4:7] =="nfo}"
				{
							returnData.move = false;
							returnData.responce = INFO;
							returnData.lin = 0;
							returnData.ang = 0;
							break;
				}
			else
				{
							returnData.move = false;
							returnData.responce = NORESPONCE_CLEAR;
							returnData.lin = 0;
							returnData.ang = 0;
							break;
				}
			}
				case "{btw"://Serial number write
			{
			if ((inputString[4:7] =="tsn ") && (inputString[14] =="}"))
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
							break;
				}
			else
				{
							returnData.move = false;
							returnData.responce = NORESPONCE_CLEAR;
							returnData.lin = 0;
							returnData.ang = 0;
							break;
				}
			}
			default: //Default case dealing with bad commands
			{
				if(inputString[0] == "{")
					for(int x = 1;x<16;x++)
						{
						if(inputString[x] =="}")
							{
								returnData.responce = COMMANDERROR;
							}
						if(returnData.responce == COMMANDERROR
							break;
						else
								returnData.responce = NORESPONCE;
						}
									
						returnData.move = false;
						returnData.lin = 0;
						returnData.ang = 0;
							
			}
		
	}			
				return returnData;
	}
