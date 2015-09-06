#include "Gcode.h"
#include "Mcode.h"
#include "StepMotor.h"
#include "pinDefine.h"
#include "config.h"

stepMotor smX=stepMotor('X');
stepMotor smY=stepMotor('Y');
stepMotor smZ=stepMotor('Z');
stepMotor smE=stepMotor('E');

int targetTemp=60;   //default target: 60
boolean heaterOn=false;
  
Gcode::Gcode(String inString){
  code=inString;
}
String Gcode::get(){
  return code;
}

void Gcode::solve(){
  int readPos =1;//reading postion
  String StrCodeNum="";
  for(readPos=1;code[readPos]!=' '&&readPos<code.length();readPos++)
  {
    StrCodeNum= StrCodeNum+code[readPos];
  }
  int codeNum=atoi(StrCodeNum.c_str());
  
  switch (codeNum){                  //The codes are executed differently according to the number after 'G'('g').
    case 0 :
      if (readPos>=code.length() ) {break;}  //Illegal,quit solving
      solve0(readPos);
      break;
    case 28:
      solve28(readPos);   
      break;
    default:
      break;     
  }
}

void Gcode::solve0(int readPos){
  
  //Check if the feedrate is changed
  int checkFrPos=readPos;
  boolean setFr=0;
  String StrFr="";
  while(checkFrPos<code.length()){
    if(code[checkFrPos]=='f'||code[checkFrPos]=='F')
      {
        for(checkFrPos++;code[checkFrPos]!=' '&&checkFrPos<code.length();checkFrPos++)
        {
          StrFr= StrFr+code[checkFrPos];
        }
        setFr=1;       
      }
    checkFrPos++;
  }
  
 //execute movement
  while(readPos<code.length()){
  while(code[readPos]==' '){readPos++;}  //skip spacing
  
  String StrPos="";  //store the destination
  switch(code[readPos]){
    case 'X':
    case 'x':
      //get the destination
      for(readPos++;code[readPos]!=' '&&readPos<code.length();readPos++)
      {
        StrPos= StrPos+code[readPos];
      }
      
      Serial.print("x moves to ");
      Serial.println(atof(StrPos.c_str()));
      if (setFr==1){smX.setFeedrate(atof(StrFr.c_str()));}  //set a new feedrate for motor x
      digitalWrite(controlSwitch, 0);       //grant the access to stepper motor x
      smX.toDestination(atof(StrPos.c_str()));
      digitalWrite(controlSwitch, 1);
      break;
      
    case 'Y':
    case 'y':
      //get the destination
      for(readPos++;code[readPos]!=' '&&readPos<code.length();readPos++)
      {
        StrPos= StrPos+code[readPos];
      }
      
      Serial.print("y moves to ");
      Serial.println(atof(StrPos.c_str()));
      if (setFr==1){ smY.setFeedrate(atof(StrFr.c_str()));} //set a new feedrate for motor y
      smY.toDestination(atof(StrPos.c_str()));
      break;
      
    case 'Z':
    case 'z':
      //get the destination
      for(readPos++;code[readPos]!=' '&&readPos<code.length();readPos++)
      {
        StrPos= StrPos+code[readPos];
      }
      
      Serial.print("z moves to ");
      Serial.println(atof(StrPos.c_str()));
      if (setFr==1){smZ.setFeedrate(atof(StrFr.c_str()));} //set a new feedrate for motor z
      smZ.toDestination(atof(StrPos.c_str()));     
      break;
      
    case 'E':
    case 'e':
      //get the destination
      for(readPos++;code[readPos]!=' '&&readPos<code.length();readPos++)
      {
        StrPos= StrPos+code[readPos];
      }
      
      Serial.print("e moves to ");
      Serial.println(atof(StrPos.c_str()));
      if (setFr==1){smE.setFeedrate(atof(StrFr.c_str()));} //set a new feedrate for motor e
      smE.toDestination(atof(StrPos.c_str()));
      break;
      
    case 'R':
    case 'r':
        if(code[readPos+1]=='1') 
        {
        digitalWrite(ROLLER,1);     //The motor for the spreader(roller) is a DC motor.
        }
        if(code[readPos+1]=='0') 
        {
        digitalWrite(ROLLER,0);     
        }
        
    default:
      readPos++;
      break;
  }
  } 
}

