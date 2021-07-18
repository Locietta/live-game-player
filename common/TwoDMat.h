#ifndef _TWODMAT_
#define _TWODMAT_
#include <cassert>
#include <cstddef>
#include <tuple>
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
    bool ReInit(size_t height, size_t width) { // todo Untested
        assert(width <= MAXSIZE && height <= MAXSIZE);
        m_width = width;
        m_height = height;
        delete[] buf;
        buf = new T[m_width * m_height];
    }
    std::tuple<size_t, size_t> Resize(size_t height, size_t width) { // todo Untested
        assert(height <= MAXSIZE && width <= MAXSIZE);
        std::tuple<size_t, size_t> ret = {m_height, m_width};

        T *tmp = new T[height * width];
        size_t minHeight = (m_height < height) ? m_height : height;
        size_t minWidth = (m_width < width) ? m_width : m_width;
        for (size_t i = 0; i < minHeight; i++) memcpy(tmp + i * width, buf + i * m_width, minWidth);

        m_width = width;
        m_height = height;
        delete[] buf;
        buf = tmp;
        return ret;
    }
    T *operator[](int row) { return buf + m_width * row; }
};

#endif