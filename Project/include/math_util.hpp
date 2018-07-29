/**
 * @file math_util.hpp
 * @brief A bunch of utilities math functions
 */

#ifndef MATH_UTIL_HPP
#define MATH_UTIL_HPP

#include <type_traits>
#include <utility>

/**
 * @brief Fast float point minmax function
 * @tparam T Input type must be a float point type
 *
 * This function is faster than std::minmax for float point numbers because it
 * doesn’t worry about NaNs and other exceptions.
 */
template <class T> std::pair<T, T> ffminmax(const T& a, const T& b)
{
  static_assert(
      std::is_floating_point_v<T>,
      "The input type of ffminmax function must be float point numbers");
  return a < b ? std::pair(a, b) : std::pair(b, a);
}

#endif // MATH_UTIL_HPP
