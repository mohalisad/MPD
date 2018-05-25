#include "diary.h"
#include "strtoken.h"

void Diary::readFromText(std::string input){
    StringTokenizer tokens(input,"\n\r");
    for(int i=0;i<tokens.size();i++){
        v.push_back(new Entry(tokens[i]));
    }
}
void Diary::addEntry(int num,Date *d,std::string t){
    v.push_back(new Entry(num,d,t));
}
std::string Diary::getEncrypted(){
    std::string retu;
    for(int i=0;i<v.size();i++)retu+=v[i]->getHash()+"\n";
    return retu;
}
Entry* Diary::operator[](int input){
    return v[input];
}

std::vector<Entry*>::size_type Diary::size(){
    return v.size();
}
