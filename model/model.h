#ifndef _MODEL_H_
#define _MODEL_H_

#include "../common/Defs.h"
#include "../common/TwoDMat.h"
#include "../common/notification/Notification.h"
#include "../common/ref_ptr.h"
#include <cassert>
#include <cstdint>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <random>

// template <typename T>
bool Initalize_Random(TwoDMat<uint32_t> &m_TwoDMat, double True_Probility, uint32_t stageNum);

// template <typename T>
class Model : public Notification {
public:
    Model(size_t heigth = defaultRowNum, size_t width = defaultColNum);
    ~Model() = default;

    // std::function<void(uint32_t)> get_model_modification() noexcept;
    bool init(double Ture_Prob = 0.18, uint32_t stageNum = 8); //< random init map //*black write matrix
    bool Run(int step);
    bool Randomize(double True_Prob);
    bool SingleStep() { return Run(1); }
    bool Randomize() { return Randomize(True_Prob); }
    bool changeState(size_t row_idx, size_t col_idx);
    bool Clear();

    // todo special solution
    bool Adjust_Random(size_t height, size_t width, double TrueProb);
    bool Load(const std::string &file_Name);
    bool Save(const std::string &file_Name);

    ref_ptr<TwoDMat<uint32_t>> Get_2DMat() { return ref_ptr(m_TwoDMat); }
    auto Get_ColorMapping() { return ref_ptr(m_colorList); }

private:
    double True_Prob;
    uint32_t m_colorStageNum;
    std::vector<uint32_t> m_colorList;
    TwoDMat<uint32_t> m_TwoDMat;
    TwoDMat<uint32_t> m_Next2DMat;

    std::function<void(uint32_t, uint32_t, bool)> changecolor;
};

#endif // _MODEL_H_
