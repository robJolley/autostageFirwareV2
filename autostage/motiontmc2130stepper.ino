//motiontmc2130stepper.cpp

#include "motiontmc2130stepper.h"
#include "globalAutostageVars.h"
#include <math.h>
#define NOLIMIT 0
#define LEFTLIMIT 1
#define RIGHTLIMIT 2
#define BOTHLIMITS 3

int motionTMC2130Stepper::initilise(int microsteps,int SilinentStepStick,int stealthChop)
{
	TMC2130Stepper::begin();
	TMC2130Stepper::microsteps(microsteps);
	TMC2130Stepper::SilentStepStick2130(SilinentStepStick); // Set stepper current
	TMC2130Stepper::stealthChop(stealthChop); // Enable extremely quiet stepping
	copyMicroSteps = microsteps;//Keeps track fo microsteps so that move can take it onto account.
	currentPos = UNKNOWN_POSITION;// Position is unknown untill home sequence complete.
    
	
	
	return 0;
}
int motionTMC2130Stepper::initilise()
{
	TMC2130Stepper::begin();
	TMC2130Stepper::microsteps(255);
	TMC2130Stepper::SilentStepStick2130(255); // Set stepper current
	TMC2130Stepper::stealthChop(1); // Enable extremely quiet stepping
	copyMicroSteps = 255;
	currentPos = UNKNOWN_POSITION;//
	
	return 0;
}
int motionTMC2130Stepper::moveRelative(int move)
{
}
int motionTMC2130Stepper::position()
{
	return currentPos;
}


///////// Angular methods

int angularTMC2130Stepper::initilise(int microsteps,int SilinentStepStick,int stealthChop)
{
	motionTMC2130Stepper::initilise(microsteps,SilinentStepStick,stealthChop);
	pinMode(index_pin,INPUT); 
}
int angularTMC2130Stepper::initilise()
{
    motionTMC2130Stepper::initilise();
    pinMode(index_pin,INPUT); 
}

float angularTMC2130Stepper::moveRelative(int move)
{
	stepsToMove = move*(360/(STEPS*copyMicroSteps));
	if(move <180)
	shaft_dir(true);
	else
	shaft_dir(false);
	
	currentPos+=move;
	return (move%(STEPS*copyMicroSteps));// If 0 is returned all is good in life,  else shows partial step required to complete angle
}

float angularTMC2130Stepper::moveAbsolute(int move)
{
	stepsToMove = ((float)STEPS*(copyMicroSteps)/360.0);
	
	if(move >= position()+180)
	{
		motionTMC2130Stepper::shaft_dir(true);
		stepsToMove = ((float)(move - position())*stepsToMove);
	}
	else
	{
		motionTMC2130Stepper::shaft_dir(false);
		stepsToMove = (float)(move)*stepsToMove;
	}
	
	currentPos+=move;
	intStepsToMove = (long)stepsToMove;
	
	return fmod(stepsToMove, 1);// If 0.0 is returned all is good in life,  else shows partial step required to complete angle cumulitive errors must be compensated for
	
};

int angularTMC2130Stepper::home()
{
	return ANGULAR_HOME;
}

int angularTMC2130Stepper::index()
{
	return 0;
}

byte angularTMC2130Stepper::move()
{
	
	if(intStepsToMove > 0)
	{
		digitalWrite(copyStep_pin, HIGH);        
		delayMicroseconds(10);
		digitalWrite(copyStep_pin, LOW);
		delayMicroseconds(10);
		intStepsToMove --;
		moveReturnVar = 1;
	}	
	else
	moveReturnVar = 0;
	return moveReturnVar;
	
}

//////////// Linear methods
int linearTMC2130Stepper::initilise(int microsteps,int SilinentStepStick,int stealthChop)
{
    motionTMC2130Stepper::initilise(microsteps,SilinentStepStick,stealthChop);
    pinMode(limit1_pin,INPUT);
	pinMode(limit2_pin,INPUT);
}
int linearTMC2130Stepper::initilise()
{
    motionTMC2130Stepper::initilise();
    pinMode(limit1_pin,INPUT);
    pinMode(limit2_pin,INPUT); 
}

float linearTMC2130Stepper::moveRelative(int move)
{
	stepsToMove = move*(LEADSCREW_PITCH/(STEPS*copyMicroSteps));
	if(move < position())
	shaft_dir(true);
	else
	shaft_dir(false);
	
	currentPos += move;
	float (move%(STEPS*copyMicroSteps));// If 0 is returned all is good in life,  else shows partial step required to complete angle
	
}

float linearTMC2130Stepper::moveAbsolute(int move) 
{
	if(move < 0)
	{
		shaft_dir(false);
		shaftDir = false;
		move = abs(move);
	}
    else
	{
		shaft_dir(true);
		shaftDir = true;
	}
    stepsToMove = (float)move*((((float)STEPS/2.0)*(float)copyMicroSteps)/LEADSCREW_PITCH);
//	Serial.print("Move::");
//	Serial.print(move);
//	Serial.print(" Copy Microsteps::");
//	Serial.print(copyMicroSteps);
//	Serial.print(" Steps::");
//	Serial.print(STEPS);
//	Serial.print(" Lead crew pitch::");
//	Serial.print(LEADSCREW_PITCH);
//	Serial.print(" Steps to move::");
//  Serial.println(stepsToMove);
//	Serial.print(" Shaft Dir:");
//	Serial.println(shaft_dir());
	intStepsToMove = (long)stepsToMove;
    return (move%(STEPS*copyMicroSteps));// If 0 is returned all is good in life,  else shows partial step required to complete angle
};

