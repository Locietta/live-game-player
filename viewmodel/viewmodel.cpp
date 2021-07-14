#include "viewmodel.h"
#include <iostream>

using namespace std;
enum { CLICK_ID, RIGHT_CLICK_ID };

function<void(unsigned int)> ViewModel::get_Notification() noexcept {
    return [this](unsigned int id) {
        switch (id) {
        case CLICK_ID: {
            cout << "view model receive notification" << endl;
            Trigger(0);
            // model->WhenClick();
        } break;
        case RIGHT_CLICK_ID: {
            cout << "view model right-clicked" << endl;
            // model->
        } break;
        default: {

        } break;
        }
    };
}

function<void(uint32_t)> ViewModel::get_xx_command() noexcept {
    return [this](uint32_t uid) {
        if (uid == 114) {
            std::cout << "view model do sth" << std::endl;
            xx_ModelCmd(0);
        }
    };
}

void ViewModel::set_xx_ModelCmd(function<void(uint32_t)> &&cmd) noexcept {
    xx_ModelCmd = move(cmd);
}