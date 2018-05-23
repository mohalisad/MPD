#include "diary.h"
#include "strtoken.h"

void Diary::readFromText(std::string input){
  StringTokenizer tokens(input,"\n");
  for(int i=0;i<input.size();i++){
    v.push_back(new Entry(tokens[i]));
  }
}
void Diary::addEntry(int num,Date *d,std::string t){
    v.push_back(new Entry(num,d,t));
}
std::string Diary::getEncrypted(){
    std::string retu;
    for(int i=0;i<v.size();i++)retu+=v[i]->getHash();
    return retu;
}
