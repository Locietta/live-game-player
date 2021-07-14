#ifndef _TOTAL_H_
#define _TOTAL_H_
#include <functional>
#include <iostream>
#include <memory>

//#include "Command.h"
#include "Notification.h"

enum { CLICK_ID, RIGHT_CLICK_ID };

template<typename T>
using rf = reference_wrapper<T>;

class View {
public:
    View() = default;
    ~View() = default;
    // void set_command_1(std::shared_ptr<Command>);

    // void click() {
    //     std::cout << "A click" << std::endl;
    //     Trigger(CLICK_ID);
    // }

    void callback(void){ std::cout << "this is a call back" << std::endl; xx_command(114); }

    void set_xx_command(function<void (uint32_t)>&& cmd) {
        xx_command = move(cmd);
    }
    int graphic_temp = 0;


    function<void(unsigned int)> get_Notification() {
        return [this](unsigned int id) {
            switch (id) {
            case CLICK_ID: {
                cout << "view receive notification" << endl;
            } break;
            default: break;
            }
        };
    }

private:
    function<void (uint32_t)> xx_command;
    // std::shared_ptr<Command> command_1;
};



class Model : public Notification {
public:
    Model() = default;
    ~Model() = default;
    
    
    function<void (uint32_t)> get_model_modification(){
        return [this](uint32_t id){
            std::cout << "model update" << std::endl;
            Trigger(id);
        };
    }


};



class ViewModel : public Notification {
public:
    ViewModel() = default;
    ~ViewModel() = default;
    // void bind(std::shared_ptr<Model>);

    // std::shared_ptr<Command> get_command_1(void);
    function<void(unsigned int)> get_Notification() {
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

    function<void (uint32_t)> get_xx_command() {
        return [this] (uint32_t uid) {
            if (uid == 114) {
                std::cout << "view model do sth" << std::endl;
                xx_ModelCmd(0);
            }
        };
    }

    void set_xx_ModelCmd(function<void (uint32_t)>&& cmd) {
        xx_ModelCmd = move(cmd);
    }

private:
    // std::shared_ptr<Model> model;
    // std::shared_ptr<Command> command_1;
    // void dothis();
    int view_data = 0;
    function<void (uint32_t)> xx_ModelCmd;
};

#endif // _TOTAL_H_