void Gcode::solve28(int readPos){
  int tempPos=readPos;
  while(code[tempPos]==' '){tempPos++;}  //skip spacing
  if(tempPos==code.length()) {          //If not assigned, all axises will home.
    smX.toHome();
    smY.toHome();
    smZ.toHome();
    //smE.toHome(); 
    Serial.println("all to home ");
  }
  while(readPos<code.length()){
    while(code[readPos]==' '){readPos++;}
    switch(code[readPos]){
    case 'X':
    case 'x':
      digitalWrite(controlSwitch, 0);   //grant the access to stepper motor x
      smX.toHome();
      Serial.println("x to home ");
      digitalWrite(controlSwitch, 1);
      readPos++;
      break;
      
    case 'Y':
    case 'y':     
      smY.toHome();
      Serial.println("y to home ");
      readPos++;
      break;
      
    case 'Z':
    case 'z':
      smZ.toHome();
      readPos++;
      Serial.println("z to home ");
      break;
      
    case 'E':
    case 'e':
      smE.toHome();
      Serial.println("e to home ");
      readPos++;
      break;
      
    default:
      readPos++;
      break;
  }
  
}
}


//Mcode solving

Mcode::Mcode(String inString){
  code=inString;
}
String Mcode::get(){
  return code;
}
void Mcode::solve(){
  int readPos =1;
  String StrCodeNum="";
  for(readPos=1;code[readPos]!=' '&&readPos<code.length();readPos++)
  {
    StrCodeNum= StrCodeNum+code[readPos];
  }
  int codeNum=atoi(StrCodeNum.c_str());
  switch (codeNum){                   //The codes are executed differently according to the number after 'M'('m').
    case 104 :
      solve104(readPos);
      break;
    case 105:
      solve105(readPos);
      break;
    case 119:
      solve119();
      break;
    case 114:
      solve114();
      break;
    default:
      break;     
  }
}

void Mcode::solve119(){
  Serial.print("x home endstop status:");
  Serial.println(smX.getIsHome());
  pinMode(2,INPUT_PULLUP);
  Serial.print("x MAX endstop status:");   //After printing one slice, the motherboard moves the carriage to x max, and then triggers this endstop.
  Serial.println(digitalRead(2));
  Serial.print("y endstop status:");
  Serial.println(smY.getIsHome());
  Serial.print("z endstop status:");
  Serial.println(smZ.getIsHome());
  
  //Serial.print("e endstop status:");
  //Serial.println(smE.getIsHome());
}

void Mcode::solve114(){
  Serial.print("Current positions: ");
  Serial.print("X:");
  Serial.print(smX.getPos());
  Serial.print(" Y:");
  Serial.print(smY.getPos());
  Serial.print(" Z:");
  Serial.print(smZ.getPos());
  Serial.print(" E:");
  Serial.println(smE.getPos());
   
}
void Mcode::solve104(int readPos){
  while(code[readPos]==' '){readPos++;}  //skip spacing
  String StrTemp="";   //store the string of target temperature
  for (readPos;code[readPos]!=' '&&readPos<code.length();readPos++)
      {
        StrTemp= StrTemp+code[readPos];
      }
  targetTemp=atof(StrTemp.c_str());
  if(targetTemp<turnOffHeater){ heaterOn=false;} 
   else{  heaterOn=true;}
}

void Mcode::solve105(int readPos){
  float x=analogRead(THERM0)/1024.0*5.0;
  float currentTemp = -1.1851*x*x*x*x*x+15.697*x*x*x*x-80.174*x*x*x+197.95*x*x-267.84*x+298.52;
  Serial.print("current temperature:"); //the fitting function of the characteristic curve of the temperature sensor
  Serial.println(currentTemp);
}
