#ifndef _MODEL_H_
#define _MODEL_H_

#include <cstdint>
#include <functional>
#include <memory>
#include "./../common/TwoDMat.h"
#include "./../common/notification/Notification.h"
#include "ref_ptr.h"
#include <cassert>



class Model : public Notification {
   public:
	Model();
	~Model() = default;

	std::function<void(uint32_t)> get_model_modification() noexcept;

	bool init(double Ture_Prob = 0.25);  //< random init map
	bool Run(int step);
	bool changeState(size_t row_idx, size_t col_idx);
	ref_ptr<TwoDMat<bool>> Get_Bool2DMat();

   private:
	TwoDMat<bool> m_TwoDMat;
	TwoDMat<bool> m_Next2DMat;

	std::function<void(uint32_t, uint32_t, bool)> changecolor;
};

#endif // _MODEL_H_
