#ifndef _VIEWMODEL_H_
#define _VIEWMODEL_H_

#include <cstdint>
#include <functional>

#include "./../model/model.h"
// VM must know the model's definition, and teacher does so
#include <any>

#include "./../common/notification/Notification.h"

class ViewModel : public Notification {
public:
    ViewModel() = default;
    ~ViewModel() = default;

    std::function<void(uint32_t)> get_Notification() noexcept;

    std::function<bool(uint32_t, uint32_t)> get_InitRdmCmd();
    std::function<bool(int)> get_Run_N_Time_Cmd();
    std::function<bool(uint32_t, uint32_t)> get_DrawCmd();

    unique_ptr<TwoDMat<bool>> Get2DBoolMat();
    void LinkToModel(const shared_ptr<Model> &spModel);

private:
    shared_ptr<Model> m_spModel;
};

#endif // _VIEWMODEL_H_
