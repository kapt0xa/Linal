#pragma once
#include "Linal.h"

namespace linal
{
    // Constructors
    template<typename T>
    const T& Direction2<T>::GetX() const noexcept 
    {
        return coordinates.x;
    }

    template<typename T>
    const T& Direction2<T>::GetY() const noexcept 
    {
        return coordinates.y;
    }

    template<typename T>
    const Vector2<T>& Direction2<T>::AsVect() const noexcept 
    {
        return coordinates;
    }

    template<typename T>
    Direction2<T>::operator const Vector2<T>& () const noexcept 
    {
        return AsVect();
    }

    // Operator Overloads
    template<typename T>
    Direction2<T> Direction2<T>::operator*(const Rotator2<T> complex) const noexcept 
    {
        return coordinates * complex.AsComplex();
    }

    template<typename T>
    Direction2<T> Direction2<T>::operator*(const RotMatrix2x2<T>& matrix) const noexcept 
    {
        return coordinates * matrix.AsMatrix();
    }

    template<typename T>
    Direction2<T> Direction2<T>::operator-() const noexcept 
    {
        return -coordinates;
    }

    template<typename T>
    Direction2<T> Direction2<T>::OrthogonalR() const noexcept 
    {
        return coordinates.OrthogonalR();
    }

    template<typename T>
    Direction2<T> Direction2<T>::OrthogonalL() const noexcept 
    {
        return coordinates.OrthogonalL();
    }

    template<typename T>
    Direction2<T>& Direction2<T>::RepairFast()
    {
        coordinates *= 1.5 - coordinates.Abs2() / 2;
        return *this;
    }

    template<typename T>
    Direction2<T>& Direction2<T>::Repair() 
    {
        coordinates.Normalize();
        return *this;
    }

    template<typename T>
    template<typename MathT>
    Direction2<T>& Direction2<T>::Repair(MathT&& sqrt_calculator) 
    {
        coordinates.Normalize(sqrt_calculator);
        return *this;
    }

    template<typename T>
    bool Direction2<T>::operator==(const Direction2<T>& other) const noexcept 
    {
        return coordinates == other.coordinates;
    }

    template<typename T>
    bool Direction2<T>::operator!=(const Direction2<T>& other) const noexcept 
    {
        return !(*this == other);
    }

    template<typename T>
    bool Direction2<T>::Compare(const Direction2<T>& other, const T& epsilon2) const noexcept 
    {
        return coordinates.Compare(other.coordinates, epsilon2);
    }

    template<typename T>
    Rotator2<T>& Direction2<T>::AsComplex() noexcept 
    {
        static_assert(sizeof(Rotator2<T>) == sizeof(Direction2<T>), "rotator2 and direction2 structs should be simillar");
        static_assert(alignof(Rotator2<T>) == alignof(Direction2<T>), "rotator2 and direction2 structs should be simillar");
        return reinterpret_cast<Rotator2<T>&>(*this);
    }

    template<typename T>
    const Rotator2<T>& Direction2<T>::AsComplex() const noexcept 
    {
        static_assert(sizeof(Rotator2<T>) == sizeof(Direction2<T>), "rotator2 and direction2 structs should be simillar");
        static_assert(alignof(Rotator2<T>) == alignof(Direction2<T>), "rotator2 and direction2 structs should be simillar");
        return reinterpret_cast<const Rotator2<T>&>(*this);
    }

    template<typename T>
    const Direction2<T> Direction2<T>::up = Vector2<T>{ 0, 1 };
    template<typename T>
    const Direction2<T> Direction2<T>::forward = up;
    template<typename T>
    const Direction2<T> Direction2<T>::down = -up;
    template<typename T>
    const Direction2<T> Direction2<T>::back = down;
    template<typename T>
    const Direction2<T> Direction2<T>::right = Vector2<T>{ 1, 0 };
    template<typename T>
    const Direction2<T> Direction2<T>::left = -right;

    // Private Constructors
    template<typename T>
    Direction2<T>::Direction2(const Vector2<T>& vector) noexcept
        : coordinates(vector) 
    {}

    template<typename T>
    Direction2<T>::Direction2(Vector2<T>&& vector) noexcept 
        : coordinates(std::move(vector))
    {}

    template<typename T>
    Direction2<T>& Direction2<T>::operator=(const Vector2<T>& vector) noexcept 
    {
        coordinates = vector;
        return *this;
    }

    template<typename T>
    Direction2<T>& Direction2<T>::operator=(Vector2<T>&& vector) noexcept 
    {
        coordinates = std::move(vector);
        return *this;
    }
}
