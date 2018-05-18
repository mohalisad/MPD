#ifndef STRTOKEN_H
#define STRTOKEN_H
#include<string>
#include<vector>
class StringTokenizer{
private:
    std::string tokenizers;
    std::vector<std::string>tokens;
    bool isItTokenizer(char input);

    static std::string charToString(char input);
public:
    StringTokenizer(std::string mainString,std::string tokenizerChars);
    std::vector<std::string> getAllTokens();
    std::string operator[](int input);
    std::vector<std::string>::size_type size();
};
#endif
