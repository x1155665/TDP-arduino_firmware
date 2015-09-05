#ifndef Mcode_h
#define Mcode_h
#include <arduino.h>

//cpp file in code.cpp
class Mcode {
   public:
    Mcode(String code); 
    String get();
    void solve();
    void solve105(int readPos);
    void solve104(int readPos);
    void solve119();
    void solve114();
 
  private:
    String code;
 
};
#endif
