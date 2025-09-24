#include <iostream>
#include "EventManagement.h"
#include "TestA.h"
using namespace std;

void TestEvent() {
    const auto Event = EventManagement::GetInstance();
    Event->AddEventListener("TestEvent", []() {
       cout<<"TestEvent Triggered\n";
    });
}

void TestEventParameter() {
    const auto Event = EventManagement::GetInstance();
    Event->AddEventListener("Parameter", function([](int x, int y) {
        cout << x << " " << y << "\n";
    }));
}

int main() {

    TestEventParameter();

    const auto Event = EventManagement::GetInstance();
    Event->DispatchEvent("Parameter", 1, 2);
    return 0;
}