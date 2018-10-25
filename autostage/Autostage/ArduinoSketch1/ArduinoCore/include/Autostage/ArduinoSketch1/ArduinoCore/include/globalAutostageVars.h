//globalAutostageVars.h
/*
Initializes the library and turns the motor in alternating directions.
*/
#ifndef GLOBAL_VARS
#define GLOBAL_VARS
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
#define SUPERFINE 255
#define FINE 64
#define COURSE 1
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
#define HELP 13
#define GOTOBSY 14
#define INFO 15

bool dir = true;
byte val = 0;
bool switcher = false;
bool inmove = false;
long previousMillis;
long interval = 1000;
struct serialReturn 
  {
    bool move;
    int responce,lin,ang;
  };
int serialResponder(int);

#endif