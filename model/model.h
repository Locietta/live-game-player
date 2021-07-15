#ifndef _MODEL_H_
#define _MODEL_H_

<<<<<<< HEAD
#include "Notification.h"
#include <cstdint>
#include <functional>

class Model : public Notification {
public:
    Model() = default;
    ~Model() = default;

    std::function<void(uint32_t)> get_model_modification() noexcept;
=======
#include <cstdint>
#include <functional>
#include <memory>

#include "./../common/notification/Notification.h"
#include "assert.h"
#define MAXSIZE 1920

template<typename T>
class TwoDMat {
	size_t m_width;
	size_t m_height;
	T* buf;

   public:
	TwoDMat(){};
	~TwoDMat() { delete[] buf; }
	TwoDMat(size_t height, size_t width) : m_width(width), m_height(height) {
		assert(m_width <= MAXSIZE && m_height <= MAXSIZE);
		buf = new T[m_width * m_height];
	}
	T* operator[](int row) { return buf + m_width * row; }

	friend class Model;
};

class Model : public Notification {
   public:
	Model(size_t length, std::function<void(uint32_t, uint32_t, bool)> &&cmd);
	~Model() = default;

	std::function<void(uint32_t)> get_model_modification() noexcept;

	bool Initalize_Random(size_t width, size_t height);
	bool Run(int step);
	bool Draw(size_t row_idx, size_t col_idx);
	shared_ptr<TwoDMat<bool>> Get_Bool2DMat();
	void Set_ChangeColor(std::function<void(uint32_t, uint32_t, bool)>&& notify) { changecolor = move(notify); };

   private:
	shared_ptr<TwoDMat<bool>> m_TwoDMat;
	shared_ptr<TwoDMat<bool>> m_Next2DMat;

	std::function<void(uint32_t, uint32_t, bool)> changecolor;
>>>>>>> pr_5
};

#endif	// _MODEL_H_
