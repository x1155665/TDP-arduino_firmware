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
    int pDIR;
    int pEN;
    int pSTEP;
    long steps_per_mm;
    long step_delay;
    int endstop_for_homing;
    boolean logic_of_ES;
    
  public:
    float getPos();
    float getFeedrate();
    boolean getIsHome();
    void toPos(float destination,float feedrate);
    void toHome();  
    stepMotor(char i);
    void setFeedrate(float Feedrate);
    void oneStep();
    void steps(float distance_to_move);
    void toDestination(float destination);
};
#endif
