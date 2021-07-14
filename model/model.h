#ifndef _MODEL_H_
#define _MODEL_H_

#include "Notification.h"
#include <cstdint>
#include <functional>

class Model : public Notification {
public:
    Model() = default;
    ~Model() = default;

    std::function<void(uint32_t)> get_model_modification() noexcept;
};

#endif // _MODEL_H_
