#include "EventManagement.h"

#include <iostream>
#include <ostream>

#pragma region CallBacks without parameters
void EventManagement::AddEventListener(string EventName, const function<void()> &Func) {
    if (!CallBacks.contains(EventName)) {
        vector<function<void()>> NewQueue;
        CallBacks.insert(pair<string, vector<function<void()>>>(EventName, NewQueue));
    }

    CallBacks[EventName].push_back(Func);
}

void EventManagement::DispatchEvent(const string &EventName) {
    if (!CallBacks.contains(EventName)) return;
    for (const auto Callback : CallBacks[EventName]) {
        Callback();
    }
}
#pragma endregion

#pragma region Callbacks with parameters
template<typename ... Args>
void EventManagement::AddEventListener(const string& EventName, const function<void(Args...)> &Func) {
    if (!ParametrizedCallbacks.contains(EventName)) {
        vector<function<void(vector<any>)>> CallBacks;
        ParametrizedCallbacks.insert(pair(EventName, Func));
    }

    ParametrizedCallbacks[EventName].push_back([Func](vector<any> Params) {
        if (sizeof...(Args) != Params.size()) {
            return;
        }
        try {
            [&]<size_t... I>(std::index_sequence<I...>) {
                Func(any_cast<Args>(Params[I])...);
            }(std::index_sequence_for<Args...>{});
        }catch (const bad_any_cast& e) {
            cout << e.what() << endl;
            return;
        }
    });
}

template<typename... Args>
void EventManagement::DispatchEvent(const string& eventName, Args&&... args) {
    if (!ParametrizedCallbacks.contains(eventName)) return;

    vector<any> params;
    (params.push_back(any(forward<Args>(args))), ...);

    for (const auto& callback : ParametrizedCallbacks[eventName]) {
        callback(params);
    }
}
#pragma endregion
