#pragma once
#include "Linal.h"
#include <cmath>

namespace linal
{
    template<typename T>
    Vector2<T>& Vector2<T>::operator += (const Vector2<T>& other) noexcept
    {
        x += other.x;
        y += other.y;

        return *this;
    }

    template<typename T>
    Vector2<T>& Vector2<T>::operator -= (const Vector2<T>& other) noexcept
    {
        x -= other.x;
        y -= other.y;

        return *this;
    }

    template<typename T>
    Vector2<T>& Vector2<T>::operator *= (const T& scalar) noexcept
    {
        x *= scalar;
        y *= scalar;

        return *this;
    }

    template<typename T>
    Vector2<T>& Vector2<T>::operator /= (const T& scalar)
    {
        if(scalar == 0)
        {
            throw std::runtime_error("devision by zero");
        }

        x /= scalar;
        y /= scalar;

        return *this;
    }
    
    template<typename T>
    Vector2<T>& Vector2<T>::operator *= (const Complex<T> complex) noexcept
    {
        AsComplex() *= complex;
        return *this;
    }

    template<typename T>
    T Vector2<T>::Abs2() const noexcept
    {
        return x*x + y*y;
    }

    template<typename T>
    T Vector2<T>::Abs() const noexcept
    {
        return std::sqrt(Abs2());
    }

    // the sqrt_calculator should have method "Sqrt(const T&) -> T&&"
    template<typename T>
    template<typename MathT>
    T Vector2<T>::Abs(MathT&& sqrt_calculator) const noexcept
    {
        return sqrt_calculator.Sqrt(Abs2());
    }

    template<typename T>
    Vector2<T> Vector2<T>::operator + (const Vector2<T>& other) const noexcept
    {
        return Vector2<T>(*this) += other;
    }

    template<typename T>
    Vector2<T> Vector2<T>::operator - (const Vector2<T>& other) const noexcept
    {
        return Vector2<T>(*this) -= other;
    }

    template<typename T>
    Vector2<T> Vector2<T>::operator * (const T& scalar) const noexcept
    {
        return Vector2<T>(*this) *= scalar;
    }

    template<typename T>
    Vector2<T> Vector2<T>::operator / (const T& scalar) const
    {
        if(scalar == 0)
        {
            throw std::runtime_error("devision by zero");
        }

        return Vector2<T>(*this) /= scalar;
    }

    template<typename T>
    Vector2<T> Vector2<T>::operator * (const Complex<T> complex) const noexcept
    {
        return Vector2<T>(*this) *= complex;
    }
    
    template<typename T>
    Vector2<T> Vector2<T>::operator*(const Matrix2x2<T>& matrix) const noexcept 
    {
        return
        {
            x * matrix.line0.x + y * matrix.line1.x,
            x * matrix.line0.y + y * matrix.line1.y
        };
    }

    template<typename T>
    T Vector2<T>::Dot(const Vector2<T>& other) const noexcept
    {
        return x*other.x + y*other.y;
    }

    template<typename T>
    Vector2<T> Vector2<T>::operator -() const noexcept
    {
        return { -x, -y };
    }

    template<typename T>
    Vector2<T> Vector2<T>::OrthogonalR() const noexcept
    {
        return { y, -x };
    }

    template<typename T>
    Vector2<T> Vector2<T>::OrthogonalL() const noexcept
    {
        return { -y, x };
    }

    template<typename T>
    Vector2<T>& Vector2<T>::Normalize()
    {
        return *this /= Abs();
    }

    template<typename T>
    Direction2<T> Vector2<T>::Normalized() const
    {
        return Vector2<T>(*this).Normalize();
    }

    template<typename T>
    template<typename MathT>
    Vector2<T>& Vector2<T>::Normalize(MathT&& sqrt_calculator)
    {
        return *this /= Abs(std::forward(sqrt_calculator));
    }

    template<typename T>
    template<typename MathT>
    Direction2<T> Vector2<T>::Normalized(MathT&& sqrt_calculator) const
    {
        return Vector2<T>(*this).Normalize(std::forward(sqrt_calculator));
    }

    template<typename T>
    bool Vector2<T>::operator == (const Vector2<T>& other) const noexcept
    {
        return (x == other.x) && (y == other.y);
    }

    template<typename T>
    bool Vector2<T>::operator != (const Vector2<T>& other) const noexcept
    {
        return !(*this == other);
    }

    template<typename T>
    bool Vector2<T>::Compare(const Vector2<T>& other, const T& epsilon2) const noexcept
    {
        return (*this - other).Abs2() < epsilon2;
    }

    template<typename T>
    Complex<T>& Vector2<T>::AsComplex() noexcept
    {
        static_assert(sizeof(Complex<T>) == sizeof(Vector2<T>), "complex and vector structs should be simillar");
        static_assert(alignof(Complex<T>) == alignof(Vector2<T>), "complex and vector structs should be simillar");
        return reinterpret_cast<Complex<T>>(*this);
    }

    template<typename T>
    const Complex<T>& Vector2<T>::AsComplex() const noexcept
    {
        static_assert(sizeof(Complex<T>) == sizeof(Vector2<T>), "complex and vector structs should be simillar");
        static_assert(alignof(Complex<T>) == alignof(Vector2<T>), "complex and vector structs should be simillar");
        return reinterpret_cast<Complex<T>>(*this);
    }

    template<typename T>
    template<typename T2>
    Vector2<T>::operator Vector2<T2>() const noexcept
    {
        return
        {
            static_cast<T2>(x),
            static_cast<T2>(y)
        };
    }

    template<typename T>
    const Vector2<T> Vector2<T>::up = {0, 1};

    template<typename T>
    const Vector2<T> Vector2<T>::forward = Vector2<T>::up;

    template<typename T>
    const Vector2<T> Vector2<T>::down = -Vector2<T>::up;

    template<typename T>
    const Vector2<T> Vector2<T>::back = -Vector2<T>::forward;

    template<typename T>
    const Vector2<T> Vector2<T>::right = {1, 0};
    
    template<typename T>
    const Vector2<T> Vector2<T>::left = {1, 0};
    
    template<typename T>
    const Vector2<T> Vector2<T>::zero = {0, 0};
    
    template<typename T>
    const Vector2<T> Vector2<T>::ones = {1, 1};
} // namespace linal
