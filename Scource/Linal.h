#pragma once
#include <stdexcept>
#include <climits>
#include <array>
#include <utility>

namespace linal // structures declarations
{
    template<typename T>
    struct Vector2;

    template<typename T>
    struct Direction2;

    template<typename T>
    struct Complex;

    template<typename T>
    struct Rotator2;

    template<typename T>
    struct Matrix2x2;

    template<typename T>
    struct RotMatrix2x2;

    //------------------------------

#define _2D_IS_TESTED_ false
#if _2D_IS_TESTED_

    template<typename T>
    struct Vector3; // to do (implement methods)

    template<typename T>
    struct Direction3; // to do

    template<typename T>
    struct Quaternion; // to do

    template<typename T>
    struct Rotator3; // to do

    template<typename T>
    struct Matrix3x3; // to do

    template<typename T>
    struct RotMatrix3x3; // to do

#endif // _2D_IS_TESTED_

    //------------------------------

    template<typename T>
    using Transform2dUniform = std::array<T, 9>;

    template<typename T>
    using Transform3dUniform = std::array<T, 16>;

//==============================================================================================================================================

    template<typename T>
    struct Vector2
    {
        T x = {0};
        T y = {0};

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
        Vector2<T> operator * (const Matrix2x2<T>& matrix) const noexcept;

        T Dot(const Vector2& other) const noexcept;
        Vector2<T> operator -() const noexcept;
        Vector2<T> OrthogonalR() const noexcept;
        Vector2<T> OrthogonalL() const noexcept;

        Vector2<T>& Normalize();
        Direction2<T> Normalized() const;
        // the sqrt_calculator should have method "Sqrt(const T&) -> T&&"
        template<typename MathT>
        Vector2<T>& Normalize(MathT&& sqrt_calculator);
        // the sqrt_calculator should have method "Sqrt(const T&) -> T&&"
        template<typename MathT>
        Direction2<T> Normalized(MathT&& sqrt_calculator) const;

        bool operator == (const Vector2<T>& other) const noexcept;
        bool operator != (const Vector2<T>& other) const noexcept;
        bool Compare(const Vector2<T>& other, const T& epsilon2) const noexcept;

        Complex<T>& AsComplex() noexcept;
        const Complex<T>& AsComplex() const noexcept;

        static constexpr Vector2<T> up = {0, 1};
        static constexpr Vector2<T> forward = up;
        static constexpr Vector2<T> down = -up;
        static constexpr Vector2<T> back = down;
        static constexpr Vector2<T> right = {1, 0};
        static constexpr Vector2<T> left = {1, 0};
        static constexpr Vector2<T> zero = {0, 0};
        static constexpr Vector2<T> ones = {1, 1};
    };

    using Vector2D = Vector2<double>;
    using Vector2F = Vector2<float>;
    using Vector2I = Vector2<int>;

//==============================================================================================================================================

    template<typename T>
    struct Direction2
    {
        // Constructors
        Direction2() = delete;
        Direction2(const Direction2<T>& other) noexcept = default;
        Direction2(Direction2<T>&& other) noexcept = default;
        Direction2<T>& operator=(const Direction2<T>& other) noexcept = default;
        Direction2<T>& operator=(Direction2<T>&& other) noexcept = default;

        const T& GetX() const noexcept;
        const T& GetY() const noexcept;

        //same as operator const Vector2();
        const Vector2<T>& AsVect() const noexcept;
        operator const Vector2<T>& () const noexcept;

        Direction2<T> operator*(const Rotator2<T> complex) const noexcept;
        Direction2<T> operator*(const RotMatrix2x2<T>& matrix) const noexcept;

        Direction2<T> operator-() const noexcept;
        Direction2<T> OrthogonalR() const noexcept;
        Direction2<T> OrthogonalL() const noexcept;

        Direction2<T>& RepairFast();
        Direction2<T>& Repair();
        // the sqrt_calculator should have method "Sqrt(const T&) -> T&&"
        template<typename MathT>
        Direction2<T>& Repair(MathT&& sqrt_calculator);

        bool operator==(const Direction2<T>& other) const noexcept;
        bool operator!=(const Direction2<T>& other) const noexcept;
        bool Compare(const Direction2<T>& other, const T& epsilon2) const noexcept;

        Rotator2<T>& AsComplex() noexcept;
        const Rotator2<T>& AsComplex() const noexcept;

        static constexpr Direction2<T> up = Vector2<T>{0, 1};
        static constexpr Direction2<T> forward = up;
        static constexpr Direction2<T> down = -up;
        static constexpr Direction2<T> back = down;
        static constexpr Direction2<T> right = Vector2<T>{1, 0};
        static constexpr Direction2<T> left = -right;

