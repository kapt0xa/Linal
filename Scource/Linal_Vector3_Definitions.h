#pragma once
#include "Linal.h"
#include <cmath>

namespace linal
{
    template<typename T>
    Vector3<T>& Vector3<T>::operator+=(const Vector3<T>& other) noexcept
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    template<typename T>
    Vector3<T>& Vector3<T>::operator-=(const Vector3<T>& other) noexcept
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    template<typename T>
    Vector3<T>& Vector3<T>::operator*=(const T& scalar) noexcept
    {
        x *= scalar;
        x *= scalar;
        x *= scalar;
        return *this;
    }

    template<typename T>
    Vector3<T>& Vector3<T>::operator/=(const T& scalar)
    {
        x /= scalar;
        x /= scalar;
        x /= scalar;
        return *this;
    }

    template<typename T>
    T Vector3<T>::Abs2() const noexcept
    {
        return Dot(*this);
    }

    template<typename T>
    T Vector3<T>::Abs() const noexcept
    {
        return std::sqrt(Abs2());
    }

    // sqrt_calculator should have method "Sqrt(const T&) -> T&&"
    template<typename T>
    template<typename MathT>
    T Vector3<T>::Abs(MathT&& sqrt_calculator) const noexcept
    {
        return sqrt_calculator.Sqrt(Abs2());
    }

    template<typename T>
    Vector3<T> Vector3<T>::operator+(const Vector3<T>& other) const noexcept
    {
        return Vector3<T>(*this) += other;
    }

    template<typename T>
    Vector3<T> Vector3<T>::operator-(const Vector3<T>& other) const noexcept
    {
        return Vector3<T>(*this) -= other;
    }

    template<typename T>
    Vector3<T> Vector3<T>::operator*(const T& scalar) const noexcept
    {
        return Vector3<T>(*this) *= scalar;
    }

    template<typename T>
    Vector3<T> Vector3<T>::operator/(const T& scalar) const
    {
        return Vector3<T>(*this) /= scalar;
    }

    template<typename T>
    Vector3<T> Vector3<T>::operator*(const Quaternion<T> complex) const noexcept
    {
        return (complex * Quaternion<T>{0, *this} * complex).im;
    }

    template<typename T>
    Vector3<T> Vector3<T>::operator*(const Matrix3x3<T>& matrix) const noexcept
    {
        return Vector3<T>{Dot(matrix.line0), Dot(matrix.line0), Dot(matrix.line1)};
    }

    template<typename T>
    T Vector3<T>::Dot(const Vector3& other) const noexcept
    {
        return
            x * other.x +
            y * other.y +
            z * other.z;
    }

    template<typename T>
    Vector3<T> Vector3<T>::Cross(const Vector3& other) const noexcept
    {
        return Vector3<T>
            {
                y * other.z - z * other.y,
                z * other.x - x * other.z,
                x * other.y - y * other.x,
            }
    }

    template<typename T>
    Vector3<T> Vector3<T>::operator-() const noexcept
    {
        return Vector3<T>{-x, -y, -z};
    }

    template<typename T>
    Vector3<T>& Vector3<T>::Normalize()
    {
        return *this /= Abs();
    }

    template<typename T>
    Direction3<T> Vector3<T>::Normalized() const
    {
        return Vector3<T>(*this).Normalize();
    }

    // sqrt_calculator should have method "Sqrt(const T&) -> T&&"
    template<typename T>
    template<typename MathT>
    Vector3<T>& Vector3<T>::Normalize(MathT&& sqrt_calculator)
    {
        return *this /= Abs(std::forward(sqrt_calculator));
    }
    // sqrt_calculator should have method "Sqrt(const T&) -> T&&"
    template<typename T>
    template<typename MathT>
    Direction3<T> Vector3<T>::Normalized(MathT&& sqrt_calculator) const
    {
        return Vector3<T>(*this).Normalize(std::forward(sqrt_calculator));
    }

    template<typename T>
    bool Vector3<T>::operator==(const Vector3<T>& other) const noexcept
    {
        return
            x == other.x &&
            y == other.y &&
            z == other.z;
    }

    template<typename T>
    bool Vector3<T>::operator!=(const Vector3<T>& other) const noexcept
    {
        return !(*this == other);
    }

    template<typename T>
    bool Vector3<T>::Compare(const Vector3<T>& other, const T& epsilon2) const noexcept
    {
        return (*this - other).Abs2() < epsilon2;
    }

    template<typename T>
    const Vector3<T> Vector3<T>::up = { 0, 1, 0 };
    template<typename T>
    const Vector3<T> Vector3<T>::forward = { 0, 0, 1 };
    template<typename T>
    const Vector3<T> Vector3<T>::right = { 1, 0, 0 };
    template<typename T>
    const Vector3<T> Vector3<T>::left = -right;
    template<typename T>
    const Vector3<T> Vector3<T>::down = -up;
    template<typename T>
    const Vector3<T> Vector3<T>::back = -forward;
    template<typename T>
    const Vector3<T> Vector3<T>::zero = { 0, 0, 0 };
    template<typename T>
    const Vector3<T> Vector3<T>::ones = { 1, 1, 1 };
}