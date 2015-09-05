#ifndef config_h
#define config_h

//Motor config
//实际上E电机未使用
//D40被用于切换arduino和喷墨打印机对y轴电机的控制权
#define default_feedrate {30,30,30,30} //墨盒回零,工作槽,料槽;Unit:mm/s

#define max_pos {1000, 1000, 1000, 1000} //墨盒回零,工作槽,料槽
#define homing_direction {1,1,1,1} //回零方向...墨盒回零,工作槽,料槽
#define home_pos {0, 0, 0, 0} //location of home..0 means that home is at minimum; 1 means that home is at maximum.
#define logic_of_endstop {1,0,0,0}//反转endstop的逻辑
#define steps_per_minimeter {80, 80, 80, 80 } //每走1毫米电机走的步数
#define turnOffHeater 20 ////Turn off the heater when the target temperature lower than this number.

#endif

