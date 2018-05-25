#ifndef DATE_H
#define DATE_H

#include <string>

class Date{
private:
  int year;
  int month;
  int day;
  int dayOfWeek;
  Date clone();
  void calcDayOfWeek();
  void setToNow(float timezone);
  bool isItKabise();
public:
  Date();
  Date(int y,int m,int d);
  Date(std::string input);
  Date prev();
  Date next();
  void goPrev();
  void goNext();
  std::string toString();
  std::string getDayOfWeek();
  static std::string now();
  static std::string clock();
};
#endif
