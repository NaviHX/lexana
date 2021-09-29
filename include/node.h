#ifndef __NODE_H__
#define __NODE_H__

#include <string>

struct Node
{
    std::string type;
    std::string description;
    int line;
    int address;

    Node* next;
};

Node* initNode(const std::string& type,const std::string& desc, int line,int address,Node* next);
void printNode(Node* npt);

#endif