#include "node.h"
#include <cstdlib>
#include <iostream>

Node* initNode(const std::string& type,const std::string& desc, int line,int address,Node* next)
{
    Node* ret=(Node*)malloc(sizeof(Node));
    if(ret==NULL)
        return NULL;
    
    ret->type=type;
    ret->description=desc;
    ret->line=line;
    ret->address=address;
    ret->next=next;

    return ret;
}

void printNode(Node* npt)
{
    std::cout<<"<";
    std::cout<<npt->type<<",";
    std::cout<<npt->description<<",";
    
    if(npt->line!=-1)
        std::cout<<npt->line<<",";
    else
        std::cout<<"-,";
    
    if(npt->address!=-1)
        std::cout<<npt->address<<",";
    else
        std::cout<<"-,";

    std::cout<<std::endl;
}