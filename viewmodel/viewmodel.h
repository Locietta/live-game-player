#ifndef _VIEWMODEL_H_
#define _VIEWMODEL_H_

#include <functional>
#include <cstdint>
#include "Notification.h"

class ViewModel : public Notification {
public:
    ViewModel() = default;
    ~ViewModel() = default;
    // void bind(std::shared_ptr<Model>);

    std::function<void(uint32_t)> get_Notification() noexcept;
    std::function<void(uint32_t)> get_xx_command() noexcept;
    void set_xx_ModelCmd(std::function<void (uint32_t)>&& cmd) noexcept;

private:
    // std::shared_ptr<Model> model;
    // std::shared_ptr<Command> command_1;
    // void dothis();
    int view_data = 0;
    function<void (uint32_t)> xx_ModelCmd;
};

#endif // _VIEWMODEL_H_
