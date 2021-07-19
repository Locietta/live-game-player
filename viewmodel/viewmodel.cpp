#include "viewmodel.h"
#include "../common/Defs.h"

#include <iostream>

using namespace std;
enum { CLICK_ID, RIGHT_CLICK_ID };

function<void(unsigned int)> ViewModel::get_Notification() noexcept {
    return [this](unsigned int id) {
        switch (id) {
        case PropID_ColorMatrix: {
#ifndef NDEBUG
            cerr << "view model receive notification" << endl;
#endif
            trigger(PropID_ColorMatrix);
        } break;
        default: {
        } break;
        }
    };
}

ref_ptr<TwoDMat<bool>> ViewModel::Get2DBoolMat() {
    return m_spModel->Get_Bool2DMat();
}

void ViewModel::LinkToModel(const shared_ptr<Model> &spModel) {
    m_spModel = spModel;
    m_spModel->add(get_Notification());
}

std::function<bool(uint32_t, uint32_t)> ViewModel::get_DrawCmd() {
    return [this](uint32_t row_idx, uint32_t col_idx) { return m_spModel->changeState(row_idx, col_idx); };
}

std::function<bool(void)> ViewModel::get_RandomizeCmd() {
    return [this](void) { return m_spModel->Randomize(); };
}

std::function<bool(void)> ViewModel::get_SingleStepCmd() {
    return [this](void) { return m_spModel->SingleStep(); };
}

std::function<bool(void)> ViewModel::get_ClearCmd() {
    return [this](void) { return m_spModel->Clear(); };
}

// std::function<bool(uint32_t, uint32_t)> ViewModel::get_InitRdmCmd() {
//     return [this](uint32_t height, uint32_t width) { return m_spModel->Initalize_Random(height, width); };
// }

// std::function<bool(int)> ViewModel::get_Run_N_Time_Cmd() {
//     return [this](int times) { return m_spModel->Run(times); };
// }
