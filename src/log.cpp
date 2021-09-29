#include "log.h"

void printLog(int logLevel, int line, const std::string &s)
{
    switch(logLevel)
    {
        case LEVEL_ERROR:
            std::cerr<<"[ERROR] Line "<<line<<" : "<<s<<std::endl;
            break;
        case LEVEL_WARNING:
            std::cerr<<"[WARNING] Line "<<line<<" : "<<s<<std::endl;
            break;
        case LEVEL_LOG:
            std::cerr<<"[LOG] Line "<<line<<" : "<<s<<std::endl;
            break;
        default:
            std::cerr<<"Unknown log level"<<std::endl;
            break;
    }
}