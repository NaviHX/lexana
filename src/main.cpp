#include "log.h"
#include "node.h"
#include "keyword.h"

#include <string>
#include <cstdlib>
#include <vector>
#include <map>

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
int charCount = 0;
std::map<std::string, int> tokenCount;

Node *tokenList = NULL;
Node *tokenTail = NULL;
Node *IDtable = NULL;
Node *IDtail = NULL;

void addToken(Node *p);
int insertID(Node *p);
int findID(const std::string &idname);
void printStatisc();
char getChar(FILE *fp);

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
    char c = 0;
    int temp;

    Node *p = NULL;

    do
    {
        switch (state)
        {
        case START:
            word = "";
            c = getChar(fp);
            switch (c)
            {
            case '#':
                printLog(LEVEL_WARNING, line, "Preprocess Instruction Encountered. Plz run preprocessor (cpp) before");
                do
                {
                    if (c == EOF)
                    {
                        state = -1;
                        break;
                    }
                    c = getChar(fp);
                } while (c != '\n');
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
            case ',':
            case ';':
            case ':':
            case '?':
                word += c;
                p = initNode(word, "-", line, -1, NULL);
                addToken(p);
                break;

            case '\n':
                word = "";
                break;

            case '\\':
            case ' ':
                break;

            case EOF:
                state = -1;
                break;

            default:
                printLog(LEVEL_ERROR, line, std::string("Illegal character : ") + c);
                break;
            }
            break;

        case SLASH:
            c = getChar(fp);
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
                addToken(p);
                break;
            case '\n':
            default:
                state = START;
                p = initNode("/", "-", line, -1, NULL);
                addToken(p);
                fseek(fp, -1, SEEK_CUR);
                break;
            }
            break;

        case LINECOMMENT:
            do
            {
                c = getChar(fp);
                if (c == EOF)
                {
                    state = -1;
                    break;
                }
            } while (c != '\n' && state != -1);
            break;

        case COMMENT:
            do
            {
                c = getChar(fp);
                if (c == '*')
                {
                    c = getChar(fp);
                    if (c == '/')
                        state = START;
                }

                if (c == EOF)
                {
                    state = -1;
                }
            } while (state == COMMENT);
            break;

        case ASTERIK:
            c = getChar(fp);
            switch (c)
            {
            case '=':
                word += '=';
                p = initNode(word, "-", line, -1, NULL);
                addToken(p);
                state = START;
                break;

            default:
                p = initNode(word, "-", line, -1, NULL);
                addToken(p);
                fseek(fp, -1, SEEK_CUR);
                state = START;
                break;
            }
            break;

        case EQUAL:
            c = getChar(fp);
            switch (c)
            {
            case '=':
                word += '=';
                p = initNode(word, "-", line, -1, NULL);
                addToken(p);
                state = START;
                break;

            default:
                p = initNode(word, "-", line, -1, NULL);
                addToken(p);
                fseek(fp, -1, SEEK_CUR);
                state = START;
                break;
            }
            break;

        case EXCLAM:
            c = getChar(fp);
            switch (c)
            {
            case '=':
                word += '=';
                p = initNode(word, "-", line, -1, NULL);
                addToken(p);
                state = START;
                break;

            default:
                p = initNode(word, "-", line, -1, NULL);
                addToken(p);
                fseek(fp, -1, SEEK_CUR);
                state = START;
                break;
            }
            break;

        case MINUS:
            c = getChar(fp);
            switch (c)
            {
            case '=':
                word += '=';
                p = initNode(word, "-", line, -1, NULL);
                addToken(p);
                state = START;
                break;

            case '-':
                word += '-';
                p = initNode(word, "-", line, -1, NULL);
                addToken(p);
                state = START;
                break;

            case '>':
                word += '>';
                p = initNode(word, "-", line, -1, NULL);
                addToken(p);
                state = START;
                break;

            default:
                p = initNode(word, "-", line, -1, NULL);
                addToken(p);
                fseek(fp, -1, SEEK_CUR);
                state = START;
                break;
            }
            break;

        case PLUS:
            c = getChar(fp);
            switch (c)
            {
            case '=':
                word += '=';
                p = initNode(word, "-", line, -1, NULL);
                addToken(p);
                state = START;
                break;

            case '+':
                word += '+';
                p = initNode(word, "-", line, -1, NULL);
                addToken(p);
                state = START;
                break;

            default:
                p = initNode(word, "-", line, -1, NULL);
                addToken(p);
                fseek(fp, -1, SEEK_CUR);
                state = START;
                break;
            }
            break;

        case STRING:
            do
            {
                c = getChar(fp);
                if (c == '\"')
                {
                    state = START;
                }
                else if (c == '\n')
                {
                    printLog(LEVEL_ERROR, line, "Require Quote after string");
                    state = START;
                }
                else if (c == '\\')
                {
                    word += c;
                    c = getChar(fp);
                    if (c != '\n')
                        word += c;
                }
                else
                {
                    word += c;
                }
            } while (state == STRING);
            if (state == -1)
            {
                printLog(LEVEL_ERROR, line, "Uncompleted string");
            }
            else
            {
                p = initNode("string", word, line, -1, NULL);
                addToken(p);
            }
            break;

        case LESS:
            c = getChar(fp);
            switch (c)
            {
            case '=':
                word += '=';
                p = initNode(word, "-", line, -1, NULL);
                addToken(p);
                state = START;
                break;

            case '<':
                word += '<';
                p = initNode(word, "-", line, -1, NULL);
                addToken(p);
                state = START;
                break;

            default:
                p = initNode(word, "-", line, -1, NULL);
                addToken(p);
                fseek(fp, -1, SEEK_CUR);
                state = START;
                break;
            }
            break;

        case GREATER:
            c = getChar(fp);
            switch (c)
            {
            case '=':
                word += '=';
                p = initNode(word, "-", line, -1, NULL);
                addToken(p);
                state = START;
                break;

            case '>':
                word += '>';
                p = initNode(word, "-", line, -1, NULL);
                addToken(p);
                state = START;
                break;

            default:
                p = initNode(word, "-", line, -1, NULL);
                addToken(p);
                fseek(fp, -1, SEEK_CUR);
                state = START;
                break;
            }
            break;

        case MOD:
            c = getChar(fp);
            switch (c)
            {
            case '=':
                word += '=';
                p = initNode(word, "-", line, -1, NULL);
                addToken(p);
                state = START;
                break;

            default:
                p = initNode(word, "-", line, -1, NULL);
                addToken(p);
                fseek(fp, -1, SEEK_CUR);
                state = START;
                break;
            }
            break;

        case IDENTIFIER:
            c = getChar(fp);
            switch (c)
            {
            case 'a' ... 'z':
            case 'A' ... 'Z':
            case '0' ... '9':
                word += c;
                break;
            default:
                if (isKeyword(word))
                {
                    p = initNode(word, "-", line, -1, NULL);
                    addToken(p);
                    state = START;
                    break;
                }
                p = initNode("identifier", word, line, -1, NULL);
                temp = findID(word);
                if (temp == -1)
                    p->address = insertID(p);
                else
                    p->address = temp;
                addToken(p);
                fseek(fp, -1, SEEK_CUR);
                state = START;
                break;
            }
            break;

        case NUMBER:
            c = getChar(fp);
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
                addToken(p);
                fseek(fp, -1, SEEK_CUR);
                state = START;
                break;
            }
            break;

        case DOT:
            c = getChar(fp);
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
                addToken(p);
                fseek(fp, -1, SEEK_CUR);
                state = START;
                break;
            }
            break;

        case DECIMAL:
            c = getChar(fp);
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
                addToken(p);
                fseek(fp, -1, SEEK_CUR);
                state = START;
                break;
            }
            break;

        case EXP:
            c = getChar(fp);
            switch (c)
            {
            case '0' ... '9':
                word += c;
                break;
            default:
                p = initNode("number", word, line, -1, NULL);
                addToken(p);
                fseek(fp, -1, SEEK_CUR);
                state = START;
                break;
            }
            break;
        }
    } while (c != EOF);

    printStatisc();

    return 0;
}

