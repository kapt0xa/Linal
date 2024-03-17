#pragma once

namespace linal // structures declarations
{
    template<typename T>
    struct Complex;

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
        Vector2<T> OrtogonalR() const noexcept;
        Vector2<T> OrtogonalL() const noexcept;

        Vector2<T>& Normalize();
        Vector2<T> Normalized() const;
        // the sqrt_calculator should have method "Sqrt(const T&) -> T&&"
        template<typename MathT>
        Vector2<T>& Normalize(MathT&& sqrt_calculator);
        // the sqrt_calculator should have method "Sqrt(const T&) -> T&&"
        template<typename MathT>
        Vector2<T>& Normalized(MathT&& sqrt_calculator);

        bool operator == (const Vector2<T>& other) const noexcept;
        bool operator != (const Vector2<T>& other) const noexcept;
        bool Compare(const Vector2<T>& other, const T& epsilon2) const noexcept;

        Complex<T>& AsComplex() noexcept;
        const Complex<T>& AsComplex() const noexcept;
    };

    using Vector2f = Vector2<float>;

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
        Complex<T>& Normalized(MathT&& sqrt_calculator);

        bool operator == (const Complex<T>& other) const noexcept;
        bool operator != (const Complex<T>& other) const noexcept;
        bool Compare(const Complex<T>& other, const T& epsilon2) const noexcept;

        Vector2<T>& AsVect() noexcept;
        const Vector2<T>& AsVect() const noexcept;
    };

    template<typename T>
    struct Matrix2d
    {
        Vector2<T> line1;
        Vector2<T> line2;

        // Compound assignment operators
        Matrix2d<T>& operator+=(const Matrix2d<T>& other) noexcept;
        Matrix2d<T>& operator-=(const Matrix2d<T>& other) noexcept;
        Matrix2d<T>& operator*=(const T& scalar) noexcept;
        Matrix2d<T>& operator/=(const T& scalar) noexcept;

        // Unary arithmetic operators
        Matrix2d<T> operator-() const noexcept;

        // Binary arithmetic operators
        Matrix2d<T> operator+(const Matrix2d<T>& other) const noexcept;
        Matrix2d<T> operator-(const Matrix2d<T>& other) const noexcept;
        Matrix2d<T> operator*(const T& scalar) const noexcept;
        Matrix2d<T> operator/(const T& scalar) const noexcept;
        Matrix2d<T> operator*(const Matrix2d<T>& other) const noexcept;

        // Comparison operators
        bool operator==(const Matrix2d<T>& other) const noexcept;
        bool operator!=(const Matrix2d<T>& other) const noexcept;

        // Access operators
        Vector2<T>& operator[](size_t index) noexcept;
        const Vector2<T>& operator[](size_t index) const noexcept;

        // Transpose
        Matrix2d<T> Transpose() const noexcept;

        // Determinant
        T Det() const noexcept;

        // Inverse
        Matrix2d<T> Inverse() const noexcept;
    };
}

namespace linal // Vector2 methods definitions
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
        return Vector2<T>(*this) /= scalar;
    }

    template<typename T>
    Vector2<T> Vector2<T>::operator * (const Complex<T> complex) const noexcept
    {
        return Vector2<T>(*this) *= complex;
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
    Vector2<T> Vector2<T>::OrtogonalR() const noexcept
    {
        return { y, -x };
    }

    template<typename T>
    Vector2<T> Vector2<T>::OrtogonalL() const noexcept
    {
        return { -y, x };
    }

    template<typename T>
    Vector2<T>& Vector2<T>::Normalize()
    {
        return *this /= Abs();
    }

    template<typename T>
    Vector2<T> Vector2<T>::Normalized() const
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
    Vector2<T>& Vector2<T>::Normalized(MathT&& sqrt_calculator)
    {
        return Vector2<T>(*this) /= Abs(std::forward(sqrt_calculator));
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
} // Vector2 methods definitions

namespace linal // Complex methods definitions
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
    Complex<T> Complex<T>::Normalized() const 
    {
        return Complex<T>(*this).Normalize();
    }

    template<typename T>
    template<typename MathT>
    Complex<T>& Complex<T>::Normalize(MathT&& sqrt_calculator) 
    {
        AsVect().Normalize(sqrt_calculator);
        return *this;
    }

    template<typename T>
    template<typename MathT>
    Complex<T>& Complex<T>::Normalized(MathT&& sqrt_calculator) 
    {
        return Complex<T>(*this).Normalize(sqrt_calculator);
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

} // Complex methods definitions

// end of file
