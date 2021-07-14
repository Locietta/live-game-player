#include "Notification.h"

void Notification::Add(function<void(uint32_t)> &&f) {
    FuncVec.push_back(move(f));
}

void Notification::Trigger(uint32_t id) {
    for (auto &i : FuncVec) {
        i(id);
    }
}
