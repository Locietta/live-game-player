#ifndef _VIEW_H_
#define _VIEW_H_

#include <functional>
#include <cstdint>
#include "Notification.h"

class View {
public:
    View() = default;
    ~View() = default;

    void click_callback(void);

    void set_xx_command(std::function<void (uint32_t)>&& cmd) noexcept;
    std::function<void(uint32_t)> get_Notification() noexcept;

private:
    int graphic_temp = 0;
    std::function<void (uint32_t)> xx_command;
};

#endif // _VIEW_H_