/* 
 * 向记号链表中添加记号,输出记号,统计记号数目
 * Node *p 添加的记号指针
 */
void addToken(Node *p)
{
    if (tokenList == NULL)
    {
        tokenList = p;
        tokenTail = p;
    }
    else
    {
        tokenTail->next = p;
        tokenTail = p;
    }
    printNode(p);

    if (tokenCount.find(p->type) == tokenCount.end())
        tokenCount[p->type] = 1;
    else
        tokenCount[p->type]++;
}

/* 
 * 向符号表末尾插入新标识符
 * Node *p 添加的标识符指针
 */
int insertID(Node *p)
{
    if (IDtable == NULL)
    {
        IDtable = p;
        IDtail = p;
        IDcount = 1;
    }
    else
    {
        IDtail->next = p;
        IDtail = p;
        IDcount++;
    }
    return IDcount - 1;
}

/* 
 * 在符号表中查询标识符,查询成功返回索引,否则返回-1
 * const std::string &idname 查询的标识符
 */
int findID(const std::string &idname)
{
    Node *cur = IDtable;
    int id = 0;
    for (; cur != NULL; cur = cur->next)
    {
        if (cur->description == idname)
        {
            return id;
        }
        id++;
    }
    return -1;
}

void printStatisc()
{
    std::cout << "=== Statiscal Data ===" << std::endl;

    for (auto &it : tokenCount)
    {
        std::cout << " " << it.first << " : " << it.second << std::endl;
    }

    std::cout << " Total Lines : " << line + 1 << std::endl;
    std::cout << " Total Chars : " << charCount << std::endl;
}

/* 
 * 获取一个字符,并统计行数与字符数
 * FILE *fp 读取的文件
 */
char getChar(FILE *fp)
{
    char c = fgetc(fp);
    if (c != EOF)
        charCount++;
    if (c == '\n')
        line++;
    return c;
}
