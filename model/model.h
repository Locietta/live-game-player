#ifndef _MODEL_H_
#define _MODEL_H_

#include "../common/Defs.h"
#include "../common/TwoDMat.h"
#include "../common/notification/Notification.h"
#include "assert.h"
#include <cstdint>
#include <functional>
#include <iostream>
#include <memory>
#include <random>

bool Initalize_Random(TwoDMat<bool> &m_TwoDMat, double True_Probility);

class Model : public Notification {
public:
    Model(size_t heigth = defaultRowNum, size_t width = defaultColNum);
    ~Model() = default;

    std::function<void(uint32_t)> get_model_modification() noexcept;

    bool init(double Ture_Prob = 0.25);              //< random init map
    bool Adjust_Random(size_t height, size_t width); // todo
    bool Load(std::string file_Name);                // todo
    bool Run(int step);
    bool SingleStep() { return Run(1); }
    bool Randomize(double True_Prob) { return Initalize_Random(m_TwoDMat, True_Prob); }
    bool Clear();
    bool changeState(size_t row_idx, size_t col_idx);
    unique_ptr<TwoDMat<bool>> Get_Bool2DMat();

private:
    TwoDMat<bool> m_TwoDMat;
    TwoDMat<bool> m_Next2DMat;

    std::function<void(uint32_t, uint32_t, bool)> changecolor;
};

#endif // _MODEL_H_
