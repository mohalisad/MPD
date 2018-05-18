#include <iostream>
#include <time.h>
#include "date.h"
Date::Date(){
  time_t now = time(0);
  int dif=0;
  int second,minute,hour;
  second=now%60;
  minute=(now/60)%60;
  now=now/3600;
  hour=now%24;
  now=now/24;
  dif=(now%(365*4+1));
  year=(now/(365*4+1))*4+1348;
  day=11;
  month=10;
  for(int i=0;i<dif;i++){
    next();
  }
  dayOfWeek=5+now%7;
  std::cout <<dayOfWeek<<'\n'<< year << '/'<<month<<'/'<<day<<std::endl;
  std::cout << hour << ':'<<minute<<':'<<second<<std::endl;
}
void Date::next(){
  day++;
  if(month<7){
    if(day>31){
      day=1;
      month++;
    }
  }else{
    if(month!=12||year%4==3){
      if(day>30){
        day=1;
        month++;
      }
    }else{
      if(day>29){
        day=1;
        month++;
      }
    }
  }
  if(month>12){
    month=1;
    year++;
  }
  dayOfWeek=(dayOfWeek+1)%7;
}
