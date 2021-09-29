#ifndef __LOG_H__
#define __LOG_H__

/*
 * Copyright © 2021 Navi.HuangXing. All rights reserved.
 * @author      : Navi.HuangXing 
 * @date        : 2021-09-29
 * @file        : log.h
 * @description : 日志输出
*/

#include <cstdio>
#include <iostream>

#define LEVEL_ERROR 2
#define LEVEL_WARNING 1
#define LEVEL_LOG 0

/* 
 * 在标准错误流打印日志
 * logLevel : 日志等级
 * line : 日志对应源文件的行号
 * s : 输出的日志信息 
 */
void printLog(int logLevel, int line, const std::string &s);

#endif