#ifndef _VIEWMODEL_H_
#define _VIEWMODEL_H_

#include "../common/Defs.h"
#include "../common/notification/Notification.h"
#include "../common/ref_ptr.h"
#include "../model/model.h"
#include <cstdint>
#include <functional>
#include <iostream>

class ViewModel : public Notification {
public:
    ViewModel() = default;
    ~ViewModel() = default;

    void LinkToModel(const std::shared_ptr<Model> &spModel);

    std::function<void(uint32_t)> get_Notification() noexcept;
    ref_ptr<TwoDMat<uint32_t>> Get2DBoolMat() { return m_spModel->Get_2DMat(); } //*Not Boolean Mat!
    auto GetColorMapping() { return ref_ptr(m_spModel->Get_ColorMapping()); }

    std::function<bool(uint32_t, uint32_t)> get_DrawCmd();
    std::function<bool()> get_RandomizeCmd();
    std::function<bool()> get_SingleStepCmd();
    std::function<bool()> get_ClearCmd();

private:
    std::shared_ptr<Model> m_spModel;
};

#endif // _VIEWMODEL_H_
