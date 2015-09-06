#ifndef config_h
#define config_h

//Motor config
//Actually, E is not used.
//D40 is used to switch control. Learn more in pinDefine.h.
#define default_feedrate {30,30,30,30} //carriage, printbed, feeder; Unit:mm/s
#define max_pos {1000, 1000, 1000, 1000} //carriage, printbed, feeder
#define homing_direction {1,1,1,1} //carriage, printbed, feeder
#define home_pos {0, 0, 0, 0} //location of home..0 means that home is at minimum; 1 means that home is at maximum.
#define logic_of_endstop {1,0,0,0}
#define steps_per_minimeter {80, 80, 80, 80 } 

//Thermo config
#define turnOffHeater 20 ////Turn off the heater when the target temperature lower than this number.

#endif

