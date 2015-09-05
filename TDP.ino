#include "Gcode.h"
#include "Mcode.h"
#include "pinDefine.h"

/*Code supported:
  G0 
  G28
  M104
  M105
  M119
  M114  */
  

boolean stringComplete=false;
String inString="" ;

extern int targetTemp;
extern boolean heaterOn;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13,1);
  pinMode(THERM0,0);
  pinMode(HEATER,1);
  pinMode(controlSwitch,1);
  digitalWrite(controlSwitch,1);
  digitalWrite(HEATER,1);
  pinMode(ROLLER,1);
}

void loop() {
  if (stringComplete){
    Serial.println("received:"+inString);
    stringComplete=false;
    if (inString[0]=='G'||inString[0]=='g'){
      Gcode gc(inString);
      gc.solve();
    }
    if (inString[0]=='M'||inString[0]=='m'){
      Mcode mc(inString);
      mc.solve();
    }
    inString="";
  }
  
//Thermo
  
  float x=analogRead(THERM0)/1024.0*5.0;
  float currentTemp = -1.1851*x*x*x*x*x+15.697*x*x*x*x-80.174*x*x*x+197.95*x*x-267.84*x+298.52;
  if(heaterOn){
    if(currentTemp<(targetTemp-2.5))
    {
        digitalWrite(HEATER,0);     
    }
    else 
      if(currentTemp>(targetTemp+5))
      {
        digitalWrite(HEATER,1);
      }
  }
  else {digitalWrite(HEATER,1);}
}
  
void serialEvent(){ 
    while ( Serial.available()){
      char inchar = Serial.read();
      if (inchar=='\n'){
        stringComplete=true;
      }
      else{
        inString+= (char)inchar;
      }  
  }
}