byte linearTMC2130Stepper::home()
{	
	byte homeReturn = 0;
	byte limitH = limit();
	if(limitH == LEFTLIMIT)
	{
		leftStop = 1;
		rightStop = 0;
	}
	else if (limitH == RIGHTLIMIT)
	{
		leftStop = 0;
		rightStop = 1;
	}
	else
	{
		leftStop = 0;
		rightStop = 0;		
	}
//	Serial.print("Left Stop:");
//	Serial.println(leftStop);
//	Serial.print(" RightStop:");
//	Serial.println(rightStop);
	if ((leftStop && (!rightStop)) || ((!leftStop) && (!rightStop)))
	{
		
		moveAbsolute(25);
		while(move() == 1)
		{
			
		}
		homeReturn = 1;
		currentPos = 25;
	}
	
	else if ((rightStop) && !(leftStop))
	{
		homeReturn = 1;
		currentPos = 25;
	}
	
	return homeReturn;
}

int linearTMC2130Stepper::limit()
{
	byte limitReturn;
	byte stoplimit = PINC;
	byte leftStoplimit = stoplimit & B00000100;
	byte rightStoplimit = stoplimit & B00001000;
	if(leftStoplimit && !rightStoplimit)
		limitReturn = LEFTLIMIT;
	else if (!leftStoplimit && rightStoplimit)
		limitReturn = RIGHTLIMIT;
	else if (leftStoplimit && rightStoplimit)
		limitReturn = BOTHLIMITS;
	else
		limitReturn = NOLIMIT;
//	Serial.print(" Limit::");
//	Serial.println(limitReturn);
	
	return limitReturn;	
}
byte linearTMC2130Stepper::move()
{
	byte moveLimit = limit();
	bool leftLimitHit = ((shaftDir == true) && (moveLimit == LEFTLIMIT));
	bool leftLimitHitStop = ((shaftDir == false) && (moveLimit == LEFTLIMIT));
	bool rightLimitHit ((shaftDir == true) && (moveLimit == RIGHTLIMIT));
	bool rightLimitHitGo ((shaftDir == false) && (moveLimit == RIGHTLIMIT));
//	Serial.print(" leftLimitHit::");
//	Serial.print(leftLimitHit);
//	Serial.print(" leftLimitHitStop::");
//	Serial.print(leftLimitHitStop);
//	Serial.print(" rightLimitHit::");
//	Serial.print(rightLimitHit);
//	Serial.print("rightlimitHitGo::");
//	Serial.println(rightLimitHitGo);
	
	if(leftLimitHit && (intStepsToMove > 0))//Hit left limit,  stop motion
	{	
//		Serial.println("Hit left,  continue moving");
		//intStepsToMove = 0;
		digitalWrite(copyStep_pin, HIGH);
		delayMicroseconds(2);
		digitalWrite(copyStep_pin, LOW);
		delayMicroseconds(2);
		//		Serial.println(intStepsToMove);
		intStepsToMove --;
		currentPos = -25;
		moveReturnVar = 1;
	}
	else if(rightLimitHitGo && (intStepsToMove > 0))//Hit left limit,  stop motion
	{	
//		Serial.println("Hit left,  continue moving");
		//intStepsToMove = 0;
		digitalWrite(copyStep_pin, HIGH);
		delayMicroseconds(2);
		digitalWrite(copyStep_pin, LOW);
		delayMicroseconds(2);
		//		Serial.println(intStepsToMove);
		intStepsToMove --;
		currentPos = 25;
		moveReturnVar = 1;
	}
	else if(rightLimitHit && (intStepsToMove > 0))//Hit right limit,  stop motion
	{	
//		Serial.println("Hit right , STOP!!");
		intStepsToMove = 0;
		currentPos = 25;
		moveReturnVar = 2;
	}
	else if(leftLimitHitStop && (intStepsToMove > 0))//Hit right limit,  stop motion
	{	
//		Serial.println("Hit right , STOP!!");
		intStepsToMove = 0;
		currentPos = -25;
		moveReturnVar = 3;
	}
	//	Serial.println(intStepsToMove);
	else if(intStepsToMove > 0 && ((!leftLimitHit) || (!rightLimitHit)))
	{	
//		Serial.println("nothing hit,  continue moving");
		digitalWrite(copyStep_pin, HIGH);
		delayMicroseconds(2);
		digitalWrite(copyStep_pin, LOW);
		delayMicroseconds(2);
		//		Serial.println(intStepsToMove);
		intStepsToMove --;
		moveReturnVar = 1;
	}	
	else
		moveReturnVar = 0;
	
	return moveReturnVar;
	
}
