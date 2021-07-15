#include "viewmodel.h"

#include <iostream>

using namespace std;
enum { CLICK_ID, RIGHT_CLICK_ID };

function<void(unsigned int)> ViewModel::get_Notification() noexcept {
	return [this](unsigned int id) {
		switch (id) {
			case CLICK_ID: {
				cout << "view model receive notification" << endl;
				Trigger(0);
				// model->WhenClick();
			} break;
			case RIGHT_CLICK_ID: {
				cout << "view model right-clicked" << endl;
				// model->
			} break;
			default: {
			} break;
		}
	};
}

function<void(uint32_t)> ViewModel::get_xx_command() noexcept {
	return [this](uint32_t uid) {
		if (uid == 114) {
			std::cout << "view model do sth" << std::endl;
			xx_ModelCmd(0);
		}
	};
}

void ViewModel::set_xx_ModelCmd(function<void(uint32_t)>&& cmd) noexcept {
	xx_ModelCmd = move(cmd);
}

std::function<bool(size_t, size_t)> ViewModel::get_InitRdmCmd() {
	return [this](size_t height, size_t width) { return m_spModel->Initalize_Random(height, width); };
}

std::function<bool(int)> ViewModel::get_Run_N_Time_Cmd() {
	return [this](int times) { return m_spModel->Run(times); };
}

std::function<bool(size_t, size_t)> ViewModel::get_DrawCmd() {
	return [this](size_t row_idx, size_t col_idx) { return m_spModel->Draw(row_idx, col_idx); };
}

shared_ptr<TwoDMat<bool>> ViewModel::Get2DBoolMat() {
	return m_spModel->Get_Bool2DMat();
}

void ViewModel::LinkToModel(const shared_ptr<Model>& spModel) {
	m_spModel = spModel;
	m_spModel->Add(get_Notification());
}