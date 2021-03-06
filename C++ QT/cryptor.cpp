#include "cryptor.h"
#include "date.h"
#include "strlib.h"
#include "codeassist.h"

#define _KEY "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!?"
#define _KEY_LENGTH 64

#define SALT_LENGTH 16
#define MULTIPLY 1.2
#define DISORDER_RATE 6

Cryptor::Cryptor():r(Date::now()){}

std::string Cryptor::randomString(const int& length){
    std::string retu;
    for(int i=0;i<length;i++){
        retu+=charToString(_KEY[r.generate()%_KEY_LENGTH]);
    }
    return retu;
}
int* Cryptor::makeDisorderMoves(const int& length,const std::string& key){
    int loopCount=DISORDER_RATE*length*2;
    int *arr=new int[loopCount];
    Random ran(key);
    for(int i=0;i<loopCount;i++){
        arr[i]=ran.generate()%length;
    }
    return arr;
}
int* Cryptor::makeDisorderArray(const int& length,const int* disorderMoves){
    int c;
    int loopCount=DISORDER_RATE*length*2;
    int* ret=new int[length];
    for(int i=0;i<length;i++){
        ret[i]=i;
    }
    for(int i=0;i<loopCount;i+=2){
        c=ret[disorderMoves[i]];
        ret[disorderMoves[i]]=ret[disorderMoves[i+1]];
        ret[disorderMoves[i+1]]=c;
    }
    return ret;
}
int Cryptor::bitSet(const char& input,const int& position,const bool& toWhat){
    int pow2=1;
    for(int i=0;i<position;i++)pow2*=2;
    if((input&pow2)==toWhat)return input;
    if(toWhat){
        return  input|pow2;
    }else{
        return input&(255-pow2);
    }
}
bool Cryptor::bitGet(const char& input,const int& position){
    int pow2=1;
    for(int i=0;i<position;i++)pow2*=2;
    return input&pow2;
}
int Cryptor::getPossition(const char& input){
    return getIndex<char>(_KEY,_KEY_LENGTH,input);
}
std::string Cryptor::encrypt(std::string input,std::string key){
    std::string retu,salt;
    int *disorderArray,*disorderMoves;
    char *chars;
    int pointer=0,length=MULTIPLY*(input.size()+1)*8;
    length=length+6-length%6;
    salt =randomString(SALT_LENGTH);
    disorderMoves=makeDisorderMoves(length,key+salt);
    disorderArray=makeDisorderArray(length,disorderMoves);
    chars=new char[length/6];
    for(int i=0;i<length/6;i++){
        chars[i]=0;
    }
    for(unsigned i=0;i<input.size();i++){
        for(int j=1;j<256;j=j*2){
            chars[disorderArray[pointer]/6]=bitSet(chars[disorderArray[pointer]/6],disorderArray[pointer]%6,input[i]&j);
            pointer++;
        }
    }
    for(int j=1;j<256;j=j*2){
        chars[disorderArray[pointer]/6]=bitSet(chars[disorderArray[pointer]/6],disorderArray[pointer]%6,0);
        pointer++;
    }
    for(;pointer<length;pointer++){
        chars[disorderArray[pointer]/6]=bitSet(chars[disorderArray[pointer]/6],disorderArray[pointer]%6,r.generate()%2);
    }
    for(int i=0;i<length/6;i++){
        retu+=_KEY[(int)chars[i]];
    }
    delete disorderArray;
    delete disorderMoves;
    return retu+salt;
}
std::string Cryptor::decrypt(std::string input,std::string key){
    int *disorderArray,*disorderMoves;
    char *chars;
    std::string ret;
    char temp;
    int length;
    std::string salt=subFromEnd(input,SALT_LENGTH);
    input = subFromBeg(input,input.size()-SALT_LENGTH);
    length=input.size()*6;
    disorderMoves=makeDisorderMoves(length,key+salt);
    disorderArray=makeDisorderArray(length,disorderMoves);
    chars=new char[length/6];
    for(int i=0;i<length/6;i++){
        chars[i]=getPossition(input[i]);
    }
    int pointer=0;
    while(pointer<length){
        temp=0;
        for(int j=0;j<8;j++){
            temp=bitSet(temp,j,bitGet(chars[disorderArray[pointer]/6],disorderArray[pointer]%6));
            pointer++;
            if(pointer==length)break;
        }
        if(temp==0)break;
        ret+=charToString(temp);
    }
    delete disorderArray;
    delete disorderMoves;
    return ret;
}
