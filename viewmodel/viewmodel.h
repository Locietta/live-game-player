#ifndef _VIEWMODEL_H_
#define _VIEWMODEL_H_

#include "../common/Defs.h"
#include "../common/notification/Notification.h"
#include "../common/ref_ptr.h"
#include "../model/model.h"
#include <FL/Enumerations.H>
#include <cstdint>
#include <functional>
#include <iostream>

enum { CLICK_ID, RIGHT_CLICK_ID };
// template <typename T>
class ViewModel : public Notification {
public:
    ViewModel() = default;
    ~ViewModel() = default;

    void LinkToModel(const std::shared_ptr<Model> &spModel);
    Fl_Color ColorMat(size_t row_idx, size_t col_idx);

    std::function<void(uint32_t)> get_Notification() noexcept;
    ref_ptr<TwoDMat<uint32_t>> Get2DBoolMat() { return m_spModel->Get_2DMat(); } //*Not Boolean Mat!
    ref_ptr<std::vector<Fl_Color>> GetCollerMapping() { return ref_ptr(colorList); }

    std::function<bool(uint32_t, uint32_t)> get_DrawCmd();
    std::function<bool()> get_RandomizeCmd();
    std::function<bool()> get_SingleStepCmd();
    std::function<bool()> get_ClearCmd();
    // std::function<bool(uint32_t, uint32_t)> get_InitRdmCmd();
    // std::function<bool(int)> get_Run_N_Time_Cmd();

private:
    std::vector<Fl_Color> colorList;
    std::shared_ptr<Model> m_spModel;
};

#endif // _VIEWMODEL_H_