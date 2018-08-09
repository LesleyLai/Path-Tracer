#pragma once

#include <algorithm>
#include <cmath>
#include <functional>
#include <ostream>
#include <type_traits>

/**
 * @file vector.hpp
 * @brief Header file for the general fixed sized vector template.
 */

/** \addtogroup math
 *  @{
 */

template <typename T, size_t size> struct Vector;

/**
 * @brief Base class of Vector contains common members for all specialization.
 */
template <typename T, size_t size> struct Vector_base {
  using size_type = size_t;
  using value_type = T;
  using Derived = Vector<T, size>;

  Derived& underlying() { return static_cast<Derived&>(*this); }
  Derived const& underlying() const
  {
    return static_cast<Derived const&>(*this);
  }

  constexpr value_type& operator[](size_type i) noexcept
  {
    return underlying().elems[i];
  }
  constexpr const value_type& operator[](size_type i) const noexcept
  {
    return underlying().elems[i];
  }

  /**
   * @brief Returns square of the length of the vector
   */
  constexpr value_type length_square() const noexcept
  {
    return dot(underlying(), underlying());
  }

  /**
   * @brief Returns length of the vector
   */
  value_type length() const noexcept { return std::sqrt(length_square()); }

  constexpr T* begin() noexcept { return std::begin(underlying().elems); }
  constexpr T* end() noexcept { return std::end(underlying().elems); }
  constexpr const T* begin() const noexcept { return cbegin(); }
  constexpr const T* end() const noexcept { return cend(); }
  constexpr const T* cbegin() const noexcept
  {
    return std::begin(underlying().elems);
  }
  constexpr const T* cend() const noexcept
  {
    return std::end(underlying().elems);
  }

protected:
  // Prevent from outside client from instantiate Vector_base
  constexpr Vector_base() noexcept = default;
};

/**
 * @brief Common functions for that all vector spetializations need
 *
 * @related Vector
 */

/**
 * @brief Template of fix-sized vectors
 */
template <typename T, size_t size> struct Vector : Vector_base<T, size> {
  T elems[size];
};

/**
 * @brief 2D Vector specialization
 * @see Vector
 */
template <typename T> struct Vector<T, 2> : Vector_base<T, 2> {
  union {
    struct {
      T x, y;
    };
    T elems[2];
  };

  constexpr Vector() noexcept = default;
  constexpr Vector(T xx, T yy) noexcept : x{xx}, y{yy} {}
};

/**
 * @brief 3D Vector specialization
 * @see Vector
 */
template <typename T> struct Vector<T, 3> : Vector_base<T, 3> {
  union {
    struct {
      T x, y, z;
    };
    struct {
      Vector<T, 2> xy;
    };
    T elems[3];
  };

  constexpr Vector() noexcept = default;
  constexpr Vector(T xx, T yy, T zz) noexcept : x{xx}, y{yy}, z{zz} {}
  constexpr Vector(Vector<T, 2> xy, T zz) noexcept : x{xy.x}, y{xy.y}, z{zz} {}
};

/**
 * @brief 4D Vector specialization
 * @see Vector
 */
template <typename T> struct Vector<T, 4> : Vector_base<T, 4> {
  union {
    struct {
      T x, y, z, w;
    };
    struct {
      Vector<T, 2> xy;
    };
    struct {
      Vector<T, 3> xyz;
    };
    T elems[4];
  };

  constexpr Vector() noexcept = default;
  constexpr Vector(T xx, T yy, T zz, T ww) noexcept : x{xx}, y{yy}, z{zz}, w{ww}
  {
  }
  constexpr Vector(Vector<T, 3> xyz, T ww) noexcept
      : x{xyz.x}, y{xyz.y}, z{xyz.z}, w{ww}
  {
  }
};

namespace detail {
template <size_t size, typename T, typename Binary_op>
constexpr Vector<T, size> binary_op(const Vector<T, size>& lhs,
                                    const Vector<T, size>& rhs,
                                    Binary_op f) noexcept
{
  Vector<T, size> result;
  for (size_t i = 0; i != size; ++i) {
    result[i] = f(lhs[i], rhs[i]);
  }
  return result;
}

template <size_t size, typename T, typename Binary_op>
constexpr Vector<T, size> binary_op(const Vector<T, size>& lhs, T rhs,
                                    Binary_op f) noexcept
{
  Vector<T, size> result;
  std::transform(std::begin(lhs), std::end(lhs), std::begin(result),
                 [=](T x) { return f(x, rhs); });
  return result;
}

} // namespace detail

/// Adds rhs to this vector
/// @related Vector
template <typename T, size_t size>
constexpr Vector<T, size>& operator+=(Vector<T, size>& lhs,
                                      const Vector<T, size>& rhs) noexcept
{
  for (size_t i = 0; i != size; ++i) {
    lhs[i] += rhs[i];
  }
  return lhs;
}

/// Subtracts rhs from this vector
/// @related Vector
template <typename T, size_t size>
constexpr Vector<T, size>& operator-=(Vector<T, size>& lhs,
                                      const Vector<T, size>& rhs) noexcept
{
  for (size_t i = 0; i != size; ++i) {
    lhs[i] -= rhs[i];
  }
  return lhs;
}

