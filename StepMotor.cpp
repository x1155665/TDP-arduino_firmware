#include "StepMotor.h"
#include "pinDefine.h"
#include "config.h"

stepMotor::stepMotor(char i){
  float tempPos[]=max_pos;
  float tempFr[]=default_feedrate;
  boolean tempDir[]=homing_direction;
  boolean tempHome[]=home_pos;
  boolean tempLogic[]=logic_of_endstop;
  boolean tempSteps[]=steps_per_minimeter;
  int ii=0;
  switch(i){
    case 'X':
      pDIR=X_DIR;
      pSTEP=X_STEP;
      pEN=X_EN;
      endstop_for_homing=ES1;
      ii=0;
      break;
    case 'Y':
      pDIR=Y_DIR;
      pSTEP=Y_STEP;
      pEN=Y_EN;
      ii=1;
      endstop_for_homing=ES2;
      break;
    case 'Z':
      pDIR=Z_DIR;
      pSTEP=Z_STEP;
      pEN=Z_EN;
      ii=2;
      endstop_for_homing=ES3;
      break;
    case 'E':
      pDIR=E_DIR;
      pSTEP=E_STEP;
      pEN=E_EN;
      ii=3;
      endstop_for_homing=ES4;
      break;
    default:
      break;
  }
  maxPos=tempPos[ii];
  feedrate=tempFr[ii];
  homeDIR=tempDir[ii];
  homePos=tempHome[ii];
  steps_per_mm=tempSteps[ii];
  logic_of_ES=tempLogic[ii];
  
  pos=0;
  isHome=0;   
  if (homePos==0) 
  {DIRtoMax=!homeDIR;}
  else
  {DIRtoMax=homeDIR;}
  pinMode(pDIR,1);
  pinMode(pEN,1);
  pinMode(pSTEP,1);
}
float stepMotor::getPos(){
  return pos;
}
float stepMotor::getFeedrate(){
  return feedrate;
}
boolean stepMotor::getIsHome(){
  pinMode(endstop_for_homing,INPUT_PULLUP);
  if(logic_of_ES)
  isHome=digitalRead(endstop_for_homing);
  else
  isHome=!digitalRead(endstop_for_homing);
  return isHome;
}

void stepMotor::toHome(){
  digitalWrite(pDIR,homeDIR);       
  digitalWrite(pEN,0);
  step_delay =1000L/steps_per_mm/feedrate;
  while(!getIsHome())
  {
    oneStep();
  }
  pos=homePos;
}

void stepMotor::setFeedrate(float Feedrate){
  feedrate=Feedrate;   
}

void stepMotor::oneStep(){
  digitalWrite(pSTEP,1);
  delay(step_delay/2);
  digitalWrite(pSTEP,0);
  delay(step_delay/2);
}

void stepMotor::steps(float distance_to_move)
{ 
  int steps_left = abs(distance_to_move)*steps_per_mm;  
  step_delay =1000L/steps_per_mm/feedrate;
  float pos_previous=pos;
  
  // determine direction based on whether distance_to_move is + or -:
  if (distance_to_move > 0) {digitalWrite(pDIR,DIRtoMax);}
  if (distance_to_move < 0) {digitalWrite(pDIR,!DIRtoMax);}
 
  while(steps_left > 0) {
    oneStep();
    pos=pos+1.0/steps_per_mm;  //Since the computational accuracy is limited, this current position is not accurate.
    steps_left--;
    }  
  pos=pos_previous+distance_to_move ;//recorrect the current position
  
}

void stepMotor::toDestination(float destination){
  steps(destination-pos);
}

