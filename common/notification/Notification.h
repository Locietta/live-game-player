#ifndef NOTIFICATION_H
#define NOTIFICATION_H
#include <cstdint>
#include <functional>
#include <vector>
using namespace std;

class Notification {
public:
    Notification() = default;
    ~Notification() = default;

    void Add(function<void(uint32_t)> &&f);
    void Trigger(uint32_t id);

    // unused
    void Remove();
    void Clear();

private:
    vector<function<void(uint32_t)>> FuncVec;
};

#endif