/// Multiplies a scalar rhs to this vector
/// @related Vector
template <typename T, size_t size>
constexpr Vector<T, size>& operator*=(Vector<T, size>& lhs, T rhs) noexcept
{
  std::transform(std::begin(lhs), std::end(lhs), std::begin(lhs),
                 [=](T x) { return x * rhs; });
  return lhs;
}

/// Divides a scalar rhs to this vector
/// @related Vector
template <typename T, size_t size>
constexpr Vector<T, size>& operator/=(Vector<T, size>& lhs, T rhs) noexcept
{
  T inv = 1 / rhs;

  std::transform(std::begin(lhs), std::end(lhs), std::begin(lhs),
                 [=](T elem) { return elem * inv; });

  return lhs;
}

/// Return the negation of the vector
/// @related Vector
template <typename T, size_t size>
constexpr Vector<T, size> operator-(const Vector<T, size>& vector) noexcept
{
  Vector<T, size> result;
  std::transform(std::begin(vector), std::end(vector), std::begin(result),
                 std::negate<T>());
  return result;
}

/**
 * @brief Returns the sum of two vector.
 * @related Vector
 */
template <typename T, size_t size>
constexpr Vector<T, size> operator+(const Vector<T, size>& lhs,
                                    const Vector<T, size>& rhs) noexcept
{
  return detail::binary_op(lhs, rhs, std::plus<T>());
}

/**
 * @brief Returns the result of subtract rhs vector from lhs vector.
 * @related Vector
 */
template <typename T, size_t size>
constexpr Vector<T, size> operator-(const Vector<T, size>& lhs,
                                    const Vector<T, size>& rhs) noexcept
{
  return detail::binary_op(lhs, rhs, std::minus<T>());
}

/**
 * @brief Calculates the scalar product of vector with the given value.
 * @related Vector
 */
template <typename T, size_t size>
constexpr Vector<T, size> operator*(const Vector<T, size>& lhs, T rhs) noexcept
{
  return detail::binary_op(lhs, rhs, std::multiplies<T>());
}

/**
 * @brief Calculates the scalar product of vector with the given value.
 * @related Vector
 */
template <typename T, size_t size>
constexpr Vector<T, size> operator*(T lhs, const Vector<T, size>& rhs) noexcept
{
  return rhs * lhs;
}

/**
 * @brief Calculates the scalar division of this vector with the given value.
 * @related Vector
 */
template <typename T, size_t size>
constexpr Vector<T, size> operator/(const Vector<T, size>& lhs, T rhs) noexcept
{
  return detail::binary_op(lhs, 1 / rhs, std::multiplies<T>());
}

/**
 * @brief Returns the dot product between the specified vectors.
 * @related Vector
 */
template <typename T, size_t size>
constexpr T dot(const Vector<T, size>& lhs, const Vector<T, size>& rhs) noexcept
{
  T result = 0;
  for (size_t i = 0; i != size; ++i) {
    result += lhs[i] * rhs[i];
  }
  return result;
}

/**
 * @brief Normalizes a vector and returns the result.
 * @related Vector
 */
template <typename T, size_t size>
constexpr Vector<T, size> normalize(const Vector<T, size>& v) noexcept
{
  return v / v.length();
}

/**
 * @brief Returns the cross product between the specified vectors.
 * @related Vector
 */
template <typename T>
constexpr Vector<T, 3> cross(const Vector<T, 3>& lhs,
                             const Vector<T, 3>& rhs) noexcept
{
  return Vector<T, 3>{lhs.y * rhs.z - lhs.z * rhs.y,
                      lhs.z * rhs.x - lhs.x * rhs.z,
                      lhs.x * rhs.y - lhs.y * rhs.x};
}

/**
 * @brief Determines if two given vectors are equal.
 * @related Vector
 */
template <typename T, size_t size>
constexpr bool operator==(const Vector<T, size>& lhs,
                          const Vector<T, size>& rhs) noexcept
{
  for (size_t i = 0; i != size; ++i) {
    if (lhs[i] != rhs[i]) return false;
  }
  return true;
}

/**
 * @brief Determines if two given vectors are not equal.
 * @related Vector
 */
template <typename T, size_t size>
constexpr bool operator!=(const Vector<T, size>& lhs,
                          const Vector<T, size>& rhs) noexcept
{
  return !(lhs == rhs);
}

/**
 * @brief Outputs a string representive of vector to a stream
 * @related Vector
 */
template <typename T, size_t size>
std::ostream& operator<<(std::ostream& os, const Vector<T, size>& v) noexcept
{
  os << "vec(";
  for (size_t i = 0, last = size - 1; i != last; ++i) {
    os << v[i] << ", ";
  }
  os << v[size - 1] << ")";
  return os;
}

using Vec2f =
    Vector<float, 2>; ///< @brief 2D single-precision float point vector type
using Vec3f =
    Vector<float, 3>; ///< @brief 3D single-precision float point vector type
using Vec4f =
    Vector<float, 4>; ///< @brief 4D single-precision float point vector type

using Vec2d =
    Vector<double, 2>; ///< @brief 2D double-precision float point vector type
using Vec3d =
    Vector<double, 3>; ///< @brief 3D double-precision float point vector type
using Vec4d =
    Vector<double, 4>; ///< @brief 4D double-precision float point vector type

/** @}*/ // math group
