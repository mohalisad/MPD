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
  void addEntry(int num,Date *d,std::string t);
  std::string getEncrypted();
  Entry* operator[](int input);
  std::vector<Entry*>::size_type size();
};

#endif
