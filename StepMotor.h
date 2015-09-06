#ifndef StepMotor_h
#define StepMotor_h
#include "arduino.h"
class stepMotor{
  private:
    float pos;
    float feedrate;
    boolean isHome;
    boolean homePos;
    float maxPos;
    boolean homeDIR;
    boolean DIRtoMax;
    int pDIR;     // the pin for DIR
    int pEN;      //The pin for Enable
    int pSTEP;    //The pin for STEP
    long steps_per_mm;
    long step_delay;  //delay time between two steps
    int endstop_for_homing;
    boolean logic_of_ES;
    
  public:
    float getPos();
    float getFeedrate();
    boolean getIsHome();
    //void toPos(float destination,float feedrate);  //move to a new position
    void toHome();        //movw to home
    stepMotor(char i);    
    void setFeedrate(float Feedrate);
    void oneStep();   //move one step
    void steps(float distance_to_move);    //move a certain distance
    void toDestination(float destination);  //move to a new position
};
#endif
