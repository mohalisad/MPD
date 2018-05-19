#include "diary.h"
#include "strtoken.h"

void Diary::readFromText(std::string input){
  StringTokenizer tokens(input,"\n");
  for(int i=0;i<input.size();i++){
    v.push_back(new Entry(tokens[i]));
  }
}
