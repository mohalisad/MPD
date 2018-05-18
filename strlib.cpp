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
std::string subFromBeg(std::string input,int size){
  std::string ret;
  for(int i=0;i<size;i++){
    ret=ret+input[i];
  }
  return ret;
}
std::string subFromEnd(std::string input,int size){
  std::string ret;
  for(int i=input.size()-1;i>input.size()-size-1;i--){
    ret=input[i]+ret;
  }
  return ret;
}
