#ifndef _TWODMAT_
#define _TWODMAT_
#include <cassert>
#include <cstddef>

#define MAXSIZE 1920

template <typename T>
struct TwoDMat {
    size_t m_width;
    size_t m_height;
    T *buf;

    TwoDMat() = default;
    ~TwoDMat() { delete[] buf; }
    TwoDMat(size_t height, size_t width) : m_width(width), m_height(height) {
        assert(m_width <= MAXSIZE && m_height <= MAXSIZE);
        buf = new T[m_width * m_height];
    }
    T *operator[](int row) { return buf + m_width * row; }
};

#endif