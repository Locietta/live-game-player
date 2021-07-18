#ifndef _NOTIFICATION_H_
#define _NOTIFICATION_H_
#include <cstdint>
#include <functional>
#include <vector>

class Notification {
public:
    Notification() = default;
    ~Notification() = default;

    void add(std::function<void(uint32_t)> &&f);
    void trigger(uint32_t id);

    // unused
    void remove();
    void clear();

private:
    std::vector<std::function<void(uint32_t)>> FuncVec;
};

#endif // _NOTIFICATION_H_
