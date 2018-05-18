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
  void next();
  std::string toString();
  static std::string now();
};
#endif
