#include <time.h>
#include "date.h"
#include "strlib.h"
#include "strtoken.h"
#include "codeassist.h"
#include "exception.h"

time_t getLocalTime(float timezone){
    time_t now = time(0);
    now+=(long)(timezone*3600);
    return now;
}

Date Date::clone() const{
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
    dayOfWeek=(5+now)%7;
}
int Date::yearLength(int year) const{
    int arr[]={1,5,9,13,17,22,26,30};
    return getIndex<int>(arr,8,year%33)!=-1?366:365;
}
int Date::monthLength(int year,int month) const{
    if(month<7)return 31;
    if(month<12||yearLength(year) == 366)return 30;
    return 29;
}
int Date::daysFromStart() const{
    int days = day;
    for(int i=1;i<month;i++){
        days+=monthLength(year,i);
    }
    return days;
}
int Date::daysToEnd() const{
    return yearLength(year)-daysFromStart();
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
    if(tokens.size()!=3)throw Exception("Date string is invalid");
    year=parseInt(tokens[0]);
    month=parseInt(tokens[1]);
    day=parseInt(tokens[2]);
    calcDayOfWeek();
}
void Date::goNext(){
    day++;
    if(day>monthLength(year,month)){
        day = 1;
        month++;
        if(month>12){
            month=1;
            year++;
        }
    }
    dayOfWeek=(dayOfWeek+1)%7;
}
void Date::goPrev(){
    day--;
    if(day==0){
        month--;
        if(month == 0){
            month = 12;
            year--;
        }
        day = monthLength(year,month);
    }
    dayOfWeek=(dayOfWeek-1)%7;
}
Date Date::prev() const{
    Date d=clone();
    d.goPrev();
    return d;
}
Date Date::next() const{
    Date d=clone();
    d.goNext();
    return d;
}
std::string Date::toString() const{
    std::string retu;
    retu= intToString(year) + "/"+intToStringSized(month,2)+"/"+intToStringSized(day,2);
    return retu;
}
std::string Date::getDayOfWeek() const{
    switch (dayOfWeek) {
    case 0:
        return "شنبه";
    case 1:
        return "یک شنبه";
    case 2:
        return "دوشنبه";
    case 3:
        return "سه شنبه";
    case 4:
        return "چهارشنبه";
    case 5:
        return "پنج شنبه";
    case 6:
        return "جمعه";
    }
    throw Exception("DayOfWeek is wrong");
}
bool Date::operator<(const Date &other)const{
    if(this->year < other.year)return true;
    else if(this->year > other.year)return false;
    if(this->month < other.month)return true;
    else if(this->month > other.month)return false;
    if(this->day < other.day)return true;
    else return false;
}
bool Date::operator>(const Date &other)const{
    return other<(*this);
}
bool Date::operator==(const Date &other)const{
    return other.day==this->day && other.month==this->month && other.day==this->day;
}
int  Date::operator-(const Date &other)const{
    const Date *max,*min;
    bool neg;
    int dif;
    if(this->year == other.year){
        return this->daysFromStart()-other.daysFromStart();
    }
    if((*this)>other){
        max = this;
        min = &other;
        neg = false;
    }else{
        max = &other;
        min = this;
        neg = true;
    }
    dif = min->daysToEnd()+max->daysFromStart();
    for(int i=min->year+1;i<max->year;i++){
        dif += yearLength(i);
    }
    return neg?-dif:dif;
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
    return intToStringSized(hour,2)+":"+intToStringSized(minute,2)+":"+intToStringSized(second,2);
}
