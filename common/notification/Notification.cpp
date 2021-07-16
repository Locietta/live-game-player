#include "Notification.h"

void Notification::Add(function<void(uint32_t)> &&f) {
    FuncVec.push_back((f));
}

void Notification::Trigger(uint32_t id) {
    for (const auto &i : FuncVec) {
        i(id);
    }
}
