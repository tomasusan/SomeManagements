#include "TestA.h"

#include <iostream>
#include <ostream>

#include "EventManagement.h"

TestA::TestA() {
    const auto Event = EventManagement::GetInstance();
    Event->AddEventListener("TestEvent", []() {
        cout << "TestA:: Event Triggered\n" << endl;
    });
}
