#include "entry.h"
#include "strlib.h"
#include "strtoken.h"

#define KEY "entry_key1234"
#define TAG_MODE 0

Cryptor Entry::c;
std::string Entry::userKey;

void Entry::setUserKey(std::string input){
    userKey=input;
}

Entry::Entry(int num,Date *d,std::string t){
    number = num;
    date=d;
    text=t;
    state=ES_UNENCRYPTED;
}

Entry::Entry(std::string input){
    state=ES_UNDECRYPTED;
    hash=input;
}

void Entry::encrypt(std::string key){
#if TAG_MODE==1
    hash= c.encrypt("<entry>"+intToString(number)+"</entry><date>"+date->toString()+"</date><text>"+c.encrypt(text,KEY)+"</text>",key);
#else
    hash= c.encrypt(intToString(number)+" "+date->toString()+" "+c.encrypt(text,KEY),key);
#endif
    state=ES_ENCRYPTED;
}
void Entry::decrypt(){
#if TAG_MODE==1
    std::string unhashed=c.decrypt(hash,userKey);
    number=parseInt(getTag(unhashed,"entry"));
    date=new Date(getTag(unhashed,"date"));
    text=c.decrypt(getTag(unhashed,"text"),KEY);
#else
    StringTokenizer tokens(c.decrypt(hash,userKey)," ");
    number=parseInt(tokens[0]);
    date=new Date(tokens[1]);
    text=c.decrypt(tokens[2],KEY);
#endif
    state=ES_DECRYPTED;
}
void Entry::recrypt(std::string newKey) {
    if(state==ES_UNDECRYPTED)decrypt();
    encrypt(newKey);
}
std::string Entry::getHash(){
    if(state==ES_UNENCRYPTED)encrypt();
    return hash;
}
std::string Entry::getText(){
    if(state==ES_UNDECRYPTED)decrypt();
    return text;
}
std::string Entry::getDate(){
    if(state==ES_UNDECRYPTED)decrypt();
    return date->toString();
}
int Entry::getNumber(){
    if(state==ES_UNDECRYPTED)decrypt();
    return number;
}
void Entry::setText(std::string input){
    text=input;
    state=ES_UNENCRYPTED;
}
void Entry::setDate(std::string input){
    date=new Date(input);
    state=ES_UNENCRYPTED;
}
void Entry::Entry::setNumber(int input){
    number=input;
    state=ES_UNDECRYPTED;
}
