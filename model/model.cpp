#include "model.h"
#include <iostream>
function<void (uint32_t)> Model::get_model_modification() noexcept {
    return [this](uint32_t id){
        std::cout << "model update" << std::endl;
        Trigger(id);
    };
}