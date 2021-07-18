#include "Notification.h"
using namespace std;

void Notification::add(function<void(uint32_t)> &&f) {
    FuncVec.push_back((f));
}

void Notification::trigger(uint32_t id) {
    for (const auto &i : FuncVec) {
        i(id);
    }
}
