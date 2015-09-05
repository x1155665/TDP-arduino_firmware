#include "Gcode.h"
#include "Mcode.h"
#include "StepMotor.h"
#include "pinDefine.h"
#include "config.h"

stepMotor smX=stepMotor('X');
stepMotor smY=stepMotor('Y');
stepMotor smZ=stepMotor('Z');
stepMotor smE=stepMotor('E');

int targetTemp=60;
boolean heaterOn=false;
  
Gcode::Gcode(String inString){
  code=inString;
}
String Gcode::get(){
  return code;
}

void Gcode::solve(){
  int readPos =1;//指令的阅读点
  String StrCodeNum="";
  for(readPos=1;code[readPos]!=' '&&readPos<code.length();readPos++)
  {
    StrCodeNum= StrCodeNum+code[readPos];
  }
  int codeNum=atoi(StrCodeNum.c_str());
  
  switch (codeNum){                  //根据g代码的内容执行
    case 0 :
      if (readPos>=code.length() ) {break;}
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
  
  //检查是否改feedrate
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
  
 //执行运动 
  while(readPos<code.length()){
  while(code[readPos]==' '){readPos++;}  //跳过空格
  String StrPos="";
  switch(code[readPos]){
    case 'X':
    case 'x':
      for(readPos++;code[readPos]!=' '&&readPos<code.length();readPos++)
      {
        StrPos= StrPos+code[readPos];
      }
      Serial.print("x moves to ");
      Serial.println(atof(StrPos.c_str()));
      if (setFr==1){smX.setFeedrate(atof(StrFr.c_str()));}
      digitalWrite(controlSwitch, 0);
      smX.toDestination(atof(StrPos.c_str()));
      digitalWrite(controlSwitch, 1);
      break;
    case 'Y':
    case 'y':
      for(readPos++;code[readPos]!=' '&&readPos<code.length();readPos++)
      {
        StrPos= StrPos+code[readPos];
      }
      Serial.print("y moves to ");
      Serial.println(atof(StrPos.c_str()));
      if (setFr==1){
        smY.setFeedrate(atof(StrFr.c_str()));
        }
      smY.toDestination(atof(StrPos.c_str()));

      break;
    case 'Z':
    case 'z':
      for(readPos++;code[readPos]!=' '&&readPos<code.length();readPos++)
      {
        StrPos= StrPos+code[readPos];
      }
      Serial.print("z moves to ");
      Serial.println(atof(StrPos.c_str()));
      if (setFr==1){smZ.setFeedrate(atof(StrFr.c_str()));}
      smZ.toDestination(atof(StrPos.c_str()));
      
      break;
    case 'E':
    case 'e':
      for(readPos++;code[readPos]!=' '&&readPos<code.length();readPos++)
      {
        StrPos= StrPos+code[readPos];
      }
      Serial.print("e moves to ");
      Serial.println(atof(StrPos.c_str()));
      if (setFr==1){smE.setFeedrate(atof(StrFr.c_str()));}
      smE.toDestination(atof(StrPos.c_str()));
      break;
    case 'R':
    case 'r':
        if(code[readPos+1]=='1') 
        {
        digitalWrite(ROLLER,1);     
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
  while(code[tempPos]==' '){tempPos++;}
  if(tempPos==code.length()) {
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
      digitalWrite(controlSwitch, 0);
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
  int readPos =1;//指令的阅读点
  String StrCodeNum="";
  for(readPos=1;code[readPos]!=' '&&readPos<code.length();readPos++)
  {
    StrCodeNum= StrCodeNum+code[readPos];
  }
  int codeNum=atoi(StrCodeNum.c_str());
  switch (codeNum){                  //根据M代码的内容执行
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
  pinMode(3,INPUT_PULLUP);
  Serial.print("x MAX endstop status:");
  Serial.println(digitalRead(3));
  Serial.print("y endstop status:");
  Serial.println(smY.getIsHome());
  Serial.print("z endstop status:");
  Serial.println(smZ.getIsHome());
  
  //Serial.print("e endstop status:");
  //Serial.println(smZ.getIsHome());
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
  while(code[readPos]==' '){readPos++;}  //跳过空格
  String StrTemp="";
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
  Serial.print("current temperature:");
  Serial.println(currentTemp);
}
