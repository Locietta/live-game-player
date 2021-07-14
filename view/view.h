#ifndef _VIEW_H_
#define _VIEW_H_

#include <functional>
#include <cstdint>
#include "GameGUI.h"
#include "Notification.h"

class View {
public:
    View() = default;
    ~View() = default;

    void click_callback();

    // let command = xxx
    void set_xx_command(std::function<void (uint32_t)>&& cmd) noexcept;

    // viewmodel notifies view to redraw
    std::function<void(uint32_t)> get_Notification() noexcept;  

private:
    GameGUI GUI;

    std::function<void (uint32_t)> xx_command;
};

#endif // _VIEW_H_