    private:
        Vector2<T> coordinates;
        
        friend struct Vector2<T>;
        friend struct RotMatrix2x2<T>;

        explicit Direction2(const Vector2<T>& vector) noexcept;
        explicit Direction2(Vector2<T>&& vector) noexcept;
        Direction2<T>& operator=(const Vector2<T>& vector) noexcept;
        Direction2<T>& operator=(Vector2<T>&& vector) noexcept;
    };

//==============================================================================================================================================

    template<typename T>
    struct Complex
    {
        T re = {0};
        T im = {0};

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

        Matrix2x2<T> MakeMatrix() const noexcept;

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
        Rotator2<T> Normalized() const;
        // the sqrt_calculator should have method "Sqrt(const T&) -> T&&"
        template<typename MathT>
        Complex<T>& Normalize(MathT&& sqrt_calculator);
        // the sqrt_calculator should have method "Sqrt(const T&) -> T&&"
        template<typename MathT>
        Rotator2<T> Normalized(MathT&& sqrt_calculator) const;

        bool operator == (const Complex<T>& other) const noexcept;
        bool operator != (const Complex<T>& other) const noexcept;
        bool Compare(const Complex<T>& other, const T& epsilon2) const noexcept;

        Vector2<T>& AsVect() noexcept;
        const Vector2<T>& AsVect() const noexcept;

        static constexpr Complex<T> one = {1, 0};
        static constexpr Complex<T> i = {0, 1};
        static constexpr Complex<T> zero = {0, 0};
    };

    using ComplexD = Complex<double>;
    using ComplexF = Complex<float>;
    using ComplexI = Complex<int>;

//==============================================================================================================================================

    template<typename T>
    struct Rotator2
    {
        // Constructors
        Rotator2() = delete;
        Rotator2(const Rotator2<T>& other) noexcept = default;
        Rotator2(Rotator2<T>&& other) noexcept = default;
        Rotator2<T>& operator=(const Rotator2<T>& other) noexcept = default;
        Rotator2<T>& operator=(Rotator2<T>&& other) noexcept = default;

        const T& GetRe() const noexcept;
        const T& GetIm() const noexcept;

        //same as operator const Vector2();
        const Complex<T>& AsComplex() const noexcept;
        operator const Complex<T>& () const noexcept;

        RotMatrix2x2<T> MakeMatrix() const noexcept;

        Rotator2<T> operator*(const Rotator2<T> other) const noexcept;

        Direction2<T>& RepairFast();
        Direction2<T>& Repair();
        // the sqrt_calculator should have method "Sqrt(const T&) -> T&&"
        template<typename MathT>
        Direction2<T>& Repair(MathT&& sqrt_calculator);

        bool operator==(const Direction2<T>& other) const noexcept;
        bool operator!=(const Direction2<T>& other) const noexcept;
        bool Compare(const Direction2<T>& other, const T& epsilon2) const noexcept;

        Direction2<T>& AsVect() noexcept;
        const Direction2<T>& AsVect() const noexcept;

        static constexpr Rotator2<T> identity = Complex<T>{1, 0};
        static constexpr Rotator2<T> orthogonal_left = Complex<T>{0, 1};
        static constexpr Rotator2<T> orthogonal_right = Complex<T>{0, -1};
        static constexpr Rotator2<T> turn_around = Complex<T>{-1, 0};
        
        static Rotator2<T> RadianRot(const T& angle) noexcept;
        // the sin_cos_calculator should have method "Sin(const T&) -> T&&" and "Cos(const T&) -> T&&"
        template<typename MathT>
        static Rotator2<T> RadianRot(const T& angle, MathT&& sin_cos_calculator);

    private:
        Complex<T> value;
        
        friend struct Complex<T>;

        explicit Rotator2(const Complex<T>& complex) noexcept;
        explicit Rotator2(Complex<T>&& complex) noexcept;
        Rotator2<T>& operator=(const Complex<T>& complex) noexcept;
        Rotator2<T>& operator=(Complex<T>&& complex) noexcept;
    };

//==============================================================================================================================================

    template<typename T>
    struct Matrix2x2
    {
        Vector2<T> line1 = {0, 0};
        Vector2<T> line2 = {0, 0};

        // Compound assignment operators
        Matrix2x2<T>& operator+=(const Matrix2x2<T>& other) noexcept;
        Matrix2x2<T>& operator-=(const Matrix2x2<T>& other) noexcept;
        Matrix2x2<T>& operator*=(const T& scalar) noexcept;
        Matrix2x2<T>& operator/=(const T& scalar);
        Matrix2x2<T>& operator*=(const Matrix2x2<T>& other) const noexcept; // for gpt: define the method via operator *

