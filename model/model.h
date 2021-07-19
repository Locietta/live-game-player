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
#include <memory>
#include <random>

bool Initalize_Random(TwoDMat<bool> &m_TwoDMat, double True_Probility);
bool Initalize_Random(TwoDMat<unsigned char> &m_TwoDMat, double True_Probility);

class Model : public Notification {
public:
    Model(size_t heigth = defaultRowNum, size_t width = defaultColNum);
    ~Model() = default;

    // std::function<void(uint32_t)> get_model_modification() noexcept;

    bool init(double Ture_Prob = 0.25); //< random init map
    bool Run(int step);
    bool Randomize(double True_Prob) {
        bool tmp = Initalize_Random(m_TwoDMat, True_Prob) && Initalize_Random(m_Color2DMat, True_Prob);
        trigger(PropID_ColorMatrix);
        return tmp;
    }
    bool SingleStep() { return Run(1); }
    bool Randomize() { return Randomize(True_Prob); }
    bool changeState(size_t row_idx, size_t col_idx);
    bool Clear();

    bool Adjust_Random(size_t height, size_t width, double TrueProb);
    bool Load(std::string file_Name);
    bool Save(std::string file_Name);

    ref_ptr<TwoDMat<bool>> Get_Bool2DMat();

private:
    double True_Prob;
    TwoDMat<bool> m_TwoDMat;
    TwoDMat<bool> m_Next2DMat;
    TwoDMat<unsigned char> m_Color2DMat;
    TwoDMat<unsigned char> m_NextColor2DMat;

    std::function<void(uint32_t, uint32_t, bool)> changecolor;
};

#endif // _MODEL_H_
