#ifndef DATE_H
#define DATE_H

#include <string>

class Date{
private:
  int  year;
  int  month;
  int  day;
  int  dayOfWeek;
  Date clone() const;
  void calcDayOfWeek();
  void setToNow(float timezone);
  int  yearLength(int year) const;
  int  monthLength(int year,int month) const;
  int  daysFromStart() const;
  int  daysToEnd() const;
public:
  Date();
  Date(int y,int m,int d);
  Date(std::string input);
  void goPrev();
  void goNext();
  Date prev() const;
  Date next() const;
  std::string toString() const;
  std::string getDayOfWeek() const;
  bool operator<(const Date &other)const;
  bool operator>(const Date &other)const;
  bool operator==(const Date &other)const;
  int  operator-(const Date &other)const;
  static std::string now();
  static std::string clock();
};
#endif
