#include "model.h"

Model::Model(size_t height, size_t width)
    : m_TwoDMat(height, width), m_Next2DMat(height, width), m_Color2DMat(height, width),
      m_NextColor2DMat(height, width) {}

bool Model::init(double True_Prob) {
    this->True_Prob = True_Prob;
    Randomize(True_Prob);
    trigger(PropID_ColorMatrix);
    return true;
}

size_t countBeside(size_t i, size_t j, TwoDMat<bool> &Mat, size_t height, size_t width) {
    // size_t sizeTmax = std::numeric_limits<size_t>::max();
    int cnt = 0;
    if (i) {
        cnt += (j) ? Mat[i - 1][j - 1] : 0;
        cnt += Mat[i - 1][j];
        cnt += (j != width - 1) ? Mat[i - 1][j + 1] : 0;
    };

    cnt += (j) ? Mat[i][j - 1] : 0;
    cnt += (j != width - 1) ? Mat[i][j + 1] : 0;

    if (i != height - 1) {
        cnt += (j) ? Mat[i + 1][j - 1] : 0;
        cnt += Mat[i + 1][j];
        cnt += (j != width - 1) ? Mat[i + 1][j + 1] : 0;
    }
    return cnt;
};

bool Model::Adjust_Random(size_t height, size_t width, double TrueProb) {
    m_TwoDMat.ReInit(height, width);
    m_Next2DMat.ReInit(height, width);
    Initalize_Random(m_TwoDMat, TrueProb);
    trigger(PropID_ColorMatrix);
    return true;
}

bool Model::Load(std::string &file_Name) {
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

bool Model::Save(std::string &file_Name) {
    std::ofstream ofs(file_Name);
    assert(ofs.is_open());
    size_t height, width;
    height = m_TwoDMat.m_height;
    width = m_TwoDMat.m_width;
    ofs << height << width << "\n";
    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) ofs << static_cast<int>(m_TwoDMat[i][j]);
        ofs << "\n";
    }
    // No change no trigger
    return true;
}

bool Model::Clear() {
    for (int i = 0; i < m_TwoDMat.m_height; i++) {
        for (int j = 0; j < m_TwoDMat.m_width; j++) {
            m_TwoDMat[i][j] = false;
        }
    }
    trigger(PropID_ColorMatrix);
    return true;
}

bool Model::Run(int step) {
    assert(step >= 0);
    auto temp = m_TwoDMat.buf;

    int cnt;
    size_t height = m_Next2DMat.m_height;
    size_t width = m_Next2DMat.m_width;
    for (int i = 0; i < step; i++) {
        for (size_t j = 0; j < height; j++) {
            for (size_t k = 0; k < width; k++) {
                cnt = countBeside(j, k, m_TwoDMat, height, width);
                if (cnt < 2 || cnt > 3) m_Next2DMat[j][k] = false;
                if (cnt == 2) m_Next2DMat[j][k] = m_TwoDMat[j][k];
                if (cnt == 3) m_Next2DMat[j][k] = true;
            }
        }

        temp = m_TwoDMat.buf;
        m_TwoDMat.buf = m_Next2DMat.buf;
        m_Next2DMat.buf = temp;
    }
    trigger(PropID_ColorMatrix);

    return true;
}

bool Model::changeState(size_t row_idx, size_t col_idx) {
    assert(row_idx < MAXSIZE && col_idx < MAXSIZE);
    m_TwoDMat[row_idx][col_idx] = !m_TwoDMat[row_idx][col_idx];
    // no trigger
    return true;
}

ref_ptr<TwoDMat<bool>> Model::Get_Bool2DMat() {
    return ref_ptr<TwoDMat<bool>>(&m_TwoDMat);
}

/* Private Function Implementations */

bool Initalize_Random(TwoDMat<bool> &m_TwoDMat, double True_Probility) {
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::bernoulli_distribution dis(True_Probility);

    for (int i = 0; i < m_TwoDMat.m_height; i++) {
        for (int j = 0; j < m_TwoDMat.m_width; j++) {
            m_TwoDMat[i][j] = dis(gen);
        }
    }
    // Not member method no trigger
    return true;
}

bool Initalize_Random(TwoDMat<uint32_t> &m_TwoDMat, double True_Probility) {
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::bernoulli_distribution dis(True_Probility);

    for (int i = 0; i < m_TwoDMat.m_height; i++) {
        for (int j = 0; j < m_TwoDMat.m_width; j++) {
            m_TwoDMat[i][j] = 0xffffff00 * dis(gen);
        }
    }
    // Not member method no trigger
    return true;
}

// size_t countBeside(size_t i, size_t j, TwoDMat<uint32_t> &Mat, size_t height, size_t width, size_t stageNum) {
//     // size_t sizeTmax = std::numeric_limits<size_t>::max();
//     int cnt = 0;
//     if (i) {
//         cnt += (j && Mat[i - 1][j - 1] == (stageNum - 1)) ? stageNum - 1 : 0;
//         cnt += Mat[i - 1][j];
//         cnt += (j != width - 1) ? Mat[i - 1][j + 1] : 0;
//     };

//     cnt += (j) ? Mat[i][j - 1] : 0;
//     cnt += (j != width - 1) ? Mat[i][j + 1] : 0;

//     if (i != height - 1) {
//         cnt += (j) ? Mat[i + 1][j - 1] : 0;
//         cnt += Mat[i + 1][j];
//         cnt += (j != width - 1) ? Mat[i + 1][j + 1] : 0;
//     }
//     return cnt;
// };

bool Model::init_Color(double True_Prob, uint32_t stageNum) {
    this->True_Prob = True_Prob;
    Randomize_Color(True_Prob);

    assert(!((stageNum - 1) % 3));
    m_colorStageNum = stageNum;

    trigger(PropID_ColorMatrix);
    return true;
}

bool Model::Run_Color(int step) {}

bool Model::changeState_Color(size_t row_idx, size_t col_idx) {}

bool Clear_Color() {}
