#ifndef TOTAL_H
#define TOTAL_H
#include <memory>
#include <iostream>
//#include "Command.h"
#include "Notification.h"

#define CLICK_ID 0

class View: public Notification
{
public:
    View(){}
    ~View(){}
    //void set_command_1(std::shared_ptr<Command>);

    void click(){
        std::cout << "A click" << std::endl;
        Trigger(CLICK_ID);
    }


    int graphic_temp = 0;

private:
    //std::shared_ptr<Command> command_1;
};



class Model
{
public:
    Model(){}
    ~Model(){}
    void WhenClick(){
        cout << "model when click" << endl;
        
    }
};






class ViewModel: public Notification
{
public:
    ViewModel();
    ~ViewModel();
    void bind(std::shared_ptr<Model>);

    //std::shared_ptr<Command> get_command_1(void);
    function<void(unsigned int)> get_command0(){ 
        return [this](unsigned int id) {
            if (id == CLICK_ID) {
                cout << "view model clicked" << endl;
                model->WhenClick();
            }
        };
    }

private:
    std::shared_ptr<Model> model;
    //std::shared_ptr<Command> command_1;
    //void dothis();
    int view_data = 0;

};














#endif