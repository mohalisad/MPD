#ifndef DATE_H
#define DATE_H
class Date{
private:
  int year;
  int month;
  int day;
  int dayOfWeek;
public:
  Date();
  void next();
};
#endif
