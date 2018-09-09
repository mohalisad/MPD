#include <string>

int parseInt(std::string input);
std::string intToString(const int& input);
std::string intToStringSized(const int& input, int fixedSize);
std::string multiString(std::string input , int multi);
std::string charToString(const char& input);
std::string subFromBeg(std::string input,int size);
std::string subFromEnd(std::string input,int size);
int findSubStr(std::string input,std::string sub);
std::string getTag(std::string input,std::string tag);
std::string readAllFromFile(std::string address);
void writeInFile(std::string address,std::string text);