        // Unary arithmetic operators
        Matrix2x2<T> operator-() const noexcept;

        // Binary arithmetic operators
        Matrix2x2<T> operator+(const Matrix2x2<T>& other) const noexcept; // for gpt: define this method and others via copying and operator += or another changing operator 
        Matrix2x2<T> operator-(const Matrix2x2<T>& other) const noexcept;
        Matrix2x2<T> operator*(const T& scalar) const noexcept;
        Matrix2x2<T> operator/(const T& scalar) const;
        Matrix2x2<T> operator*(const Matrix2x2<T>& other) const noexcept; // for gpt: define the method via transpose and Vector2::Dot();

        // Comparison operators
        bool operator==(const Matrix2x2<T>& other) const noexcept;
        bool operator!=(const Matrix2x2<T>& other) const noexcept;
        bool Compare(const Matrix2x2<T>& other, const T& epsilon2) const noexcept; // for gpt: the method works like ==, but it is tolerant to arithmetical mistake.

        // Transpose
        Matrix2x2<T> Transposed() const noexcept;

        // Determinant
        T Det() const noexcept;

        // Inverse
        Matrix2x2<T> Inversed() const;

        static constexpr Matrix2x2<T> one = 
        {
            { 1, 0 },
            { 0, 1 }
        };
        static constexpr Matrix2x2<T> zero = 
        {
            { 0, 0 },
            { 0, 0 }
        };

        Transform2dUniform<T> MakeTransform2D(const Vector2<T>& offset) const noexcept;
        Transform3dUniform<T> MakeTransform3D(const Vector2<T>& offset) const noexcept;

        static std::pair<Matrix2x2<T>, Vector2<T>> ReadTransform(const Transform2dUniform<T>& transform) noexcept;
        static std::pair<Matrix2x2<T>, Vector2<T>> ReadTransform(const Transform3dUniform<T>& transform) noexcept;
    };

    using Matrix2x2D = Matrix2x2<double>;
    using Matrix2x2F = Matrix2x2<float>;
    using Matrix2x2I = Matrix2x2<int>;

//==============================================================================================================================================

    template<typename T>
    struct RotMatrix2x2
    {
        const Direction2<T>& Line1() const noexcept;
        const Direction2<T>& Line2() const noexcept;
        const Direction2<T>& Column1() const noexcept;
        const Direction2<T>& Column2() const noexcept;

        // there is no riliable way to repair rot_matrix. not recomended to accumulate arithmetical error
        RotMatrix2x2 operator * (const RotMatrix2x2& other) const noexcept;

        // same as transpose
        RotMatrix2x2<T>& Inverse() noexcept;
        // same as transposed
        RotMatrix2x2<T> Inversed() const noexcept;

        const Matrix2x2<T>& AsMatrix() const noexcept;

        static constexpr RotMatrix2x2<T> identity = {Matrix2x2<T>::identity};
        static constexpr RotMatrix2x2<T> orthogonal_left = {Matrix2x2<T>::orthogonal_left};
        static constexpr RotMatrix2x2<T> orthogonal_right = {Matrix2x2<T>::orthogonal_right};
        static constexpr RotMatrix2x2<T> turn_around = {Matrix2x2<T>::turn_around};

    private:

        friend struct Rotator2<T>;

        Matrix2x2<T> value = { { 1, 0 }, { 0, 1 } };
    };

//##############################################################################################################################################

#if _2D_IS_TESTED_

    template<typename T>
    struct Vector3
    {
        T x = {0};
        T y = {0};
        T z = {0};

        Vector3<T>& operator+=(const Vector3<T>& other) noexcept;
        Vector3<T>& operator-=(const Vector3<T>& other) noexcept;
        Vector3<T>& operator*=(const T& scalar) noexcept;
        Vector3<T>& operator/=(const T& scalar);
        Vector3<T>& operator*=(const Quaternion<T> complex) noexcept;

        T Abs2() const noexcept;
        T Abs() const noexcept;
        // sqrt_calculator should have method "Sqrt(const T&) -> T&&"
        template<typename MathT>
        T Abs(MathT&& sqrt_calculator) const noexcept;

        Vector3<T> operator+(const Vector3<T>& other) const noexcept;
        Vector3<T> operator-(const Vector3<T>& other) const noexcept;
        Vector3<T> operator*(const T& scalar) const noexcept;
        Vector3<T> operator/(const T& scalar) const;
        Vector3<T> operator*(const Complex<T> complex) const noexcept;
        Vector3<T> operator*(const Matrix3x3<T>& matrix) const noexcept;

