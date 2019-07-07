# TDP-arduino_firmware

An arduino firmware for a 3D-printer based on injet printing.

This firmware is intended for a project of CDHAW, tognji University and works together with TDP-host(https://github.com/x1155665/TDP-host ). Anyway, it still works well indepently.

Commands supported:
  
  G0 
  
  G28
  
  M104
  
  M105
  
  M119
  
  M114  
  
  The syntax of the supported commands is the same as Marlin's(http://www.marlinfirmware.org/index.php/G-Code_in_Marlin )
  
  Exception:
   
    G0 R1   //turn on spreader
  
    G0 R0   //turn off spreader 


In most cases, this firmware is not as competent as Marlin. However, it's more friendly to the beginners and those who want to make some modifications.
