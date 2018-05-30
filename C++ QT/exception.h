#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <string>
class Exception{
private:
    std::string  msg;
public:
    Exception(std::string message);
    std::string getExceptionMessage();
};
#endif
