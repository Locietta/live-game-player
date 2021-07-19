#include "viewmodel.h"

void ViewModel::LinkToModel(const std::shared_ptr<Model> &spModel) {
    m_spModel = spModel;
    m_spModel->add(get_Notification());
}

std::function<bool(uint32_t, uint32_t)> ViewModel::get_DrawCmd() {
    return [this](uint32_t row_idx, uint32_t col_idx) { return m_spModel->changeState(row_idx, col_idx); };
}

std::function<bool()> ViewModel::get_RandomizeCmd() {
    return [this]() { return m_spModel->Randomize(); };
}

std::function<bool()> ViewModel::get_SingleStepCmd() {
    return [this]() { return m_spModel->SingleStep(); };
}

std::function<bool()> ViewModel::get_ClearCmd() {
    return [this]() { return m_spModel->Clear(); };
}

std::function<void(unsigned int)> ViewModel::get_Notification() noexcept {
    return [this](unsigned int id) {
        switch (id) {
        case PropID_ColorMatrix: {
            trigger(PropID_ColorMatrix);
        } break;
        default: {
        } break;
        }
    };
}
