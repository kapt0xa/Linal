#pragma once
#include "Linal.h"

namespace linal
{

    template<typename T>
    Complex<T>& Complex<T>::operator += (const Complex<T>& other) noexcept 
    {
        AsVect() += other.AsVect();
        return *this;
    }

    template<typename T>
    Complex<T>& Complex<T>::operator -= (const Complex<T>& other) noexcept 
    {
        AsVect() -= other.AsVect();
        return *this;
    }

    template<typename T>
    Complex<T>& Complex<T>::operator *= (const Complex<T>& other) noexcept 
    {
        return *this = *this * other;
    }

    template<typename T>
    Complex<T>& Complex<T>::operator /= (const Complex<T>& other) noexcept 
    {
        return *this = *this / other;
    }

    template<typename T>
    Complex<T>& Complex<T>::operator *= (const T& multiplier) noexcept 
    {
        AsVect() *= multiplier;
        return *this;
    }

    template<typename T>
    Complex<T>& Complex<T>::operator /= (const T& scalar) 
    {
        AsVect() /= scalar;
        return *this;
    }

    template<typename T>
    T Complex<T>::Abs() const noexcept 
    {
        return AsVect().Abs();
    }

    template<typename T>
    T Complex<T>::Abs2() const noexcept 
    {
        return AsVect().Abs2();
    }

    template<typename T>
    template<typename MathT>
    T Complex<T>::Abs(MathT&& sqrt_calculator) const noexcept 
    {
        return AsVect().Abs(std::forward(sqrt_calculator));
    }

    template<typename T>
    Matrix2x2<T> Complex<T>::MakeMatrix() const noexcept
    {
        return Matrix2x2
        {
            {re, -im},
            {im, re}
        };
    }

    template<typename T>
    Complex<T> Complex<T>::operator + (const Complex<T>& other) const noexcept 
    {
        return Complex<T>(*this) += other;
    }

    template<typename T>
    Complex<T> Complex<T>::operator - (const Complex<T>& other) const noexcept 
    {
        return Complex<T>(*this) -= other;
    }

    template<typename T>
    Complex<T> Complex<T>::operator * (const Complex<T>& other) const noexcept {
        return 
        {
            re * other.re - im * other.im,
            re * other.im + im * other.re
        };
    }

    template<typename T>
    Complex<T> Complex<T>::operator / (const Complex<T>& other) const noexcept 
    {
        return (*this * other.Conjugate()) /= other.Abs2();
    }

    template<typename T>
    Complex<T> Complex<T>::operator * (const T& multiplier) const noexcept 
    {
        return Complex<T>(*this) *= multiplier;
    }

    template<typename T>
    Complex<T> Complex<T>::operator / (const T& scalar) const 
    {
        return Complex<T>(*this) /= scalar;
    }

    template<typename T>
    Complex<T> Complex<T>::operator -() const noexcept 
    {
        return {-re, -im};
    }

    template<typename T>
    Complex<T> Complex<T>::Inverted() const 
    {
        return Conjugate() /= Abs2();
    }

    template<typename T>
    Complex<T> Complex<T>::Conjugate() const noexcept {
        return Complex<T>{re, -im};
    }

    template<typename T>
    Complex<T>& Complex<T>::Normalize() 
    {
        AsVect().Normalize();
        return *this;
    }

    template<typename T>
    Rotator2<T> Complex<T>::Normalized() const 
    {
        return Complex<T>(*this).Normalize();
    }

    template<typename T>
    template<typename MathT>
    Complex<T>& Complex<T>::Normalize(MathT&& sqrt_calculator) 
    {
        AsVect().Normalize(std::forward(sqrt_calculator));
        return *this;
    }

    template<typename T>
    template<typename MathT>
    Rotator2<T> Complex<T>::Normalized(MathT&& sqrt_calculator) const
    {
        return Complex<T>(*this).Normalize(std::forward(sqrt_calculator));
    }

    template<typename T>
    bool Complex<T>::operator == (const Complex<T>& other) const noexcept 
    {
        return AsVect() == other.AsVect();
    }

    template<typename T>
    bool Complex<T>::operator != (const Complex<T>& other) const noexcept 
    {
        return !(*this == other);
    }

    template<typename T>
    bool Complex<T>::Compare(const Complex<T>& other, const T& epsilon2) const noexcept 
    {
        return AsVect().Compare(other.AsVect(), epsilon2);
    }

    template<typename T>
    Vector2<T>& Complex<T>::AsVect() noexcept
    {
        static_assert(sizeof(Complex<T>) == sizeof(Vector2<T>), "complex and vector structs should be simillar");
        static_assert(alignof(Complex<T>) == alignof(Vector2<T>), "complex and vector structs should be simillar");
        return reinterpret_cast<Vector2<T>&>(*this);
    }

    template<typename T>
    const Vector2<T>& Complex<T>::AsVect() const noexcept 
    {
        static_assert(sizeof(Complex<T>) == sizeof(Vector2<T>), "complex and vector structs should be simillar");
        static_assert(alignof(Complex<T>) == alignof(Vector2<T>), "complex and vector structs should be simillar");
        return reinterpret_cast<const Vector2<T>&>(*this);
    }

} // namespace linal