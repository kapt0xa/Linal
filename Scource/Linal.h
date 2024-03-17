#pragma once
#include <stdexcept>
#include <climits>

namespace linal // structures declarations
{
    template<typename T>
    struct Vector2;

    template<typename T>
    struct Complex;

    template<typename T>
    struct Matrix2d;

//==============================================================================================================================================

    template<typename T>
    struct Vector2
    {
        T x = {};
        T y = {};

        Vector2<T>& operator += (const Vector2<T>& other) noexcept;
        Vector2<T>& operator -= (const Vector2<T>& other) noexcept;
        Vector2<T>& operator *= (const T& scalar) noexcept;
        Vector2<T>& operator /= (const T& scalar);
        Vector2<T>& operator *= (const Complex<T> complex) noexcept;

        T Abs2() const noexcept;
        T Abs() const noexcept;
        // the sqrt_calculator should have method "Sqrt(const T&) -> T&&"
        template<typename MathT>
        T Abs(MathT&& sqrt_calculator) const noexcept;

        Vector2<T> operator + (const Vector2<T>& other) const noexcept;
        Vector2<T> operator - (const Vector2<T>& other) const noexcept;
        Vector2<T> operator * (const T& scalar) const noexcept;
        Vector2<T> operator / (const T& scalar) const;
        Vector2<T> operator * (const Complex<T> complex) const noexcept;

        T Dot(const Vector2& other) const noexcept;
        Vector2<T> operator -() const noexcept;
        Vector2<T> OrthogonalR() const noexcept;
        Vector2<T> OrthogonalL() const noexcept;

        Vector2<T>& Normalize();
        Vector2<T> Normalized() const;
        // the sqrt_calculator should have method "Sqrt(const T&) -> T&&"
        template<typename MathT>
        Vector2<T>& Normalize(MathT&& sqrt_calculator);
        // the sqrt_calculator should have method "Sqrt(const T&) -> T&&"
        template<typename MathT>
        Vector2<T> Normalized(MathT&& sqrt_calculator) const;

        bool operator == (const Vector2<T>& other) const noexcept;
        bool operator != (const Vector2<T>& other) const noexcept;
        bool Compare(const Vector2<T>& other, const T& epsilon2) const noexcept;

        Complex<T>& AsComplex() noexcept;
        const Complex<T>& AsComplex() const noexcept;
    };

    using Vector2f = Vector2<float>;

//==============================================================================================================================================

    template<typename T>
    struct Complex
    {
        T re = {};
        T im = {};

        Complex<T>& operator += (const Complex<T>& other) noexcept;
        Complex<T>& operator -= (const Complex<T>& other) noexcept;
        Complex<T>& operator *= (const Complex<T>& other) noexcept;
        Complex<T>& operator /= (const Complex<T>& other) noexcept;
        Complex<T>& operator *= (const T& scalar) noexcept;
        Complex<T>& operator /= (const T& scalar);

        T Abs2() const noexcept;
        T Abs() const noexcept;
        // the sqrt_calculator should have method "Sqrt(const T&) -> T&&"
        template<typename MathT>
        T Abs(MathT&& sqrt_calculator) const noexcept;

        Complex<T> operator + (const Complex<T>& other) const noexcept;
        Complex<T> operator - (const Complex<T>& other) const noexcept;
        Complex<T> operator * (const Complex<T>& other) const noexcept;
        Complex<T> operator / (const Complex<T>& other) const noexcept;
        Complex<T> operator * (const T& scalar) const noexcept;
        Complex<T> operator / (const T& scalar) const;

        Complex<T> operator -() const noexcept;
        // same as 1 / Complex<T>{re, im}
        Complex<T> Inverted() const;
        Complex<T> Conjugate() const noexcept;

        Complex<T>& Normalize();
        Complex<T> Normalized() const;
        // the sqrt_calculator should have method "Sqrt(const T&) -> T&&"
        template<typename MathT>
        Complex<T>& Normalize(MathT&& sqrt_calculator);
        // the sqrt_calculator should have method "Sqrt(const T&) -> T&&"
        template<typename MathT>
        Complex<T> Normalized(MathT&& sqrt_calculator) const;

        bool operator == (const Complex<T>& other) const noexcept;
        bool operator != (const Complex<T>& other) const noexcept;
        bool Compare(const Complex<T>& other, const T& epsilon2) const noexcept;

        Vector2<T>& AsVect() noexcept;
        const Vector2<T>& AsVect() const noexcept;
    };

//==============================================================================================================================================

    template<typename T>
    struct Matrix2d
    {
        Vector2<T> line1;
        Vector2<T> line2;

        // Compound assignment operators
        Matrix2d<T>& operator+=(const Matrix2d<T>& other) noexcept;
        Matrix2d<T>& operator-=(const Matrix2d<T>& other) noexcept;
        Matrix2d<T>& operator*=(const T& scalar) noexcept;
        Matrix2d<T>& operator/=(const T& scalar);
        Matrix2d<T>& operator*=(const Matrix2d<T>& other) const noexcept; // for gpt: define the method via operator *

        // Unary arithmetic operators
        Matrix2d<T> operator-() const noexcept;

        // Binary arithmetic operators
        Matrix2d<T> operator+(const Matrix2d<T>& other) const noexcept; // for gpt: define this method and others via copying and operator += or another changing operator 
        Matrix2d<T> operator-(const Matrix2d<T>& other) const noexcept;
        Matrix2d<T> operator*(const T& scalar) const noexcept;
        Matrix2d<T> operator/(const T& scalar) const;
        Matrix2d<T> operator*(const Matrix2d<T>& other) const noexcept; // for gpt: define the method via transpose and Vector2::Dot();

        // Comparison operators
        bool operator==(const Matrix2d<T>& other) const noexcept;
        bool operator!=(const Matrix2d<T>& other) const noexcept;
        bool Compare(const Matrix2d<T>& other, const T& epsilon2) const noexcept; // for gpt: the method works like ==, but it is tolerant to arithmetical mistake.

        // Transpose
        Matrix2d<T> Transpose() const noexcept;

        // Determinant
        T Det() const noexcept;

        // Inverse
        Matrix2d<T> Inverse() const;
    };
}

//==============================================================================================================================================

#include "Linal_Vector2_Definitions.h"
#include "Linal_Complex_Definitions.h"
#include "Linal_Matrix2d_Definitions.h"

// end of file
