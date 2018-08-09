#include <catch.hpp>

#include "vector.hpp"

template <typename T, size_t size> class Point;

template <typename T, size_t size> struct Point_base {
  using size_type = size_t;
  using value_type = T;
  using Point_type = Point<T, size>;

  constexpr value_type& operator[](size_type i) noexcept
  {
    return static_cast<Point_type*>(this)->elems[i];
  }
  constexpr const value_type& operator[](size_type i) const noexcept
  {
    return static_cast<const Point_type* const>(this)->elems[i];
  }
};

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
 * @brief Determines if two given points are equal.
 * @related Point
 */
template <typename T, size_t size>
constexpr bool operator==(const Point<T, size>& lhs,
                          const Point<T, size>& rhs) noexcept
{
  for (size_t i = 0; i != size; ++i) {
    if (lhs[i] != rhs[i]) return false;
  }
  return true;
}

/**
 * @brief Determines if two given points are not equal.
 * @related Point
 */
template <typename T, size_t size>
constexpr bool operator!=(const Point<T, size>& lhs,
                          const Point<T, size>& rhs) noexcept
{
  return !(lhs == rhs);
}

/**
 * @brief Adds rhs to this point.
 * @related Point
 * @related Vector
 */
template <typename T, size_t size>
constexpr Point<T, size>& operator+=(Point<T, size>& lhs,
                                     const Vector<T, size>& rhs) noexcept
{
  for (size_t i = 0; i != size; ++i) {
    lhs[i] += rhs[i];
  }
  return lhs;
}

/**
 * @brief Subtracts rhs to this point.
 * @related Point
 * @related Vector
 */
template <typename T, size_t size>
constexpr Point<T, size>& operator-=(Point<T, size>& lhs,
                                     const Vector<T, size>& rhs) noexcept
{
  for (size_t i = 0; i != size; ++i) {
    lhs[i] -= rhs[i];
  }
  return lhs;
}

using Point2f = Point<float, 2>;
using Point2d = Point<double, 2>;
using Point3f = Point<float, 3>;
using Point3d = Point<double, 3>;
using Point4f = Point<float, 4>;
using Point4d = Point<double, 4>;

TEST_CASE("Point", "[math]")
{
  Point3d p{1, 2, 3};
  Vec3d v{1, 1, 1};

  SECTION("Array-style indexing for Point")
  {
    REQUIRE(p[2] == Approx(3));
    ++p[2];
    REQUIRE(p[2] == Approx(4));
  }

  SECTION("Comparison of Point")
  {
    REQUIRE(p == Point3d{1, 2, 3});
    REQUIRE(p != Point3d{2, 3, 4});
  }

  SECTION("Unary operations for Point")
  {
    SECTION("+=")
    {
      p += v;
      REQUIRE(p == Point3d{2, 3, 4});
    }

    SECTION("+=")
    {
      p -= v;
      REQUIRE(p == Point3d{0, 1, 2});
    }
  }
}
