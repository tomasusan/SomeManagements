#pragma once

template<typename T>
class Singleton {
public:
    Singleton() = default;
    Singleton(Singleton const &) = delete;

    Singleton &operator=(Singleton const &) = delete;

    static T* GetInstance() {
        static T instance;
        return &instance;
    }
};
