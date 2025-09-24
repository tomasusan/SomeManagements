//
// Created by admin on 25-9-24.
//

#include "LogManagement.h"
#include <iostream>
#include <windows.h>

void LogManagement::Display(const std::string &Message, const std::string &LogName) {
    PrintHead(Level::Display, LogName);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
    std::cout << Message << "\n";
}

void LogManagement::Warning(const std::string &Message, const std::string &LogName) {
    PrintHead(Level::Warning, LogName);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
    std::cout << Message << "\n";
}

void LogManagement::Error(const std::string &Message, const std::string &LogName) {
    PrintHead(Level::Error, LogName);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
    std::cout << Message << "\n";
}

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
