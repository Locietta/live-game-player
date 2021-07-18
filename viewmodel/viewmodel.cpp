#include "viewmodel.h"
#include "Defs.h"

#include <iostream>

using namespace std;
enum { CLICK_ID, RIGHT_CLICK_ID };

function<void(unsigned int)> ViewModel::get_Notification() noexcept {
    return [this](unsigned int id) {
        switch (id) {
        case PropID_ColorMatrix: {
            cerr << "view model receive notification" << endl;
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

// std::function<bool(uint32_t, uint32_t)> ViewModel::get_InitRdmCmd() {
//     return [this](uint32_t height, uint32_t width) { return m_spModel->Initalize_Random(height, width); };
// }

// std::function<bool(int)> ViewModel::get_Run_N_Time_Cmd() {
//     return [this](int times) { return m_spModel->Run(times); };
// }
