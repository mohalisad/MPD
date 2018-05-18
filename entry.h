#ifndef ENTRY_H
#define ENTRY_H
#include "date.h";
class Entry{
private:
  int number;
  Date *date;
  std::string text;
public:
  std::string toString();
};
std::string toString(){

}
#endif
