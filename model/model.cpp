#include "model.h"

#include <assert.h>

#include <iostream>
#include <random>

Model::Model(size_t length, std::function<void(uint32_t, uint32_t, bool)> &&cmd) {
	Set_ChangeColor(move(cmd));
	Initalize_Random(length, length);
}

auto countBeside = [](size_t i, size_t j, shared_ptr<TwoDMat<bool>> MatPtr) {
	TwoDMat<bool>& Mat = *MatPtr;
	size_t sizeTmax = std::numeric_limits<size_t>::max();
	int cnt = 0;
	if (i) {
		cnt += (j) ? Mat[i - 1][j - 1] : 0;
		cnt += Mat[i - 1][j];
		cnt += (j != sizeTmax) ? Mat[i - 1][j + 1] : 0;
	};

	cnt += (j) ? Mat[i][j - 1] : 0;
	cnt += (j != sizeTmax) ? Mat[i][j + 1] : 0;

	if (i != sizeTmax) {
		cnt += (j) ? Mat[i + 1][j - 1] : 0;
		cnt += Mat[i + 1][j];
		cnt += (j != sizeTmax) ? Mat[i + 1][j + 1] : 0;
	}
	return cnt;
};

function<void(uint32_t)> Model::get_model_modification() noexcept {
	return [this](uint32_t id) {
		std::cout << "model update" << std::endl;
		Trigger(id);
	};
}

bool Model::Initalize_Random(size_t height, size_t width) {
	m_TwoDMat = make_shared<TwoDMat<bool>>(height, width);
	m_Next2DMat = make_shared<TwoDMat<bool>>(height, width);

	std::random_device rd;	 // Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd());	 // Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> dis(0, 1);

	for (int i = 0; i < m_TwoDMat->m_height; i++) {
		for (int j = 0; j < m_TwoDMat->m_width; j++) {
			(*m_TwoDMat)[i][j] = dis(gen);
			changecolor(i, j, (*m_TwoDMat)[i][j]);
		}
	}
	//cout << (*m_TwoDMat)[0][0] << endl;

	// Trigger(0);
	return true;
}

bool Model::Run(int step) {
	assert(step >= 0);
	shared_ptr<TwoDMat<bool>> temp;

	int cnt;
	for (int i = 0; i < step; i++) {
		for (size_t j = 0; j < m_Next2DMat->m_width; j++) {
			for (size_t k = 0; k < m_Next2DMat->m_height; k++) {
				cnt = countBeside(j, k, m_TwoDMat);
				if (cnt < 2 || cnt > 3) (*m_Next2DMat)[j][k] = false;
				if (cnt == 2) (*m_Next2DMat)[j][k] = (*m_TwoDMat)[j][k];
				if (cnt == 3) (*m_Next2DMat)[j][k] = true;
			}
		}
		temp = m_TwoDMat;
		m_TwoDMat = m_Next2DMat;
		m_Next2DMat = temp;
	}

	return true;
}

bool Model::Draw(size_t row_idx, size_t col_idx) {
	assert(row_idx < MAXSIZE && col_idx < MAXSIZE);
	cout << (*m_TwoDMat)[row_idx][col_idx] << "turn to" << !(*m_TwoDMat)[row_idx][col_idx] << endl;
	(*m_TwoDMat)[row_idx][col_idx] = ! (*m_TwoDMat)[row_idx][col_idx];
	return true;
}

shared_ptr<TwoDMat<bool>> Model::Get_Bool2DMat() {
	return m_TwoDMat;
}
