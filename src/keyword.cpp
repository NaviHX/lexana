#include "keyword.h"
#include <vector>

std::vector<std::string> keyword = {"auto","double","int","struct","break","else","long","switch","case","enum","register",
        "typedef","char","extern","return","union","const","float","short","unsigned","continue","for",
         "signed","void","default","goto","sizeof","volatile","do","while","static","if"};

bool isKeyword(const std::string& s)
{
    for(int i=0;i<keyword.size();i++)
    {
        if(s==keyword[i])
            return true;
    }
    return false;
}