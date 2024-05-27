#pragma once
#include "Linal.h"

namespace linal
{
    template<typename T>
    Quaternion<T>& Quaternion<T>::operator+=(const Quaternion<T>& other) noexcept
    {
        re += other.re;
        im += other.im;
        return *this;
    }

    template<typename T>
    Quaternion<T>& Quaternion<T>::operator-=(const Quaternion<T>& other) noexcept
    {
        re -= other.re;
        im -= other.im;
        return *this;
    }

    template<typename T>
    Quaternion<T>& Quaternion<T>::operator*=(const Quaternion<T>& other) noexcept
    {
        return *this = *this * other;
    }

    template<typename T>
    Quaternion<T>& Quaternion<T>::operator*=(const T& scalar) noexcept
    {
        re *= scalar;
        im *= scalar;
        return *this;
    }

    template<typename T>
    Quaternion<T>& Quaternion<T>::operator/=(const T& scalar)
    {
        re /= scalar;
        im /= scalar;
        return *this;
    }

    template<typename T>
    T Quaternion<T>::Abs2() const noexcept
    {
        return re * re + im.Abs2();
    }

    template<typename T>
    T Quaternion<T>::Abs() const noexcept
    {
        return std::sqrt(Abs2());
    }

    // sqrt_calculator should have method "Sqrt(const T&) -> T&&"
    template<typename T>
    template<typename MathT>
    T Quaternion<T>::Abs(MathT&& sqrt_calculator) const noexcept
    {
        return sqrt_calculator.Sqrt(Abs2());
    }

    template<typename T>
    RotMatrix3x3<T> Quaternion<T>::MakeMatrix() const noexcept
    {
        T xx2 = 2 * im.x * im.x / Abs2();
        T yy2 = 2 * im.y * im.y / Abs2();
        T zz2 = 2 * im.z * im.z / Abs2();

        T xy2 = 2 * im.x * im.y / Abs2();
        T yz2 = 2 * im.y * im.z / Abs2();
        T zx2 = 2 * im.z * im.x / Abs2();

        T wx2 = 2 * im.x * re / Abs2();
        T wy2 = 2 * im.y * re / Abs2();
        T wz2 = 2 * im.z * re / Abs2();
        return RotMatrix3x3<T>
        {
            Matrix3x3<T>
            {
                Vector3<T>{ T(1) - yy2 - zz2,        xy2 - wz2,        zx2 + wy2 },
                Vector3<T>{        xy2 + wz2, T(1) - zz2 - xx2,        yz2 - wx2 },
                Vector3<T>{        zx2 - wy2,        yz2 + wx2, T(1) - xx2 - yy2 },
            };
        }
    }

    template<typename T>
    Quaternion<T> Quaternion<T>::operator+(const Quaternion<T>& other) const noexcept
    {
        return Quaternion<T>(*this) += other;
    }

    template<typename T>
    Quaternion<T> Quaternion<T>::operator-(const Quaternion<T>& other) const noexcept
    {
        return Quaternion<T>(*this) -= other;
    }

    template<typename T>
    Quaternion<T> Quaternion<T>::operator*(const Quaternion<T>& other) const noexcept
    {
        return Quaternion<T>
        {
            re * other.re - im.Dot(other.im),
            im * other.re + other.im * re + im.Cross(other.im)
        };
    }

    template<typename T>
    Quaternion<T> Quaternion<T>::operator*(const T& scalar) const noexcept
    {
        return Quaternion<T>(*this) *= scalar;
    }

    template<typename T>
    Quaternion<T> Quaternion<T>::operator/(const T& scalar) const
    {
        return Quaternion<T>(*this) /= scalar;
    }

    template<typename T>
    Quaternion<T> Quaternion<T>::operator-() const noexcept
    {
        return Quaternion<T>{-re, -im};
    }

    // same as 1 / Quaternion<T>{re, im}
    template<typename T>
    Quaternion<T> Quaternion<T>::Inverted() const
    {
        return Conjugate() / Abs2();
    }

    template<typename T>
    Quaternion<T> Quaternion<T>::Conjugate() const noexcept
    {
        return Quaternion<T>{re, -im};
    }

    template<typename T>
    Quaternion<T>& Quaternion<T>::Normalize()
    {
        return *this /= Abs();
    }

    template<typename T>
    Rotator3<T> Quaternion<T>::Normalized() const
    {
        return Quaternion<T>(*this).Normalize();
    }

    // sqrt_calculator should have method "Sqrt(const T&) -> T&&"
    template<typename T>
    template<typename MathT>
    Quaternion<T>& Quaternion<T>::Normalize(MathT&& sqrt_calculator)
    {
        return *this /= Abs(std::forward(sqrt_calculator));
    }

    template<typename T>
    template<typename MathT>
    Rotator3<T> Quaternion<T>::Normalized(MathT&& sqrt_calculator) const
    {
        return Quaternion<T>(*this).Normalize(std::forward(sqrt_calculator));
    }

    template<typename T>
    bool Quaternion<T>::operator==(const Quaternion<T>& other) const noexcept
    {
        return re == other.re && im == other.im;
    }

    template<typename T>
    bool Quaternion<T>::operator!=(const Quaternion<T>& other) const noexcept
    {
        return !(*this == other);
    }

    template<typename T>
    bool Quaternion<T>::Compare(const Quaternion<T>& other, const T& epsilon2) const noexcept
    {
        return (*this - other).Abs2() < epsilon2;
    }

    template<typename T>
    const Quaternion<T> Quaternion<T>::one = { 1, Vector3<T>::zero };
    template<typename T>
    const Quaternion<T> Quaternion<T>::i = { 0, Vector3<T>::right };
    template<typename T>
    const Quaternion<T> Quaternion<T>::j = { 0, Vector3<T>::up };
    template<typename T>
    const Quaternion<T> Quaternion<T>::k = { 0, Vector3<T>::forward };
    template<typename T>
    const Quaternion<T> Quaternion<T>::zero = { 0, Vector3<T>::zero };
}