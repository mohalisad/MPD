#include "exception.h"
Exception::Exception(std::string message){
    msg=message;
}
std::string Exception::getExceptionMessage(){
    return msg;
}
