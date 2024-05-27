#pragma once
#include "Linal.h"

namespace linal
{
    template<typename T>
    Matrix2x2<T>& Matrix2x2<T>::operator+=(const Matrix2x2<T>& other) noexcept 
    {
        line0 += other.line0;
        line1 += other.line1;
        return *this;
    }

    template<typename T>
    Matrix2x2<T>& Matrix2x2<T>::operator-=(const Matrix2x2<T>& other) noexcept 
    {
        line0 -= other.line0;
        line1 -= other.line1;
        return *this;
    }

    template<typename T>
    Matrix2x2<T>& Matrix2x2<T>::operator*=(const T& scalar) noexcept 
    {
        line0 *= scalar;
        line1 *= scalar;
        return *this;
    }

    template<typename T>
    Matrix2x2<T>& Matrix2x2<T>::operator/=(const T& scalar) 
    {
        line0 /= scalar;
        line1 /= scalar;
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
        return {-line0, -line1};
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
            {line0.Dot(other_t.line0), line0.Dot(other_t.line1)},
            {line1.Dot(other_t.line0), line1.Dot(other_t.line1)} 
        };
    }

    template<typename T>
    bool Matrix2x2<T>::operator==(const Matrix2x2<T>& other) const noexcept 
    {
        return (line0 == other.line0) && (line1 == other.line1);
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
        return temp.line0.Abs2() + temp.line1.Abs2() < epsilon2;
    }

    template<typename T>
    Matrix2x2<T> Matrix2x2<T>::Transposed() const noexcept 
    {
        return 
        { 
            {line0.x, line1.x}, 
            {line0.y, line1.y} 
        };
    }

    template<typename T>
    T Matrix2x2<T>::Det() const noexcept 
    {
        return line0.x * line1.y - line0.y * line1.x;
    }

    // Inverse
    template<typename T>
    Matrix2x2<T> Matrix2x2<T>::Inversed() const 
    {
        T det = Det();
        if (det == 0) 
        {
            throw std::runtime_error("can't invert matrix with det == 0");
        }
        return 
        { 
            {line1.y / det, -line0.y / det}, 
            {-line1.x / det, line0.x / det} 
        };
    }

    template <typename T>
    const Matrix2x2<T> Matrix2x2<T>::one = 
    {
        { 1, 0 },
        { 0, 1 }
    };

    template <typename T>
    const Matrix2x2<T> Matrix2x2<T>::zero = 
    {
        { 0, 0 },
        { 0, 0 }
    };

    template<typename T>
    Transform2dUniform<T> Matrix2x2<T>::MakeTransform2D(const Vector2<T>& offset) const noexcept
    {
        Transform2dUniform<T> transform;
        transform[0] = line0.x;
        transform[1] = line0.y;
        transform[2] = offset.x;
        transform[3] = line1.x;
        transform[4] = line1.y;
        transform[5] = offset.y;
        transform[6] = 0;
        transform[7] = 0;
        transform[8] = 1;
        return transform;
    }

    template<typename T>
    Transform3dUniform<T> Matrix2x2<T>::MakeTransform3D(const Vector2<T>& offset) const noexcept
    {
        Transform3dUniform<T> transform;
        transform[0] = line0.x;
        transform[1] = line0.y;
        transform[2] = 0;
        transform[3] = 0;
        transform[4] = line1.x;
        transform[5] = line1.y;
        transform[6] = 0;
        transform[7] = 0;
        transform[8] = 0;
        transform[9] = 0;
        transform[10] = 1;
        transform[11] = 0;
        transform[12] = offset.x;
        transform[13] = offset.y;
        transform[14] = 0;
        transform[15] = 1;
        return transform;
    }

    template<typename T>
    std::pair<Matrix2x2<T>, Vector2<T>> Matrix2x2<T>::ReadTransform(const Transform2dUniform<T>& transform) noexcept
    {
        Matrix2x2<T> matrix;
        matrix.line0 = {transform[0], transform[1]};
        matrix.line1 = {transform[3], transform[4]};
        Vector2<T> offset = {transform[2], transform[5]};
        return {matrix, offset};
    }

    template<typename T>
    std::pair<Matrix2x2<T>, Vector2<T>> Matrix2x2<T>::ReadTransform(const Transform3dUniform<T>& transform) noexcept
    {
        Matrix2x2<T> matrix;
        matrix.line0 = {transform[0], transform[1]};
        matrix.line1 = {transform[4], transform[5]};
        Vector2<T> offset = {transform[12], transform[13]};
        return {matrix, offset};
    }


} // namespace linal