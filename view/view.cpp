#include "view.h"
#include <iostream>

using namespace std;

enum { CLICK_ID, RIGHT_CLICK_ID };

void View::click_callback(void) {
    cout << "this is a call back" << endl;
    xx_command(114);
}

void View::set_xx_command(function<void(uint32_t)> &&cmd) noexcept {
    xx_command = move(cmd);
}

function<void(unsigned int)> View::get_Notification() noexcept {
    return [this](unsigned int id) {
        switch (id) {
        case CLICK_ID: {
            cout << "view receive notification" << endl;
        } break;
        default: break;
        }
    };
}