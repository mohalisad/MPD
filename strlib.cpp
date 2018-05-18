#include <sstream>
#include "strlib.h"

std::string intToString(int input){
    std::ostringstream myCustomStreamString;
    myCustomStreamString<<input;
    return myCustomStreamString.str();
}
std::string charToString(char input){
  char t[]={input,'\0'};
  return std::string(t);
}
