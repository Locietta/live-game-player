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

bool Initalize_Random(TwoDMat<bool> &m_TwoDMat, double True_Probility);
bool Initalize_Random(TwoDMat<uint32_t> &m_TwoDMat, double True_Probility);

class Model : public Notification {
public:
    Model(size_t heigth = defaultRowNum, size_t width = defaultColNum);
    ~Model() = default;

    // std::function<void(uint32_t)> get_model_modification() noexcept;

    //*black write matrix
    bool init(double Ture_Prob = 0.25); //< random init map
    bool Run(int step);
    bool Randomize(double True_Prob) {
        bool tmp = Initalize_Random(m_TwoDMat, True_Prob);
        trigger(PropID_ColorMatrix);
        return tmp;
    }
    bool SingleStep() { return Run(1); }
    bool Randomize() { return Randomize(True_Prob); }
    bool changeState(size_t row_idx, size_t col_idx);
    bool Clear();
    //*color matrix
    bool init_Color(double True_Prob = 0.25, uint32_t stageNum = 10); // stageNum = 3 * k + 1, k > 0
    bool Run_Color(int step);
    bool Randomize_Color(double True_Prob) {
        bool tmp = Initalize_Random(m_Color2DMat, True_Prob);
        trigger(PropID_ColorMatrix);
        return tmp;
    }
    bool SingleStep_Color() { return Run_Color(1); }
    bool changeState_Color(size_t row_idx, size_t col_idx);
    bool Clear_Color();

    bool Adjust_Random(size_t height, size_t width, double TrueProb);
    bool Load(const std::string &file_Name);
    bool Save(const std::string &file_Name);

    ref_ptr<TwoDMat<bool>> Get_Bool2DMat();

private:
    double True_Prob;
    TwoDMat<bool> m_TwoDMat;
    TwoDMat<bool> m_Next2DMat;

    uint32_t m_colorStageNum;
    TwoDMat<uint32_t> m_Color2DMat;
    TwoDMat<uint32_t> m_NextColor2DMat;

    std::function<void(uint32_t, uint32_t, bool)> changecolor;
};

#endif // _MODEL_H_
