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
} // namespace detail

class Degree;

/// The Radian class
class Radian {
public:
  /// Default constructor
  constexpr Radian() : value_{0} {}

  /// Degree to Radian implicit conversion function
  constexpr Radian(Degree degree); // NOLINT

  /// Construct radian from a number
  constexpr explicit Radian(float value) : value_{value} {}

  /// Returns value of underlying float
  constexpr float value() const { return value_; }

  /// Return the negation of the Radian
  constexpr Radian operator-() const { return Radian{-value_}; }

  constexpr Radian& operator+=(Radian rhs);
  constexpr Radian& operator-=(Radian rhs);
  constexpr Radian& operator*=(float rhs);
  constexpr Radian& operator/=(float rhs);

private:
  float value_;
};

/// The Degree class
class Degree {
public:
  constexpr Degree() : value_{0} {}

  /// Radian to Degree implicit conversion function
  constexpr Degree(Radian radian); // NOLINT

  /// Constructs degree from a number
  constexpr explicit Degree(float value);

  /// Gets value of underlying float
  constexpr float value() const { return value_; }

  /// Return the negation of the Degree
  constexpr Degree operator-() const { return Degree{-value_}; }

  constexpr Degree& operator+=(Degree rhs);
  constexpr Degree& operator-=(Degree rhs);
  constexpr Degree& operator*=(float rhs);
  constexpr Degree& operator/=(float rhs);

private:
  float value_;
};

/**
 * @brief Returns the sum of two radians.
 * @related Radian
 */
constexpr Radian operator+(Radian lhs, Radian rhs)
{
  return Radian(lhs.value() + rhs.value());
}

/**
 * @brief Returns the difference of two radians.
 * @related Radian
 */
constexpr Radian operator-(Radian lhs, Radian rhs)
{
  return Radian(lhs.value() - rhs.value());
}

/**
 * @brief Returns the product of a radian and a scalar.
 * @related Radian
 */
constexpr Radian operator*(Radian lhs, float rhs)
{
  return Radian(lhs.value() * rhs);
}

/**
 * @brief Returns the product of a radian and a scalar.
 * @related Radian
 */
constexpr Radian operator*(float lhs, Radian rhs)
{
  return Radian(lhs * rhs.value());
}

/**
 * @brief Divides a radian value by another radian.
 * @related Radian
 */
constexpr float operator/(Radian lhs, Radian rhs)
{
  return lhs.value() / rhs.value();
}

/**
 * @brief Divides a radian value by a scalar.
 * @related Radian
 */
constexpr Radian operator/(Radian lhs, float rhs)
{
  return Radian(lhs.value() / rhs);
}

/**
 * @brief Returns the sum of two degrees.
 * @related Degree
 */
constexpr Degree operator+(Degree lhs, Degree rhs)
{
  return Degree(lhs.value() + rhs.value());
}

/**
 * @brief Returns the difference of two degrees.
 * @related Degree
 */
constexpr Degree operator-(Degree lhs, Degree rhs)
{
  return Degree(lhs.value() - rhs.value());
}

/**
 * @brief Returns the product of a degree and a scalar.
 * @related Degree
 */
constexpr Degree operator*(Degree lhs, float rhs)
{
  return Degree(lhs.value() * rhs);
}

/**
 * @brief Returns the product of a degree and a scalar.
 * @related Degree
 */
constexpr Degree operator*(float lhs, Degree rhs)
{
  return Degree(lhs * rhs.value());
}

/**
 * @brief Divides a degree value by a scalar.
 * @related Degree
 */
constexpr float operator/(Degree lhs, Degree rhs)
{
  return lhs.value() / rhs.value();
}

/**
 * @brief Divides a degree value by another degree.
 * @related Degree
 */
constexpr Degree operator/(Degree lhs, float rhs)
{
  return Degree(lhs.value() / rhs);
}

/**
 * @related Radian
 */
constexpr bool operator==(Radian lhs, Radian rhs)
{
  return lhs.value() == rhs.value();
}

/**
 * @related Radian
 */
constexpr bool operator!=(Radian lhs, Radian rhs)
{
  return lhs.value() != rhs.value();
}

/**
 * @related Radian
 */
constexpr bool operator<(Radian lhs, Radian rhs)
{
  return lhs.value() < rhs.value();
}

/**
 * @related Radian
 */
constexpr bool operator>(Radian lhs, Radian rhs)
{
  return lhs.value() > rhs.value();
}

/**
 * @related Radian
 */
constexpr bool operator<=(Radian lhs, Radian rhs)
{
  return lhs.value() <= rhs.value();
}

/**
 * @related Radian
 */
constexpr bool operator>=(Radian lhs, Radian rhs)
{
  return lhs.value() >= rhs.value();
}

/**
 * @related Degree
 */
constexpr bool operator==(Degree lhs, Degree rhs)
{
  return lhs.value() == rhs.value();
}

/**
 * @related Degree
 */
constexpr bool operator!=(Degree lhs, Degree rhs)
{
  return lhs.value() != rhs.value();
}

/**
 * @related Degree
 */
constexpr bool operator<(Degree lhs, Degree rhs)
{
  return lhs.value() < rhs.value();
}

/**
 * @related Degree
 */
constexpr bool operator>(Degree lhs, Degree rhs)
{
  return lhs.value() > rhs.value();
}

/**
 * @related Degree
 */
constexpr bool operator<=(Degree lhs, Degree rhs)
{
  return lhs.value() <= rhs.value();
}

/**
 * @related Degree
 */
constexpr bool operator>=(Degree lhs, Degree rhs)
{
  return lhs.value() >= rhs.value();
}

/// Adds rhs to this radian
constexpr Radian& Radian::operator+=(Radian rhs)
{
  value_ += rhs.value();
  return *this;
}

/// Subtracts rhs from this radian
constexpr Radian& Radian::operator-=(Radian rhs)
{
  value_ -= rhs.value();
  return *this;
}

/// Multiplies a scalar rhs to this radian
constexpr Radian& Radian::operator*=(float rhs)
{
  value_ *= rhs;
  return *this;
}

/// Divides a scalar rhs to this radian
constexpr Radian& Radian::operator/=(float rhs)
{
  value_ /= rhs;
  return *this;
}

/// Adds rhs to this degree
constexpr Degree& Degree::operator+=(Degree rhs)
{
  value_ += rhs.value();
  return *this;
}

/// Subtracts rhs from this degree
constexpr Degree& Degree::operator-=(Degree rhs)
{
  value_ -= rhs.value();
  return *this;
}

/// Multiplies a scalar rhs to this degree
constexpr Degree& Degree::operator*=(float rhs)
{
  value_ *= rhs;
  return *this;
}

/// Divides a scalar rhs to this degree
constexpr Degree& Degree::operator/=(float rhs)
{
  value_ /= rhs;
  return *this;
}

constexpr Radian::Radian(Degree degree)
    : value_{degree.value() * detail::deg2rad}
{
}

constexpr Degree::Degree(Radian radian)
    : value_{radian.value() * detail::rad2deg}
{
}

constexpr Degree::Degree(float value) : value_{value} {}

// Output Radian and Degree into stream
std::ostream& operator<<(std::ostream& os, Radian radian);
std::ostream& operator<<(std::ostream& os, Degree degree);

/// Literal for radian
constexpr Radian operator"" _rad(long double r)
{
  return Radian(static_cast<float>(r));
}

/// Literal for degree
constexpr Degree operator"" _deg(long double d)
{
  return Degree(static_cast<float>(d));
}

/** @}*/ // math group

#endif
