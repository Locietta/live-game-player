#include "Notification.h"

void Notification::Trigger(uint32_t id) {
    for (auto & i : FuncVec) { i(id); }
}
