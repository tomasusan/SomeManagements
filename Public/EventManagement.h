#pragma once
#include <any>
#include "Singleton.h"
#include <string>
#include <vector>
#include <map>
#include <functional>

using namespace std;

class EventManagement : public Singleton<EventManagement> {
private:
    map<string, vector<function<void()>>> CallBacks;
    map<string, vector<function<void(vector<any>)>>> ParametrizedCallbacks;

public:
    void AddEventListener(string EventName, const function<void()> &Func);
    template<typename... Args>
    void AddEventListener(const string &EventName, const function<void(Args...)> &Func);

    void DispatchEvent(const string &EventName);
    template<typename... Args>
    void DispatchEvent(const string &eventName, Args &&... args);
};
