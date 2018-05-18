#ifndef DATE_H
#define DATE_H

#include <string>

class Date{
private:
  int year;
  int month;
  int day;
  int dayOfWeek;
  void calcDayOfWeek();
public:
  Date();
  Date(int y,int m,int d);
  Date(std::string input);
  void prev();
  void next();
  std::string toString();
  static std::string now();
  static std::string clock();
};
#endif
