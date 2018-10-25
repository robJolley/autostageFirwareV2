//motiontmc2130stepper.h
#pragma once
#include <SPI.h>
#include <TMC2130Stepper.h>

#ifndef MOTIONTMC2130STEPPER_H
#define MOTIONTMC2130STEPPER_H

#define STEPS 200
#define LEADSCREW_PITCH 2.54
#define UNKNOWN_POSITION 400

class motionTMC2120Stepper: public TMC2130Stepper{
	public:
		int initilise(int,int,int);//To be used in setup code section,  performs begin, microsteps,SilentStepStick & stelthChop
		int home();//move to home position returns 1 when complete?
		int moveRelative (int);//Move relative from existing point,  returns absolute position
		int moveAbsolute(int);//Move to absolute position 
		int position();// Returns position of stepper
	private:
		int copyMicroSteps;//Copy of pins so we dont have to look inside the black box.
		int copyEnable_pin;
		int copyDir_pin;
		int copyStep_pin;
		int copyCs_pin;
		int currentPos;
}

class angularTMC2120Stepper: public motionTMC2130Stepper{
		public:
		angularTMC2120Stepper(int enable_pin, int dir_pin, int step_pin,int cs_pin, int index_pin)
				:motionTMC2130Stepper(enable_pin, int dir_pin, int step_pin,int cs_pin),index_pin(index_pin)
				{
					
				}
				int index(int);//to return 1 when indexer microswitch tripped
			private:
				int index_pin;
};

class linearTMC2120Stepper: public motionTMC2130Stepper{
		public:
		linearTMC2120Stepper(int enable_pin, int dir_pin, int step_pin,int cs_pin, int limit1_pin, int limit2_pin)
						:motionTMC2130Stepper(enable_pin, int dir_pin, int step_pin,int cs_pin),limit1_pin(limit1_pin), limit2_pin(limit2_pin)
						{
						}					
				int limit();//to return 1 when indexer1 microswitch tripped, 2 when indexer2 tripped
			private:
				int limit1_pin;
				int limit2_pin;

}

#endif /* MOTIONTMC2120STEPPER_H */