#ifndef DIARY_H
#define DIARY_H

#include <string>
#include <vector>
#include "entry.h"

class Diary{
private:
  std::vector<Entry*> v;
public:
  void readFromText(std::string input);
};

#endif
