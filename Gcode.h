#ifndef Gcode_h
#define Gcode_h
#include <arduino.h>
 
class Gcode {
   public:
    Gcode(String code); 
    String get();
    void solve();
    void solve0(int readPos);
    void solve28(int readPos);
 
  private:
    String code;
 
};
#endif
