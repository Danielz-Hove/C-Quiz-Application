#include<windows.h>
#include "Color_Definations.h"2
void _Colors(int k){
  HANDLE  hconsole;
  hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hconsole,k);
}
void RESET(){
    _Colors(15);
}
void RED(){
    _Colors(4);
}
void LIGHT_RED(){
    _Colors(12);
}
void DARK_BLUE(){
    _Colors(1);
}void LIGHT_BLUE(){
    _Colors(3);
}
void GREEN(){
    _Colors(10);
}
void PURPLE(){
    _Colors(13);
}
void YELLOW(){
    _Colors(6);
}
void CREAM(){
    _Colors(14);
}
void GREY(){
    _Colors(7);
}
void DARK_GREEN(){
    _Colors(2);
}
void BLUE_ISH(){
 _Colors(9);
}
void CREAM_B(){
    _Colors(233);
}

