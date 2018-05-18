#ifndef DATE_H
#define DATE_H

#include <string>

class Date{
private:
  int year;
  int month;
  int day;
  int dayOfWeek;
public:
  Date();
  Date(int y,int m,int d);
  void prev();
  void next();
  std::string toString();
  static std::string now();
};
#endif
