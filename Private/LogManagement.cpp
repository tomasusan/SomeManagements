//
// Created by admin on 25-9-24.
//

#include "LogManagement.h"
#include <iostream>
#include <windows.h>

/**
 * @author tomasusan
 * @date 2025-09-24
 * @brief 级别：一般消息
 * @param Message 日志信息
 * @param LogName 日志分类
 */
void LogManagement::Display(const std::string &Message, const std::string &LogName) {
    PrintHead(Level::Display, LogName);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
    std::cout << Message << "\n";
}

/**
 * @author tomasusan
 * @date 2025-09-24
 * @brief 级别：警告
 * @param Message 日志信息
 * @param LogName 日志分类
 */
void LogManagement::Warning(const std::string &Message, const std::string &LogName) {
    PrintHead(Level::Warning, LogName);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
    std::cout << Message << "\n";
}

/**
 * @author tomasusan
 * @date 2025-09-24
 * @brief 级别：错误
 * @param Message 日志信息
 * @param LogName 日志分类
 */
void LogManagement::Error(const std::string &Message, const std::string &LogName) {
    PrintHead(Level::Error, LogName);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
    std::cout << Message << "\n";
}

/**
 * @author tomasusan
 * @date 2025-09-24
 * @brief 创建日志头
 * @param LogLevel 日志级别
 * @param LogName 日志分类
 */
void LogManagement::PrintHead(const Level LogLevel, const std::string &LogName) {
    Color LogColor = WHITE;
    std::string LogType = "Unknown";
    switch (LogLevel) {
        case Level::Display:
            LogColor = WHITE;
            LogType = "Display";
            break;
        case Level::Warning:
            LogColor = YELLOW;
            LogType = "Warning";
            break;
        case Level::Error:
            LogColor = RED;
            LogType = "Error";
            break;
        default:
            LogColor = GRAY;
            LogType = "Unknown";
            break;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
    std::cout << "[" + LogName + "] ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LogColor);
    std::cout << LogType + ": ";
}
