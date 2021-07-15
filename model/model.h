#ifndef _MODEL_H_
#define _MODEL_H_

#include <cstdint>
#include <functional>
#include <memory>
#include "./../common/TwoDMat.h"
#include "./../common/notification/Notification.h"
#include "assert.h"



class Model : public Notification {
   public:
	Model(size_t length, std::function<void(uint32_t, uint32_t, bool)>&& cmd);
	~Model() = default;

	std::function<void(uint32_t)> get_model_modification() noexcept;

	bool Initalize_Random(size_t width, size_t height);
	bool Run(int step);
	bool Draw(size_t row_idx, size_t col_idx);
	shared_ptr<TwoDMat<bool>> Get_Bool2DMat();
	void Set_ChangeColor(std::function<void(uint32_t, uint32_t, bool)>&& notify) { changecolor = move(notify); };

   private:
	TwoDMat<bool> m_TwoDMat;
	TwoDMat<bool> m_Next2DMat;

	std::function<void(uint32_t, uint32_t, bool)> changecolor;
};

#endif	// _MODEL_H_
