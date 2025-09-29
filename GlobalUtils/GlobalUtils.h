#pragma once

#include <iostream>
using namespace std;

class GlobalUtils {
    public:
    static string String(const int number) {
        return std::to_string(number);
    }

    static string String(const long number) {
        return std::to_string(number);
    }

};