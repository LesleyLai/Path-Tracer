#ifndef POINT_HPP
#define POINT_HPP

#include <algorithm>

#include "vector.hpp"

/** \addtogroup math
 *  @{
 */

template <typename T, size_t size> class Point;

template <typename T, size_t size>
struct Point_base : Vector_like_base<T, size, Point<T, size>> {
  /**
   * @brief Convert this point into a vector with same value
   */
  explicit operator Vector<T, size>() const
  {
    Vector<T, size> v;
    std::copy(std::begin(*this), std::end(*this), std::begin(v));
    return v;
  }

protected:
  constexpr Point_base() = default;
};

/**
 * @brief Template of fix-sized points
 */
template <typename T, size_t size> class Point : Point_base<T, size> {
  T elems[size];
};

/**
 * @brief 2D Point specialization
 * @see Point
 */
template <typename T> struct Point<T, 2> : Point_base<T, 2> {
  union {
    struct {
      T x, y;
    };
    T elems[2];
  };

  constexpr Point() noexcept = default;
  constexpr Point(T xx, T yy) noexcept : x{xx}, y{yy} {}
};

/**
 * @brief 3D Point specialization
 * @see Point
 */
template <typename T> struct Point<T, 3> : Point_base<T, 3> {
  union {
    struct {
      T x, y, z;
    };
    struct {
      Point<T, 2> xy;
    };
    T elems[3];
  };

  constexpr Point() noexcept = default;
  constexpr Point(T xx, T yy, T zz) noexcept : x{xx}, y{yy}, z{zz} {}
  constexpr Point(Point<T, 2> xy, T zz) noexcept : x{xy.x}, y{xy.y}, z{zz} {}
};

/**
 * @brief 4D Point specialization
 * @see Point
 */
template <typename T> struct Point<T, 4> : Point_base<T, 4> {
  union {
    struct {
      T x, y, z, w;
    };
    struct {
      Point<T, 2> xy;
    };
    struct {
      Point<T, 3> xyz;
    };
    T elems[4];
  };

  constexpr Point() noexcept = default;
  constexpr Point(T xx, T yy, T zz, T ww) noexcept : x{xx}, y{yy}, z{zz}, w{ww}
  {
  }
  constexpr Point(Point<T, 3> xyz, T ww) noexcept
      : x{xyz.x}, y{xyz.y}, z{xyz.z}, w{ww}
  {
  }
};

/**
 * @brief Adds rhs to this point.
 * @related Point Vector
 */
template <typename T, size_t size>
constexpr Point<T, size>& operator+=(Point<T, size>& lhs,
                                     const Vector<T, size>& rhs) noexcept
{
  std::transform(std::begin(lhs), std::end(lhs), std::begin(rhs),
                 std::begin(lhs), std::plus<T>());
  return lhs;
}

/**
 * @brief Subtracts rhs to this point.
 * @related Point Vector
 */
template <typename T, size_t size>
constexpr Point<T, size>& operator-=(Point<T, size>& lhs,
                                     const Vector<T, size>& rhs) noexcept
{
  std::transform(std::begin(lhs), std::end(lhs), std::begin(rhs),
                 std::begin(lhs), std::minus<T>());
  return lhs;
}

/**
 * @brief Subtracts two Points creates a Vector.
 * @related Point Vector
 */
template <typename T, size_t size>
constexpr Vector<T, size> operator-(const Point<T, size>& lhs,
                                    const Point<T, size>& rhs) noexcept
{
  Vector<T, size> result{};
  std::transform(std::begin(lhs), std::end(lhs), std::begin(rhs),
                 std::begin(result), std::minus<T>());
  return result;
}

/**
 * @brief Adds a Vector to Point create another Point
 * @related Point Vector
 */
template <typename T, size_t size>
constexpr Point<T, size> operator+(const Point<T, size>& lhs,
                                   const Vector<T, size>& rhs) noexcept
{
  Point<T, size> result{};
  std::transform(std::begin(lhs), std::end(lhs), std::begin(rhs),
                 std::begin(result), std::plus<T>());
  return result;
}

/**
 * @brief Adds a Point to Vector create another Point
 * @related Point Vector
 */
template <typename T, size_t size>
constexpr Point<T, size> operator+(const Vector<T, size>& lhs,
                                   const Point<T, size>& rhs) noexcept
{
  return rhs + lhs;
}

/**
 * @brief Subtracts a Vector to Point create another Point
 * @related Point Vector
 */
template <typename T, size_t size>
constexpr Point<T, size> operator-(const Point<T, size>& lhs,
                                   const Vector<T, size>& rhs) noexcept
{
  Point<T, size> result{};
  std::transform(std::begin(lhs), std::end(lhs), std::begin(rhs),
                 std::begin(result), std::minus<T>());
  return result;
}

/**
 * @brief Linearly interpolates between two Points.
 * @related Point
 * @note The parameter t is not clamped into [0, 1], so the result may be
 * outside the range
 *
 * When t = 0 returns lhs. When t = 1 returns rhs. When t = 0.5 returns the
 * point midway between lhs and rhs.
 */
template <typename T, size_t size>
constexpr Point<T, size> lerp(const Point<T, size>& lhs,
                              const Point<T, size>& rhs, T t) noexcept
{
  return lhs + (rhs - lhs) * t;
}

using Point2f = Point<float, 2>;
using Point2d = Point<double, 2>;
using Point3f = Point<float, 3>;
using Point3d = Point<double, 3>;
using Point4f = Point<float, 4>;
using Point4d = Point<double, 4>;

/** @}*/ // math group

#endif // POINT_HPP
