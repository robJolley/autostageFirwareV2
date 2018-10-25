#include <SPI.h>
#include "motiontmc2130stepper.h"

/*
Initializes the library and turns the motor in alternating directions.
*/
#define EN_PIN_TT    6  // Nano v3:  16 Mega:  38  //enable (CFG6)
#define DIR_PIN_TT   A4 //      19      55  //direction
#define STEP_PIN_TT  4  //      18      54  //step
#define CS_PIN_TT    5  //      17      64  //chip select

#define EN_PIN_LS    10  // Nano v3:  16 Mega:  38  //enable (CFG6)
#define DIR_PIN_LS   9 //      19      55  //direction
#define STEP_PIN_LS  8  //      18      54  //step
#define CS_PIN_LS    7  //      17      64  //chip select
#define GREEN_LED A0
#define RED_LED A1
#define MTR_DRV 3
#define PB A5
#define LST1 A2
#define LST2 A3
#define TTLS  2

bool dir = true;
byte val = 0;
bool switcher = false;
long previousMillis;
long interval = 1000;
#include <TMC2130Stepper.h>
angularTMC2130Stepper TMC2130_TT = angularTMC2130Stepper(EN_PIN_TT, DIR_PIN_TT, STEP_PIN_TT, CS_PIN_TT, TTLS);
linearTMC2130Stepper TMC2130_LS = linearTMC2130Stepper(EN_PIN_LS, DIR_PIN_LS, STEP_PIN_LS, CS_PIN_LS, LST1, LST2);

void setup()
	{
		TMC2130_TT.initilise();//Initilise with default settings
		TCM2130_LS.initilise();//Initilise with default settings
		TCM2130_LS.home();
		TMC2130_TT.home();
	}

void loop()
	{	
		 
		
		(TMC2130_LS.move() || TMC2130_TT.move())
		TMC2130_TT.move();
	}
	


