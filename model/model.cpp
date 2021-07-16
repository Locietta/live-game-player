#include "model.h"
#include "Defs.h"

#include <assert.h>

#include <iostream>
#include <random>

static bool Initalize_Random(TwoDMat<bool> &m_TwoDMat);

Model::Model() : m_TwoDMat(RowCellNum, ColCellNum) {}

bool Model::init() {
    Initalize_Random(m_TwoDMat);
    Trigger(ProperID_ColorMatrix_Update);
	return true;
}

auto countBeside = [](size_t i, size_t j, TwoDMat<bool> &Mat) {
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

bool Model::Run(int step) {
    assert(step >= 0);
    auto temp = m_TwoDMat.buf;

    int cnt;
    for (int i = 0; i < step; i++) {
        for (size_t j = 0; j < m_Next2DMat.m_width; j++) {
            for (size_t k = 0; k < m_Next2DMat.m_height; k++) {
                cnt = countBeside(j, k, m_TwoDMat);
                if (cnt < 2 || cnt > 3) m_Next2DMat[j][k] = false;
                if (cnt == 2) m_Next2DMat[j][k] = m_TwoDMat[j][k];
                if (cnt == 3) m_Next2DMat[j][k] = true;
            }
        }

        temp = m_TwoDMat.buf;
        m_TwoDMat.buf = m_Next2DMat.buf;
        m_Next2DMat.buf = temp;
    }

    return true;
}

bool Model::Draw(size_t row_idx, size_t col_idx) {
    assert(row_idx < MAXSIZE && col_idx < MAXSIZE);
    cout << m_TwoDMat[row_idx][col_idx] << " turn to " << !m_TwoDMat[row_idx][col_idx] << endl;
    m_TwoDMat[row_idx][col_idx] = !m_TwoDMat[row_idx][col_idx];
    return true;
}

unique_ptr<TwoDMat<bool>> Model::Get_Bool2DMat() {
    return unique_ptr<TwoDMat<bool>>(&m_TwoDMat);
}

/* Private Function Implementations */

static bool Initalize_Random(TwoDMat<bool> &m_TwoDMat) {
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(0, 1);

    for (int i = 0; i < m_TwoDMat.m_height; i++) {
        for (int j = 0; j < m_TwoDMat.m_width; j++) {
            m_TwoDMat[i][j] = dis(gen);
        }
    }
    return true;
}