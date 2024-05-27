#pragma once
#include "Linal.h"
#include <cmath>

namespace linal
{
    template<typename T>
    Rotator2<T>::Rotator2(const Complex<T>& complex) noexcept : value(complex) {}

    template<typename T>
    Rotator2<T>::Rotator2(Complex<T>&& complex) noexcept : value(std::move(complex)) {}

    template<typename T>
    Rotator2<T>& Rotator2<T>::operator=(const Complex<T>& complex) noexcept
    {
        value = complex;
        return *this;
    }

    template<typename T>
    Rotator2<T>& Rotator2<T>::operator=(Complex<T>&& complex) noexcept
    {
        value = std::move(complex);
        return *this;
    }

    template<typename T>
    const T& Rotator2<T>::GetRe() const noexcept
    {
        return value.re;
    }

    template<typename T>
    const T& Rotator2<T>::GetIm() const noexcept
    {
        return value.im;
    }

    template<typename T>
    const Complex<T>& Rotator2<T>::AsComplex() const noexcept
    {
        return value;
    }

    template<typename T>
    Rotator2<T>::operator const Complex<T>& () const noexcept
    {
        return AsComplex();
    }

    template<typename T>
    RotMatrix2x2<T> Rotator2<T>::MakeMatrix() const noexcept
    {
        return AsComplex().MakeMatrix();
    }

    template<typename T>
    Rotator2<T> Rotator2<T>::operator*(const Rotator2<T> other) const noexcept
    {
        return value * other.value;
    }
    
    template<typename T>
    Rotator2<T> Rotator2<T>::operator/(const Rotator2<T> other) const noexcept
    {
        return value * other.value.Conjugate();
    }

    template<typename T>
    Direction2<T>& Rotator2<T>::RepairFast()
    {
        AsVect().RepairFast();
        return *this;
    }

    template<typename T>
    Direction2<T>& Rotator2<T>::Repair()
    {
        AsVect().Repair();
        return *this;
    }

    template<typename T>
    template<typename MathT>
    Direction2<T>& Rotator2<T>::Repair(MathT&& sqrt_calculator)
    {
        AsVect().Repair(std::forward(sqrt_calculator));
        return *this();
    }

    template<typename T>
    bool Rotator2<T>::operator==(const Direction2<T>& other) const noexcept
    {
        return AsVect() == other.AsVect();
    }

    template<typename T>
    bool Rotator2<T>::operator!=(const Direction2<T>& other) const noexcept
    {
        return !(*this == other);
    }

    template<typename T>
    bool Rotator2<T>::Compare(const Direction2<T>& other, const T& epsilon2) const noexcept
    {
        return AsComplex().Compare(other.AsComplex(), epsilon2);
    }

    template<typename T>
    Direction2<T>& Rotator2<T>::AsVect() noexcept
    {
        static_assert(sizeof(Rotator2<T>) == sizeof(Direction2<T>), "rotator2 and direction2 structs should be simillar");
        static_assert(alignof(Rotator2<T>) == alignof(Direction2<T>), "rotator2 and direction2 structs should be simillar");
        return reinterpret_cast<Direction2<T>&>(*this);
    }

    template<typename T>
    const Direction2<T>& Rotator2<T>::AsVect() const noexcept
    {
        static_assert(sizeof(Rotator2<T>) == sizeof(Direction2<T>), "rotator2 and direction2 structs should be simillar");
        static_assert(alignof(Rotator2<T>) == alignof(Direction2<T>), "rotator2 and direction2 structs should be simillar");
        return reinterpret_cast<const Direction2<T>&>(*this);
    }

    template<typename T>
    T Rotator2<T>::GetAngle() const noexcept
    {
        constexpr T sqrt_half = T{0.70710678118};
        if(std::abs(GetRe()) < sqrt_half)
        {
            if(GetIm() > 0)
            {
                return std::acos(GetRe());
            }
            else
            {
                return -std::acos(GetRe());
            }
        }
        else
        {
            if(GetRe() > 0)
            {
                return std::asin(GetRe());
            }
            else
            {
                if(GetIm() > 0)
                {
                    return tau/2 - std::asin(GetRe());
                }
                else
                {
                    return -tau/2 - std::asin(GetRe());
                }
            }
        }
    }

    // the asin_acos_calculator should have method "ASin(const T&) -> T&&" and "ACos(const T&) -> T&&"
    template<typename T>
    template<typename MathT>
    T Rotator2<T>::GetAngle(MathT&& asin_acos_calculator) const noexcept
    {
        if(std::abs(GetRe()) < asin_acos_calculator.SqrtHalf())
        {
            if(GetIm() > 0)
            {
                return asin_acos_calculator.ACos(GetRe());
            }
            else
            {
                return -asin_acos_calculator.ACos(GetRe());
            }
        }
        else
        {
            if(GetRe() > 0)
            {
                return asin_acos_calculator.ASin(GetRe());
            }
            else
            {
                if(GetIm() > 0)
                {
                    return tau/2 - asin_acos_calculator.ASin(GetRe());
                }
                else
                {
                    return -tau/2 - asin_acos_calculator.ASin(GetRe());
                }
            }
        }
    }

    template <typename T>
    const Rotator2<T> Rotator2<T>::identity = Rotator2(Complex<T>{1, 0});

    template <typename T>
    const Rotator2<T> Rotator2<T>::orthogonal_left = Rotator2(Complex<T>{0, 1});

    template <typename T>
    const Rotator2<T> Rotator2<T>::orthogonal_right = Rotator2(Complex<T>{0, -1});

    template <typename T>
    const Rotator2<T> Rotator2<T>::turn_around = Rotator2(Complex<T>{-1, 0});

    template<typename T>
    Rotator2<T> Rotator2<T>::RadianRot(const T& angle) noexcept 
    {
        return Rotator2<T>{Complex<T>{std::cos(angle), std::sin(angle)}};
    }

    template<typename T>
    template<typename MathT>
    Rotator2<T> Rotator2<T>::RadianRot(const T& angle, MathT&& sin_cos_calculator) 
    {
        return Rotator2<T>{Complex<T>{sin_cos_calculator.Cos(angle), sin_cos_calculator.Sin(angle)}};
    }

    template<typename T>
    Rotator2<T> Rotator2<T>::FromTo(const Vector2<T>& from, const Vector2<T>& to) noexcept
    {
        Rotator2 result = to.AsComplex() / from.AsComplex();
        result.Repair();
        return result;
    }

    template<typename T>
    Rotator2<T> Rotator2<T>::FromTo(const Direction2<T>& from, const Direction2<T>& to) noexcept
    {
        return to.AsComplex() / from.AsComplex();
    }

    template<typename T>
    template<typename MathT>
    Rotator2<T> Rotator2<T>::FromTo(const Vector2<T>& from, const Vector2<T>& to, MathT&& sqrt_calculator) noexcept
    {
        Rotator2 result = to.AsComplex() / from.AsComplex();
        result.Repair(std::forward(sqrt_calculator));
        return result;
    }

}
