#define X_EN 38
#define X_DIR A1
#define X_STEP A0
#define Y_EN A2
#define Y_DIR A7
#define Y_STEP A6
#define Z_EN A8
#define Z_DIR 48
#define Z_STEP 46
#define E_EN 24
#define E_DIR 28
#define E_STEP 26
#define ES1 3
#define ES2 14
#define ES3 18
#define ES4 19
#define HEATER 42
#define ROLLER 9
#define THERM0 A13

//Switch the control of step motor between arduino and the motherboard of the inkjet printer...,
//A previous showed that there was no need to switch the control of step motor, so I leave it here as an option.
#define controlSwitch 40 
