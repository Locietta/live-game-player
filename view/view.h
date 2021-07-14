#ifndef _VIEW_H_
#define _VIEW_H_

#include <functional>
#include <cstdint>
#include "Notification.h"

enum { CLICK_ID, RIGHT_CLICK_ID, ClickOnCell }; // CLICK_ID, RIGHT_CLICK_ID for test, can be deleted later

class View {
public:
    View() = default;
    ~View() = default;

    void click_callback(); // can be deleted later

    // let command = xxx
    void set_xx_command(std::function<void (uint32_t)>&& cmd) noexcept;
    void set_ClickOnCell_Cmd( std::function< bool (uint32_t, uint32_t)>&& cmd) noexcept;

    // viewmodel notifies view to redraw
    std::function<void(uint32_t)> get_Notification() noexcept;  

protected:
    std::function< bool (uint32_t, uint32_t)> ClickOnCell_Cmd;

    std::function<void (uint32_t)> xx_command;

};

#endif // _VIEW_H_
