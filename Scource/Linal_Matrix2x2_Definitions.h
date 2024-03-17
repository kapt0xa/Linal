#pragma once
#include "Linal.h"

namespace linal
{
    template<typename T>
    Matrix2x2<T>& Matrix2x2<T>::operator+=(const Matrix2x2<T>& other) noexcept 
    {
        line1 += other.line1;
        line2 += other.line2;
        return *this;
    }

    template<typename T>
    Matrix2x2<T>& Matrix2x2<T>::operator-=(const Matrix2x2<T>& other) noexcept 
    {
        line1 -= other.line1;
        line2 -= other.line2;
        return *this;
    }

    template<typename T>
    Matrix2x2<T>& Matrix2x2<T>::operator*=(const T& scalar) noexcept 
    {
        line1 *= scalar;
        line2 *= scalar;
        return *this;
    }

    template<typename T>
    Matrix2x2<T>& Matrix2x2<T>::operator/=(const T& scalar) 
    {
        line1 /= scalar;
        line2 /= scalar;
        return *this;
    }

    template<typename T>
    Matrix2x2<T>& Matrix2x2<T>::operator*=(const Matrix2x2<T>& other) const noexcept 
    {
        return *this = *this * other;
    }

    template<typename T>
    Matrix2x2<T> Matrix2x2<T>::operator-() const noexcept 
    {
        return {-line1, -line2};
    }

    template<typename T>
    Matrix2x2<T> Matrix2x2<T>::operator+(const Matrix2x2<T>& other) const noexcept 
    {
        return Matrix2x2<T>(*this) += other;
    }

    template<typename T>
    Matrix2x2<T> Matrix2x2<T>::operator-(const Matrix2x2<T>& other) const noexcept 
    {
        return Matrix2x2<T>(*this) -= other;
    }

    template<typename T>
    Matrix2x2<T> Matrix2x2<T>::operator*(const T& scalar) const noexcept 
    {
        return Matrix2x2<T>(*this) *= scalar;
    }

    template<typename T>
    Matrix2x2<T> Matrix2x2<T>::operator/(const T& scalar) const 
    {
        return Matrix2x2<T>(*this) /= scalar;
    }

    template<typename T>
    Matrix2x2<T> Matrix2x2<T>::operator*(const Matrix2x2<T>& other) const noexcept 
    {
        Matrix2x2<T> other_t = other.Transpose();
        return 
        { 
            {line1.Dot(other_t.line1), line1.Dot(other_t.line2)},
            {line2.Dot(other_t.line1), line2.Dot(other_t.line2)} 
        };
    }

    template<typename T>
    bool Matrix2x2<T>::operator==(const Matrix2x2<T>& other) const noexcept 
    {
        return (line1 == other.line1) && (line2 == other.line2);
    }

    template<typename T>
    bool Matrix2x2<T>::operator!=(const Matrix2x2<T>& other) const noexcept 
    {
        return !(*this == other);
    }

    template<typename T>
    bool Matrix2x2<T>::Compare(const Matrix2x2<T>& other, const T& epsilon2) const noexcept 
    {
        Matrix2x2<T> temp = *this - other;
        return temp.line1.Abs2() + temp.line2.Abs2() < epsilon2;
    }

    template<typename T>
    Matrix2x2<T> Matrix2x2<T>::Transpose() const noexcept 
    {
        return 
        { 
            {line1.x, line2.x}, 
            {line1.y, line2.y} 
        };
    }

    template<typename T>
    T Matrix2x2<T>::Det() const noexcept 
    {
        return line1.x * line2.y - line1.y * line2.x;
    }

    // Inverse
    template<typename T>
    Matrix2x2<T> Matrix2x2<T>::Inverse() const 
    {
        T det = Det();
        if (det == 0) 
        {
            throw std::runtime_error("can't invert matrix with det == 0");
        }
        return 
        { 
            {line2.y / det, -line1.y / det}, 
            {-line2.x / det, line1.x / det} 
        };
    }

} // namespace linal