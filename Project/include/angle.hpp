#ifndef ANGLE_HPP
#define ANGLE_HPP


/**
 * @file angle.hpp
 * @brief float point Degrees and Radians classes, along with literal operators.
 */

#include <ostream>

/** \addtogroup math
 *  @{
 */

/// Constant pi
constexpr float pi =
        3.1415926535897932384626433832795028841971693993751058209749445923078164062f;

namespace detail {
constexpr float deg2rad = pi / 180;
constexpr float rad2deg = 180 / pi;
}

class Degree;

/// The Radian class
class Radian
{
public:
    /// Default constructor
    constexpr Radian() : value_{0} {}

    /// Degree to Radian conversion function
    constexpr Radian(Degree degree);

    /// Construct radian from a number
    constexpr explicit Radian(float value) : value_{value} {}

    /// Returns value of underlying float
    constexpr float value() const { return value_; }

    /// Return the negation of the Radian
    constexpr Radian operator-() const { return Radian{-value_}; }

    Radian& operator+=(Radian rhs);
    Radian& operator-=(Radian rhs);
    Radian& operator*=(float rhs);
    Radian& operator/=(float rhs);

private:
    float value_;
};

/// The Degree class
class Degree
{
public:
    constexpr Degree() : value_{0} {}

    /// Radian to Degree conversion function
    constexpr Degree(Radian radian);

    /// Constructs degree from a number
    constexpr explicit Degree(float value);

    /// Gets value of underlying float
    constexpr float value() const { return value_; }

    /// Return the negation of the Degree
    constexpr Degree operator-() const { return Degree{-value_}; }

    Degree& operator+=(Degree rhs);
    Degree& operator-=(Degree rhs);
    Degree& operator*=(float rhs);
    Degree& operator/=(float rhs);


private:
    float value_;
};


/**
 * @brief Returns the sum of two radians.
 * @related Radian
 */
constexpr Radian operator+(Radian lhs, Radian rhs) {
    return Radian(lhs.value() + rhs.value());
}

/**
 * @brief Returns the difference of two radians.
 * @related Radian
 */
constexpr Radian operator-(Radian lhs, Radian rhs) {
    return Radian(lhs.value() - rhs.value());
}

/**
 * @brief Returns the product of a radian and a scalar.
 * @related Radian
 */
constexpr Radian operator*(Radian lhs, float rhs) {
    return Radian(lhs.value() * rhs);
}

/**
 * @brief Returns the product of a radian and a scalar.
 * @related Radian
 */
constexpr Radian operator*(float lhs, Radian rhs) {
    return Radian(lhs * rhs.value());
}

/**
 * @brief Divides a radian value by another radian.
 * @related Radian
 */
constexpr float operator/(Radian lhs, Radian rhs) {
    return lhs.value() / rhs.value();
}

/**
 * @brief Divides a radian value by a scalar.
 * @related Radian
 */
constexpr Radian operator/(Radian lhs, float rhs) {
    return Radian(lhs.value() / rhs);
}

/**
 * @brief Returns the sum of two degrees.
 * @related Degree
 */
constexpr Degree operator+(Degree lhs, Degree rhs) {
    return Degree(lhs.value() + rhs.value());
}

/**
 * @brief Returns the difference of two degrees.
 * @related Degree
 */
constexpr Degree operator-(Degree lhs, Degree rhs) {
    return Degree(lhs.value() - rhs.value());
}

/**
 * @brief Returns the product of a degree and a scalar.
 * @related Degree
 */
constexpr Degree operator*(Degree lhs, float rhs) {
    return Degree(lhs.value() * rhs);
}

/**
 * @brief Returns the product of a degree and a scalar.
 * @related Degree
 */
constexpr Degree operator*(float lhs, Degree rhs) {
    return Degree(lhs * rhs.value());
}

/**
 * @brief Divides a degree value by a scalar.
 * @related Degree
 */
