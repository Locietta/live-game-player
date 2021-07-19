#include "model.h"
#include <cstdint>

Model::Model(size_t height, size_t width)
    : m_TwoDMat(height, width), m_Next2DMat(height, width) {}

constexpr uint32_t rgb_color(uint8_t r, uint8_t g, uint8_t b) { //< ret = (r, g, b, 0x00)
    if (!r && !g && !b) return 0x000000; // black
    else return (uint32_t)(((((r << 8) | g) << 8) | b) << 8);
}

bool Model::init(double True_Prob, uint32_t stageNum) {
    this->True_Prob = True_Prob;
    m_colorStageNum = stageNum;
    
    const uint32_t limit = 0xff, tmp0 = 0x100, tmp1 = 0x200;
    uint32_t divisor = tmp0 * 15 / 8 / (stageNum - 1);

    m_colorList.clear();
    uint32_t partialSum = 0;
    for (uint32_t i = 0; i < stageNum - 1; i++) {
        if (partialSum >= tmp1) {
            m_colorList.push_back(rgb_color(partialSum % tmp1, limit, limit));
        } else if (partialSum >= tmp0) {
            m_colorList.push_back(rgb_color(0x00, partialSum % tmp0, limit));
        } else {
            m_colorList.push_back(rgb_color(0x00, 0x00, partialSum % tmp0));
        }
        partialSum += divisor;
    }
    m_colorList.push_back(rgb_color(0xcc, 0xcc, 0xcc)); // white

    Randomize(True_Prob);
    trigger(PropID_ColorMatrix);
    return true;
}

size_t countBeside(size_t i, size_t j, TwoDMat<uint32_t> &Mat, size_t height, size_t width, uint32_t stageNum) {
    // size_t sizeTmax = std::numeric_limits<size_t>::max();
#define active(i, j) (Mat[i][j] == (stageNum - 1))
    int cnt = 0;
    if (i) {
        cnt += j && active(i - 1, j - 1);
        cnt += active(i - 1, j);
        cnt += (j != width - 1) && active(i - 1, j + 1);
    };

    cnt += j && active(i, j - 1);
    cnt += (j != width - 1) && active(i, j + 1);

    if (i != height - 1) {
        cnt += j && active(i + 1, j - 1);
        cnt += active(i + 1, j);
        cnt += (j != width - 1) && active(i + 1, j + 1);
    }
    return cnt;
};

bool Model::Run(int step) {
    assert(step >= 0);
    auto temp = m_TwoDMat.buf;

    size_t height = m_Next2DMat.m_height;
    size_t width = m_Next2DMat.m_width;
    for (int i = 0; i < step; i++) {
        for (size_t j = 0; j < height; j++) {
            for (size_t k = 0; k < width; k++) {
                auto cnt = countBeside(j, k, m_TwoDMat, height, width, m_colorStageNum);
                if (cnt < 2 || cnt > 3) m_Next2DMat[j][k] = (m_TwoDMat[j][k]) ? m_TwoDMat[j][k] - 1 : 0;
                if (cnt == 2) {
                    if (m_TwoDMat[j][k] == m_colorStageNum - 1)
                        m_Next2DMat[j][k] = m_TwoDMat[j][k];
                    else if (!m_TwoDMat[j][k])
                        m_Next2DMat[j][k] = 0;
                    else
                        m_Next2DMat[j][k] = m_TwoDMat[j][k] - 1;
                }
                if (cnt == 3) m_Next2DMat[j][k] = m_colorStageNum - 1;
            }
        }

        temp = m_TwoDMat.buf;
        m_TwoDMat.buf = m_Next2DMat.buf;
        m_Next2DMat.buf = temp;
    }
    trigger(PropID_ColorMatrix);

    return true;
}

bool Model::Randomize(double True_Prob) {
    bool tmp = Initalize_Random(m_TwoDMat, True_Prob, m_colorStageNum);
    trigger(PropID_ColorMatrix);
    return tmp;
}

bool Model::changeState(size_t row_idx, size_t col_idx) {
    assert(row_idx < MAXSIZE && col_idx < MAXSIZE);
    m_TwoDMat[row_idx][col_idx] = (m_TwoDMat[row_idx][col_idx]) ? 0 : m_colorStageNum - 1;
    // no trigger
    return true;
}

bool Model::Clear() {
    for (int i = 0; i < m_TwoDMat.m_height; i++) {
        for (int j = 0; j < m_TwoDMat.m_width; j++) {
            m_TwoDMat[i][j] = 0;
        }
    }
    trigger(PropID_ColorMatrix);
    return true;
}

/* Private Function Implementations */

bool Initalize_Random(TwoDMat<uint32_t> &m_TwoDMat, double True_Probility, uint32_t stageNum) {
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::bernoulli_distribution dis(True_Probility);

    for (int i = 0; i < m_TwoDMat.m_height; i++) {
        for (int j = 0; j < m_TwoDMat.m_width; j++) {
            m_TwoDMat[i][j] = (dis(gen)) ? stageNum - 1 : 0;
        }
    }
    // Not member method no trigger
    return true;
}

bool Model::Adjust_Random(size_t height, size_t width, double TrueProb) {
    m_TwoDMat.ReInit(height, width);
    m_Next2DMat.ReInit(height, width);
    Initalize_Random(m_TwoDMat, TrueProb, m_colorStageNum);
    trigger(PropID_ColorMatrix);
    return true;
}

bool Model::Load(const std::string &file_Name) {
    std::ifstream ifs(file_Name);
    assert(ifs.is_open());
    size_t height, width;
    ifs >> height >> width;
    m_TwoDMat.ReInit(height, width);
    m_Next2DMat.ReInit(height, width);
    for (size_t i = 0; i < height; i++)
        for (size_t j = 0; j < width; j++) ifs >> m_TwoDMat[i][j];
    trigger(PropID_ColorMatrix);
    return true;
}

bool Model::Save(const std::string &file_Name) {
    std::ofstream ofs(file_Name);
    assert(ofs.is_open());
    size_t height, width;
    height = m_TwoDMat.m_height;
    width = m_TwoDMat.m_width;
    ofs << height << width << "\n";
    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) ofs << static_cast<uint32_t>(m_TwoDMat[i][j]);
        ofs << "\n";
    }
    // No change no trigger
    return true;
}