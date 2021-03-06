//motiontmc2130stepper.cpp

#include "motiontmc2130stepper.h"

int motionTMC2130Stepper::initilise(int microsteps,int SilinentStepStick,int stealthChop)
	{
		TMC2130Stepper::begin();
		TMC2130Stepper::microsteps(microsteps);
		TMC2130Stepper::SilentStepStick2130(SilinentStepStick); // Set stepper current
		TMC2130Stepper::stealthChop(stealthChop); // Enable extremely quiet stepping
		copyMicroSteps(microsteps);//Keeps track fo microsteps so that move can take it onto account.
		currentPos = UNKNOWN_POSITION;// Position is unknown untill home sequence complete.
		
		
		return 0;
	};
int motionTMC2130Stepper::initilise()
	{
		TMC2130Stepper::begin();
		TMC2130Stepper::microsteps(255);
		TMC2130Stepper::SilentStepStick2130(800); // Set stepper current
		TMC2130Stepper::stealthChop(1); // Enable extremely quiet stepping
		copyMicroSteps(255);
		currentPos = UNKNOWN_POSITION;//
		return 0;
	};
int motionTMC2130Stepper::moveRelative()
	{
	};
int motionTMC2130Stepper::position()
	{
		return currentPos;
	};
int motionTMC2130Stepper::moveAbsolute()
	{
	};
int motionTMC2130Stepper::home()
	{

	};
int motionTMC2130Stepper::move()
	{
	};
	
///////// Angular methods

int angularTMC2130Stepper::initilise(int microsteps,int SilinentStepStick,int stealthChop)
	{
		motionTMC2130Stepper::initilise(microsteps,SilinentStepStick,stealthChop);
		pinMode(index_pin, 
	}

float angularTMC2130Stepper::moveRelative(int move)
	{
		stepsToMove = move*(360/(STEPS*copyMicroSteps));
		if(move <180)
			::shaft_dir(true);
		else
			::shaft_dir(false);

		currentPos+=move;
		return (move%(STEPS*copyMicroSteps));// If 0 is returned all is good in life,  else shows partial step required to complete angle
	};

int angularTMC2130Stepper::moveAbsolute()
	{
		stepsToMove = move*(360/(STEPS*copyMicroSteps));
		if(move >= position()+180)
			{
				::shaft_dir(true);
				stepsToMove = (move - position())*(360/(STEPS*copyMicroSteps));
			}
		else
			::shaft_dir(false);

		currentPos+=move;
		return (move%(STEPS*copyMicroSteps));// If 0.0 is returned all is good in life,  else shows partial step required to complete angle cumulitive errors must be compensated for
	};
	
int angularTMC2130Stepper::home()
	{
		
	};

int angularTMC2130Stepper::index()
	{
		return 0;
	};
int angularTMC2130Stepper::move()
	{
		if(stepsToMove < 0)
			{
				digitaWrite(copyStep_pin, HIGH);
				delayMicroseconds(10);
				digitalWrite(copyStep_pin, LOW);
				stepsToMove --;
				moveReturnVar = 0;
			}	
		else
				moveReturnVar = 1;
		return moveReturnVar;
					
	}
	
//////////// Linear methods
int linearTMC2130Stepper::moveRelative(int move)
	{
		stepsToMove = move*(LEADSCREW_PITCH/(STEPS*copyMicroSteps));
		if(move < position())
			::shaft_dir(true);
		else
			::shaft_dir(false);

		currentPos += move;
		return (move%(STEPS*copyMicroSteps));// If 0 is returned all is good in life,  else shows partial step required to complete angle

	};

int linearTMC2130Stepper::moveAbsolute() 
	{
	};
	
int linearTMC2130Stepper::home()
	{

	};

int linearTMC2120Stepper::limit()
	{
		return 0;
	};
	

