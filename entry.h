#ifndef ENTRY_H
#define ENTRY_H

#include "date.h"

class Entry{
private:
  int number;
  Date *date;
public:
  std::string text;
  Entry(int num,Date *d,std::string t);
  Entry(std::string input);
  std::string toString();
};

#endif
