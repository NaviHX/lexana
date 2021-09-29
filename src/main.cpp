#include "log.h"
#include "node.h"
#include "keyword.h"

#include <string>
#include <cstdlib>

#define START 0
#define IDENTIFIER 1
#define NUMBER 2
#define DOT 3
#define DECIMAL 4
#define EXP 5
#define SLASH 6
#define LINECOMMENT 7
#define COMMENT 8
#define ASTERIK 9
#define EQUAL 10
#define EXCLAM 11
#define MINUS 12
#define PLUS 13
#define STRING 14
#define LESS 15
#define GREATER 16
#define MOD 17

int IDcount = 0;

Node *tokenList = NULL;
Node *tokenTail = NULL;
Node *IDtable = NULL;
Node *IDtail = NULL;

void insertToken(Node *p);
int insertID(Node *p);
int findID(const std::string &idname);

int state = 0;
int line = 0;

int main(int argc, char *argv[])
{
    FILE *fp = NULL;

    if (argc < 2)
    {
        printLog(LEVEL_ERROR, 0, "Input File Name Needed");
        std::cout << "Usage : lexana <filepath>\n";
        return 0;
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printLog(LEVEL_ERROR, 0, "Open File Error");
        return 0;
    }

    std::string word;
    char c;
    int temp;

    Node *p = NULL;

    do
    {
        switch (state)
        {
        case START:
            word = "";
            c = fgetc(fp);
            switch (c)
            {
            case '#':
                printLog(LEVEL_WARNING, line, "Preprocess Instruction Encountered");
                do
                {
                    if (c == EOF)
                    {
                        state = -1;
                        break;
                    }
                    c = fgetc(fp);
                } while (c != '\n');
                line++;
                break;

            case '/':
                state = SLASH;
                word += '/';
                break;

            case 'a' ... 'z':
            case 'A' ... 'Z':
                state = IDENTIFIER;
                word += c;
                break;

            case '0' ... '9':
                state = NUMBER;
                word += c;
                break;

            case '+':
                state = PLUS;
                word += '+';
                break;

            case '-':
                state = MINUS;
                word += '-';
                break;

            case '*':
                state = ASTERIK;
                word += '*';
                break;

            case '=':
                state = EQUAL;
                word += '=';
                break;

            case '!':
                state = EXCLAM;
                word += '!';
                break;

            case '\"':
                state = STRING;
                break;

            case '<':
                state = LESS;
                word += '<';
                break;

            case '>':
                state = GREATER;
                word += '>';
                break;

            case '%':
                state = MOD;
                word += '%';
                break;

            case '~':
            case '^':
            case '&':
            case '(':
            case ')':
            case '[':
            case ']':
            case '{':
            case '}':
            case '.':
                word += c;
                p = initNode(word, "-", line, -1, NULL);
                insertToken(p);
                break;

            case '\n':
                word = "";
                line++;
                break;

            case '\\':
                break;

            default:
                printLog(LEVEL_ERROR, line, std::string("Illegal character : ") + c);
                break;
            }
            break;

        case SLASH:
            c = fgetc(fp);
            switch (c)
            {
            case '*':
                state = COMMENT;
                word = "";
                break;
            case '/':
                state = LINECOMMENT;
                word = "";
                break;
            case '=':
                word += c;
                state = 0;
                p = initNode(word, "-", line, -1, NULL);
                insertToken(p);
                break;
            case '\n':
                line++;
            default:
                state = START;
                p = initNode("/", "-", line, -1, NULL);
                insertToken(p);
                fseek(fp, -1, SEEK_CUR);
                break;
            }
            break;

        case LINECOMMENT:
            do
            {
                c = fgetc(fp);
                if (c == EOF)
                {
                    state = -1;
                    break;
                }
            } while (c != '\n' && state != -1);
            line++;
            break;

        case COMMENT:
            do
            {
                c = fgetc(fp);
                if (c == '*')
                {
                    c = fgetc(fp);
                    if (c == '/')
                        state = START;
                }

                if (c == '\n')
                    line++;

                if (c == EOF)
                {
                    state = -1;
                }
            } while (state == COMMENT);
            break;

        case ASTERIK:
            c = fgetc(fp);
            switch (c)
            {
            case '=':
                word += '=';
                p = initNode(word, "-", line, -1, NULL);
                insertToken(p);
                state = START;
                break;

            default:
                p = initNode(word, "-", line, -1, NULL);
                insertToken(p);
                fseek(fp, -1, SEEK_CUR);
                state = START;
                break;
            }
            break;

        case EQUAL:
            c = fgetc(fp);
            switch (c)
            {
            case '=':
                word += '=';
                p = initNode(word, "-", line, -1, NULL);
                insertToken(p);
                state = START;
                break;

            default:
                p = initNode(word, "-", line, -1, NULL);
                insertToken(p);
                fseek(fp, -1, SEEK_CUR);
                state = START;
                break;
            }
            break;

        case EXCLAM:
            c = fgetc(fp);
            switch (c)
            {
            case '=':
                word += '=';
                p = initNode(word, "-", line, -1, NULL);
                insertToken(p);
                state = START;
                break;

            default:
                p = initNode(word, "-", line, -1, NULL);
                insertToken(p);
                fseek(fp, -1, SEEK_CUR);
                state = START;
                break;
            }
            break;

        case MINUS:
            c = fgetc(fp);
            switch (c)
            {
            case '=':
                word += '=';
                p = initNode(word, "-", line, -1, NULL);
                insertToken(p);
                state = START;
                break;

            case '-':
                word += '-';
                p = initNode(word, "-", line, -1, NULL);
                insertToken(p);
                state = START;
                break;

            case '>':
                word += '>';
                p = initNode(word, "-", line, -1, NULL);
                insertToken(p);
                state = START;
                break;

            default:
                p = initNode(word, "-", line, -1, NULL);
                insertToken(p);
                fseek(fp, -1, SEEK_CUR);
                state = START;
                break;
            }
            break;

        case PLUS:
            c = fgetc(fp);
            switch (c)
            {
            case '=':
                word += '=';
                p = initNode(word, "-", line, -1, NULL);
                insertToken(p);
                state = START;
                break;

            case '+':
                word += '+';
                p = initNode(word, "-", line, -1, NULL);
                insertToken(p);
                state = START;
                break;

            default:
                p = initNode(word, "-", line, -1, NULL);
                insertToken(p);
                fseek(fp, -1, SEEK_CUR);
                state = START;
                break;
            }
            break;

        case STRING:
            do
            {
                c = fgetc(fp);
                if (c == '\\')
                {
                    word += c;
                    c = fgetc(fp);
                    if (c != '\n')
                        word += c;
                }
                if (c == '\n')
                    line++;
                if (c == EOF)
                    state = -1;
            } while (state == STRING);
            if (state == -1)
            {
                printLog(LEVEL_ERROR, line, "Uncompleted string");
            }
            else
            {
                p = initNode("string", word, line, -1, NULL);
                insertToken(p);
            }
            break;

        case LESS:
            c = fgetc(fp);
            switch (c)
            {
            case '=':
                word += '=';
                p = initNode(word, "-", line, -1, NULL);
                insertToken(p);
                state = START;
                break;

            default:
                p = initNode(word, "-", line, -1, NULL);
                insertToken(p);
                fseek(fp, -1, SEEK_CUR);
                state = START;
                break;
            }
            break;

        case GREATER:
            c = fgetc(fp);
            switch (c)
            {
            case '=':
                word += '=';
                p = initNode(word, "-", line, -1, NULL);
                insertToken(p);
                state = START;
                break;

            default:
                p = initNode(word, "-", line, -1, NULL);
                insertToken(p);
                fseek(fp, -1, SEEK_CUR);
                state = START;
                break;
            }
            break;

        case MOD:
            c = fgetc(fp);
            switch (c)
            {
            case '=':
                word += '=';
                p = initNode(word, "-", line, -1, NULL);
                insertToken(p);
                state = START;
                break;

            default:
                p = initNode(word, "-", line, -1, NULL);
                insertToken(p);
                fseek(fp, -1, SEEK_CUR);
                state = START;
                break;
            }
            break;

        case IDENTIFIER:
            c = fgetc(fp);
            switch (c)
            {
            case 'a' ... 'z':
            case 'A' ... 'Z':
            case '0' ... '9':
                word += c;
                break;
            default:
                if(isKeyword(word))
                {
                    p=initNode(word,"-",line,-1,NULL);
                    insertToken(p);
                    break;
                }
                p = initNode("identifier", word, line, -1, NULL);
                temp = findID(word);
                if (temp == -1)
                    p->address = insertID(p);
                else
                    p->address = temp;
                insertToken(p);
                fseek(fp, -1, SEEK_CUR);
                state = START;
                break;
            }
            break;

        case NUMBER:
            c = fgetc(fp);
            switch (c)
            {
            case '0' ... '9':
                word += c;
                break;
            case '.':
                word += c;
                state = DOT;
                break;
            case 'E':
            case 'e':
                word += c;
                state = EXP;
                break;
            default:
                p = initNode("number", word, line, -1, NULL);
                insertToken(p);
                fseek(fp, -1, SEEK_CUR);
                state = START;
                break;
            }
            break;

        case DOT:
            c = fgetc(fp);
            switch (c)
            {
            case '0' ... '9':
                word += c;
                state = DECIMAL;
                break;
            case 'e':
            case 'E':
                word += c;
                state = EXP;
                break;
            default:
                p = initNode("number", word, line, -1, NULL);
                insertToken(p);
                fseek(fp, -1, SEEK_CUR);
                state = START;
                break;
            }
            break;

        case DECIMAL:
            c = fgetc(fp);
            switch (c)
            {
            case '0' ... '9':
                word += c;
                break;
            case 'e':
            case 'E':
                word += c;
                state = EXP;
                break;
            default:
                p = initNode("number", word, line, -1, NULL);
                insertToken(p);
                fseek(fp, -1, SEEK_CUR);
                state = START;
                break;
            }
            break;

        case EXP:
            c = fgetc(fp);
            switch (c)
            {
            case '0' ... '9':
                word += c;
                break;
            default:
                p = initNode("number", word, line, -1, NULL);
                insertToken(p);
                fseek(fp, -1, SEEK_CUR);
                state = START;
                break;
            }
            break;
        }
    } while (c != EOF);
    
    for(p=tokenList;p!=NULL;p=p->next)
    {
        printNode(p);
    }

    return 0;
}

void insertToken(Node* p)
{
    if(tokenList==NULL)
    {
        tokenList=p;
        tokenTail=p;
    }
    else
    {
        tokenTail->next=p;
        tokenTail=p;
    }
}

int insertID(Node* p)
{
    if(IDtable==NULL)
    {
        IDtable=p;
        IDtail=p;
        IDcount=1;
    }
    else
    {
        IDtail->next=p;
        IDtail=p;
        IDcount++;
    }
    return IDcount;
}

int findID(const std::string& idname)
{
    Node* cur=IDtable;
    int id=0;
    for(;cur!=NULL;cur=cur->next)
    {
        if(cur->description==idname)
        {
            return id;
        }
        id++;
    }
    return -1;
}
