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
    Matrix2x2<T> Matrix2x2<T>::Transposed() const noexcept 
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
    Matrix2x2<T> Matrix2x2<T>::Inversed() const 
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

    template<typename T>
    Transform2dUniform<T> Matrix2x2<T>::MakeTransform2D(const Vector2<T>& offset) const noexcept
    {
        Transform2dUniform<T> transform;
        transform[0] = line1.x;
        transform[1] = line1.y;
        transform[2] = offset.x;
        transform[3] = line2.x;
        transform[4] = line2.y;
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
        transform[0] = line1.x;
        transform[1] = line1.y;
        transform[2] = 0;
        transform[3] = 0;
        transform[4] = line2.x;
        transform[5] = line2.y;
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
        matrix.line1 = {transform[0], transform[1]};
        matrix.line2 = {transform[3], transform[4]};
        Vector2<T> offset = {transform[2], transform[5]};
        return {matrix, offset};
    }

    template<typename T>
    std::pair<Matrix2x2<T>, Vector2<T>> Matrix2x2<T>::ReadTransform(const Transform3dUniform<T>& transform) noexcept
    {
        Matrix2x2<T> matrix;
        matrix.line1 = {transform[0], transform[1]};
        matrix.line2 = {transform[4], transform[5]};
        Vector2<T> offset = {transform[12], transform[13]};
        return {matrix, offset};
    }


} // namespace linal