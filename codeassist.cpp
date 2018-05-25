#include "codeassist.h"
#include "strtoken.h"

#if defined(__APPLE__)||defined(__MACH__)
#include <mach-o/dyld.h>
std::string getPath(){
    char buffer[1024];
    unsigned int size;
    std::string retu="/";
    _NSGetExecutablePath(buffer, &size);
    _NSGetExecutablePath(buffer, &size);
    StringTokenizer tokens(std::string(buffer),"/");
    for(int i=0;i<(int)tokens.size()-4;i++){

        retu+=tokens[i]+"/";
    }
    return retu;
}
#endif
