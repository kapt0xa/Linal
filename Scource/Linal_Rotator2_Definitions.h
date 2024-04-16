#pragma once
#include "Linal.h"

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
    Rotator2<T> Rotator2<T>::RadianRot(const T& angle) noexcept {
        return Rotator2<T>{Complex<T>{std::cos(angle), std::sin(angle)}};
    }

    template<typename T>
    template<typename MathT>
    Rotator2<T> Rotator2<T>::RadianRot(const T& angle, MathT&& sin_cos_calculator) {
        return Rotator2<T>{Complex<T>{sin_cos_calculator.Cos(angle), sin_cos_calculator.Sin(angle)}};
    }

}