constexpr float operator/(Degree lhs, Degree rhs) {
    return lhs.value() / rhs.value();
}

/**
 * @brief Divides a degree value by another degree.
 * @related Degree
 */
constexpr Degree operator/(Degree lhs, float rhs) {
    return Degree(lhs.value() / rhs);
}

/**
 * @related Radian
 */
constexpr bool operator==(Radian lhs, Radian rhs) {
    return lhs.value() == rhs.value();
}

/**
 * @related Radian
 */
constexpr bool operator!=(Radian lhs, Radian rhs) {
    return lhs.value() != rhs.value();
}

/**
 * @related Radian
 */
constexpr bool operator<(Radian lhs, Radian rhs) {
    return lhs.value() < rhs.value();
}

/**
 * @related Radian
 */
constexpr bool operator>(Radian lhs, Radian rhs) {
    return lhs.value() > rhs.value();
}

/**
 * @related Radian
 */
constexpr bool operator<=(Radian lhs, Radian rhs) {
    return lhs.value() <= rhs.value();
}

/**
 * @related Radian
 */
constexpr bool operator>=(Radian lhs, Radian rhs) {
    return lhs.value() >= rhs.value();
}

/**
 * @related Degree
 */
constexpr bool operator==(Degree lhs, Degree rhs) {
    return lhs.value() == rhs.value();
}

/**
 * @related Degree
 */
constexpr bool operator!=(Degree lhs, Degree rhs) {
    return lhs.value() != rhs.value();
}

/**
 * @related Degree
 */
constexpr bool operator<(Degree lhs, Degree rhs) {
    return lhs.value() < rhs.value();
}

/**
 * @related Degree
 */
constexpr bool operator>(Degree lhs, Degree rhs) {
    return lhs.value() > rhs.value();
}

/**
 * @related Degree
 */
constexpr bool operator<=(Degree lhs, Degree rhs) {
    return lhs.value() <= rhs.value();
}

/**
 * @related Degree
 */
constexpr bool operator>=(Degree lhs, Degree rhs) {
    return lhs.value() >= rhs.value();
}

/// Adds rhs to this radian
inline Radian &Radian::operator+=(Radian rhs) {
    value_ += rhs.value(); return *this;
}

/// Subtracts rhs from this radian
inline Radian &Radian::operator-=(Radian rhs) {
    value_ -= rhs.value(); return *this;
}

/// Multiplies a scalar rhs to this radian
inline Radian &Radian::operator*=(float rhs) {
    value_ *= rhs; return *this;
}

/// Divides a scalar rhs to this radian
inline Radian &Radian::operator/=(float rhs) {
    value_ /= rhs; return *this;
}

/// Adds rhs to this degree
inline Degree &Degree::operator+=(Degree rhs) {
    value_ += rhs.value(); return *this;
}

/// Subtracts rhs from this degree
inline Degree &Degree::operator-=(Degree rhs) {
    value_ -= rhs.value(); return *this;
}

/// Multiplies a scalar rhs to this degree
inline Degree &Degree::operator*=(float rhs) {
    value_ *= rhs; return *this;
}

/// Divides a scalar rhs to this degree
inline Degree &Degree::operator/=(float rhs) {
    value_ /= rhs; return *this;
}

inline constexpr Radian::Radian(Degree degree)
    :value_{degree.value() * detail::deg2rad} {}

inline constexpr Degree::Degree(Radian radian)
    :value_{radian.value() * detail::rad2deg} {}

inline constexpr Degree::Degree(float value) :value_{value} {}

// Output Radian and Degree into stream
std::ostream& operator<<(std::ostream& os, Radian radian);
std::ostream& operator<<(std::ostream& os, Degree degree);

/// Literal for radian
constexpr Radian operator"" _rad(long double r) {
    return Radian(static_cast<float>(r));
}

/// Literal for degree
constexpr Degree operator"" _deg(long double d) {
    return Degree(static_cast<float>(d));
}

/** @}*/

#endif
