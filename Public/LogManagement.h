#pragma once
#include "Singleton.h"
#include <string>

enum Level {
    Display = 0,
    Warning = 1,
    Error = 2,
};

/**
 * @author tomasusan
 * @date 2025-09-24
 * @brief 整理格式的日志输出类
 */
class LogManagement : public Singleton<LogManagement>{
public:
    void Display(const std::string &Message, const std::string &LogName = "DefaultLog");
    void Warning(const std::string &Message, const std::string &LogName = "DefaultLog");
    void Error(const std::string &Message, const std::string &LogName = "DefaultLog");

private:
    void PrintHead(Level LogLevel, const std::string &LogName = "DefaultLog");
};

enum Color {
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    YELLOW = 6,
    WHITE = 7,
    GRAY = 8,
    BRIGHT_BLUE = 9,
    BRIGHT_GREEN = 10,
    BRIGHT_CYAN = 11,
    BRIGHT_RED = 12,
    BRIGHT_MAGENTA = 13,
    BRIGHT_YELLOW = 14,
    BRIGHT_WHITE = 15
};
