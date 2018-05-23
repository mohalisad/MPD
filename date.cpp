#include <time.h>
#include "date.h"
#include "strlib.h"
#include "strtoken.h"

time_t getLocalTime(float timezone){
  time_t now = time(0);
  now+=3600*timezone;
  return now;
}

Date Date::clone(){
  Date d;
  d.dayOfWeek=dayOfWeek;
  d.day=day;
  d.month=month;
  d.year=year;
  return d;
}
void Date::calcDayOfWeek(){
  int monthDays=(month-1)*31-(month<8?0:month-7);
  dayOfWeek=(year+year/4+day+monthDays)%7;
}
void Date::setToNow(float timezone){
  time_t now = getLocalTime(timezone);
  int dif=0;
  now=now/3600;
  now=now/24;
  dif=(now%(365*4+1));
  year=(now/(365*4+1))*4+1348;
  day=11;
  month=10;
  for(int i=0;i<dif;i++){
    goNext();
  }
  dayOfWeek=5+now%7;
}

Date::Date(){
  setToNow(3.5);
  if(month<7)setToNow(4.5);
}
Date::Date(int y,int m,int d){
  year=y;
  month=m;
  day=d;
  calcDayOfWeek();
}
Date::Date(std::string input){
  StringTokenizer tokens(input,"/");
  year=parseInt(tokens[0]);
  month=parseInt(tokens[1]);
  day=parseInt(tokens[2]);
  calcDayOfWeek();
}
void Date::goNext(){
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
void Date::goPrev(){
  day--;
  if(day==0){
    day=31;
    month--;
    if(month==0){
      month=12;
      year--;
    }
    if(month>6){
      day--;
    }
    if(month==12&&year%4!=3){
      day--;
    }
    dayOfWeek=(dayOfWeek-1)%7;
  }
}
Date Date::prev(){
  Date d=clone();
  d.goPrev();
  return d;
}
Date Date::next(){
  Date d=clone();
  d.goNext();
  return d;
}
std::string Date::toString(){
  std::string retu;
  retu= intToString(year) + "/"+intToString(month)+"/"+intToString(day);
  return retu;
}
std::string Date::now(){
  Date d;
  return d.toString()+" "+Date::clock();
}
std::string Date::clock(){
  time_t now = getLocalTime(Date().month<7?4.5:3.5);
  int second,minute,hour;
  second=now%60;
  minute=(now/60)%60;
  hour=(now/3600)%24;
  return intToString(hour)+":"+intToString(minute)+":"+intToString(second);
}
