#ifndef _NOTIFICATION_H_
#define _NOTIFICATION_H_
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

#endif // _NOTIFICATION_H_
