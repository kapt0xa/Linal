#pragma once
#include "Linal.h"

namespace linal
{
    template<typename T>
    const Direction2<T>& RotMatrix2x2<T>::Line0() const noexcept
    {
        static_assert(sizeof(Vector2<T>) == sizeof(Direction2<T>), "vector and direction structs should be simillar");
        static_assert(alignof(Vector2<T>) == alignof(Direction2<T>), "vector and direction structs should be simillar");
        return reinterpret_cast<const Direction2<T>&>(value.line0);
    }

    template<typename T>
    const Direction2<T>& RotMatrix2x2<T>::Line1() const noexcept
    {
        static_assert(sizeof(Vector2<T>) == sizeof(Direction2<T>), "vector and direction structs should be simillar");
        static_assert(alignof(Vector2<T>) == alignof(Direction2<T>), "vector and direction structs should be simillar");
        return reinterpret_cast<const Direction2<T>&>(value.line1);
    }

    template<typename T>
    const Direction2<T>& RotMatrix2x2<T>::Column0() const noexcept
    {
        return {{value.line0.x, value.line1.x}};
    }

    template<typename T>
    const Direction2<T>& RotMatrix2x2<T>::Column1() const noexcept
    {
        return {{value.line0.y, value.line1.y}};
    }

    template<typename T>
    RotMatrix2x2<T> RotMatrix2x2<T>::operator*(const RotMatrix2x2& other) const noexcept
    {
        return RotMatrix2x2<T>{ value * other.value };
    }

    template<typename T>
    RotMatrix2x2<T>& RotMatrix2x2<T>::Inverse() noexcept
    {
        value.line0.y = -value.line0.y;
        value.line1.x = -value.line1.x;
        return *this;
    }

    template<typename T>    
    RotMatrix2x2<T> RotMatrix2x2<T>::Inversed() const noexcept
    {
        return RotMatrix2x2(*this).Inverse();
    }

    template<typename T>
    const Matrix2x2<T>& RotMatrix2x2<T>::AsMatrix() const noexcept
    {
        return value;
    }

    template<typename T>
    const RotMatrix2x2<T> RotMatrix2x2<T>::identity = { Matrix2x2<T>::identity };
    template<typename T>
    const RotMatrix2x2<T> RotMatrix2x2<T>::orthogonal_left = { Matrix2x2<T>::orthogonal_left };
    template<typename T>
    const RotMatrix2x2<T> RotMatrix2x2<T>::orthogonal_right = { Matrix2x2<T>::orthogonal_right };
    template<typename T>
    const RotMatrix2x2<T> RotMatrix2x2<T>::turn_around = { Matrix2x2<T>::turn_around };
}
