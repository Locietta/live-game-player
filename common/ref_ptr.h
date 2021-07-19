#ifndef _REF_PTR_H_
#define _REF_PTR_H_

#include <cassert>

template <typename T>
class ref_ptr {
public:
    constexpr ref_ptr() noexcept : m_p(nullptr) {}
    constexpr explicit ref_ptr(T &t) noexcept : m_p(&t) {}
    constexpr explicit ref_ptr(T *p) noexcept : m_p(p) {}
    constexpr ref_ptr(const ref_ptr &src) noexcept : m_p(src.m_p) {}
    constexpr ref_ptr(ref_ptr &&src) noexcept : m_p(src.m_p) { src.m_p = nullptr; }
    ~ref_ptr() noexcept = default;

    constexpr ref_ptr &operator=(const ref_ptr &src) noexcept {
        if (this != &src) {
            m_p = src.m_p;
        }
        return *this;
    }

    constexpr ref_ptr &operator=(ref_ptr &&src) noexcept {
        if (this != &src) {
            m_p = src.m_p;
            src.m_p = nullptr;
        }
        return *this;
    }

    constexpr ref_ptr<T> &operator=(T *p) noexcept {
        m_p = p;
        return *this;
    }

    void reset() noexcept { m_p = nullptr; }
    [[nodiscard]] constexpr bool isNull() const noexcept { return m_p == nullptr; }
    constexpr const T *get() const noexcept { return m_p; }
    constexpr T *get() noexcept { return m_p; }
    constexpr const T *operator->() const noexcept { return get(); }
    constexpr T *operator->() noexcept { return get(); }
    constexpr const T &operator*() const noexcept {
        assert(!isNull());
        return *get();
    }
    constexpr T &operator*() noexcept {
        assert(!isNull());
        return *get();
    }

private:
    T *m_p;
};

#endif // _REF_PTR_H_