        T Dot(const Vector3& other) const noexcept;
        Vector3<T> Cross(const Vector3& other) const noexcept;
        Vector3<T> operator-() const noexcept;

        Vector3<T>& Normalize();
        Direction3<T> Normalized() const;
        // sqrt_calculator should have method "Sqrt(const T&) -> T&&"
        template<typename MathT>
        Vector3<T>& Normalize(MathT&& sqrt_calculator);
        // sqrt_calculator should have method "Sqrt(const T&) -> T&&"
        template<typename MathT>
        Direction3<T> Normalized(MathT&& sqrt_calculator) const;

        bool operator==(const Vector3<T>& other) const noexcept;
        bool operator!=(const Vector3<T>& other) const noexcept;
        bool Compare(const Vector3<T>& other, const T& epsilon2) const noexcept;

        static constexpr Vector3<T> up = {0, 1, 0};
        static constexpr Vector3<T> forward = {0, 0, 1};
        static constexpr Vector3<T> right = {1, 0, 0};
        static constexpr Vector3<T> left = -right;
        static constexpr Vector3<T> down = -up;
        static constexpr Vector3<T> back = -forward;
        static constexpr Vector3<T> zero = {0, 0, 0};
        static constexpr Vector3<T> ones = {1, 1, 1};
    };

    using Vector3D = Vector3<double>;
    using Vector3F = Vector3<float>;
    using Vector3I = Vector3<int>;

//==============================================================================================================================================

    template<typename T>
    struct Quaternion
    {
        T re = {0};
        Vector3<T> im = Vector3<T>::zero;

        Quaternion<T>& operator+=(const Quaternion<T>& other) noexcept;
        Quaternion<T>& operator-=(const Quaternion<T>& other) noexcept;
        Quaternion<T>& operator*=(const Quaternion<T>& other) noexcept;
        Quaternion<T>& operator*=(const T& scalar) noexcept;
        Quaternion<T>& operator/=(const T& scalar);

        T Abs2() const noexcept;
        T Abs() const noexcept;
        // sqrt_calculator should have method "Sqrt(const T&) -> T&&"
        template<typename MathT>
        T Abs(MathT&& sqrt_calculator) const noexcept;

        RotMatrix3x3<T> MakeMatrix() const noexcept;

        Quaternion<T> operator+(const Quaternion<T>& other) const noexcept;
        Quaternion<T> operator-(const Quaternion<T>& other) const noexcept;
        Quaternion<T> operator*(const Quaternion<T>& other) const noexcept;
        Quaternion<T> operator*(const T& scalar) const noexcept;
        Quaternion<T> operator/(const T& scalar) const;

        Quaternion<T> operator-() const noexcept;
        // same as 1 / Quaternion<T>{re, im}
        Quaternion<T> Inverted() const;
        Quaternion<T> Conjugate() const noexcept;

        Quaternion<T>& Normalize();
        Rotator3<T> Normalized() const;
        // sqrt_calculator should have method "Sqrt(const T&) -> T&&"
        template<typename MathT>
        Quaternion<T>& Normalize(MathT&& sqrt_calculator);
        // sqrt_calculator should have method "Sqrt(const T&) -> T&&"
        template<typename MathT>
        Rotator3<T> Normalized(MathT&& sqrt_calculator) const;

        bool operator==(const Quaternion<T>& other) const noexcept;
        bool operator!=(const Quaternion<T>& other) const noexcept;
        bool Compare(const Quaternion<T>& other, const T& epsilon2) const noexcept;

        Vector3<T>& AsVect() noexcept;
        const Vector3<T>& AsVect() const noexcept;

        static constexpr Quaternion<T> one = {1, Vector3<T>::zero};
        static constexpr Quaternion<T> i = {0, Vector3<T>::right};
        static constexpr Quaternion<T> j = {0, Vector3<T>::up};
        static constexpr Quaternion<T> k = {0, Vector3<T>::forward};
        static constexpr Quaternion<T> zero = {0, Vector3<T>::zero};
    };

    using QuatD = Quaternion<double>;
    using QuatF = Quaternion<float>;
    using QuatI = Quaternion<int>;

#endif // _2D_IS_TESTED_

}

//==============================================================================================================================================

#include "Linal_Vector2_Definitions.h"
#include "Linal_Complex_Definitions.h"
#include "Linal_Matrix2x2_Definitions.h"
#include "Linal_Direction2_Definitions.h"
#include "Linal_Rotator2_Definitions.h"
#include "Linal_RotMatrix2x2_Definitions.h"
