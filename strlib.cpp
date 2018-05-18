#include <sstream>
#include "strlib.h"
#include "exception.h"

int parseInt(std::string input){
    bool isItNegative=false;
    int number=0;
    if(input.size()==0)return 0;
    if(input[0]=='-')isItNegative=true;
    for(int i=isItNegative?1:0;(unsigned)i<input.size();i++){
        if(input[i]>='0'&&input[i]<='9'){
            number=number*10+input[i]-'0';
        }else throw Exception("It's not an int number.");
    }
    return isItNegative?-number:number;
}
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
int findSubStr(std::string input,std::string sub){
  bool check;
  for(unsigned i=0;i<input.size();i++){
    check=true;
    for(unsigned j=0;j<sub.size();j++){
      if(input[i+j]!=sub[j]){
        check=false;
        break;
      }
    }
    if(check)return i;
  }
  return -1;
}
std::string getTag(std::string input,std::string tag){
  std::string ret;
  ret=subFromEnd(input,input.size()-findSubStr(input,"<"+tag+">")-tag.size()-2);
  ret=subFromBeg(ret,findSubStr(ret,"</"+tag+">"));
  return ret;
}
