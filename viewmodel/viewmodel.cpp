#include "viewmodel.h"

// std::function<bool(uint32_t, uint32_t)> ViewModel::get_InitRdmCmd() {
//     return [this](uint32_t height, uint32_t width) { return m_spModel->Initalize_Random(height, width); };
// }

// std::function<bool(int)> ViewModel::get_Run_N_Time_Cmd() {
//     return [this](int times) { return m_spModel->Run(times); };
// }
// template <typename T>
Fl_Color ViewModel::ColorMat(size_t row_idx, size_t col_idx) {
    return colorList[(*m_spModel->Get_2DMat())[row_idx][col_idx]];
}

// template <typename T>
void ViewModel::LinkToModel(const std::shared_ptr<Model> &spModel) {
    m_spModel = spModel;
    m_spModel->add(get_Notification());

    uint32_t limit = std::numeric_limits<std::uint8_t>::max();
    uint32_t tmp0 = limit + 1;
    uint32_t tmp1 = 2 * tmp0;
    uint32_t tmp = 3 * tmp0;
    uint32_t stageNum = m_spModel->Get_StageNum();
    uint32_t divisor = tmp * 5 / 8 / (stageNum - 1);

    colorList.clear();
    uint32_t partialSum = -divisor;
    for (uint32_t i = 0; i < stageNum - 1; i++) {
        partialSum += divisor;
        if (partialSum >= tmp1) {
            colorList.push_back(fl_rgb_color(partialSum % tmp1, limit, limit));
        } else if (partialSum >= tmp0) {
            colorList.push_back(fl_rgb_color(0, partialSum % tmp0, limit));
        } else {
            colorList.push_back(fl_rgb_color(0, 0, partialSum % tmp0));
        }
    }
    colorList.push_back(fl_rgb_color(255, 255, 255));
}

// template <typename T>
std::function<bool(uint32_t, uint32_t)> ViewModel::get_DrawCmd() {
    return [this](uint32_t row_idx, uint32_t col_idx) { return m_spModel->changeState(row_idx, col_idx); };
}

// template <typename T>
std::function<bool()> ViewModel::get_RandomizeCmd() {
    return [this](void) { return m_spModel->Randomize(); };
}

// template <typename T>
std::function<bool()> ViewModel::get_SingleStepCmd() {
    return [this](void) { return m_spModel->SingleStep(); };
}

// template <typename T>
std::function<bool()> ViewModel::get_ClearCmd() {
    return [this](void) { return m_spModel->Clear(); };
}

// template <typename T>
std::function<void(unsigned int)> ViewModel::get_Notification() noexcept {
    return [this](unsigned int id) {
        switch (id) {
        case PropID_ColorMatrix: {
#ifndef NDEBUG
            std::cerr << "view model receive notification" << std::endl;
#endif
            trigger(PropID_ColorMatrix);
        } break;
        default: {
        } break;
        }
    };
}