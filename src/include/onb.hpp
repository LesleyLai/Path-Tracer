#ifndef ONB_HPP
#define ONB_HPP

#include <array>

#include "point.hpp"
#include "vector.hpp"

/**
 * @brief This class represents an Ortho-normal Bases
 *
 * A 3d Ortho-normal bases contains three mutually-orthogonal unit basis vectors
 */
template <typename Real> class ONB {
public:
  /**
   * @brief The default constructor of ONB constructs a standard basis in 3D
   */
  constexpr ONB() noexcept = default;

  static constexpr auto from_w(Vector<Real, 3> w) noexcept -> ONB<Real>
  {
    const auto w_unit = normalize(w);
    const auto a = [&]() -> Vector<Real, 3> {
      if (std::abs(w_unit.x) > 0.9) {
        return {0, 1, 0};
      }
      else {
        return {1, 0, 0};
      }
    }();

    const auto v = normalize(cross(w_unit, a));
    const auto u = cross(w_unit, v);
    return {u, v, w_unit};
  }

  /// Gets the u component of the ONB
  constexpr auto u() const noexcept -> Vector<Real, 3> { return u_; }

  /// Gets the v component of the ONB
  constexpr auto v() const noexcept -> Vector<Real, 3> { return v_; }

  /// Gets the w component of the ONB
  constexpr auto w() const noexcept -> Vector<Real, 3> { return w_; }

  /**
   * @brief Transform a point from local onb into a point in world onb
   */
  constexpr auto to_world(Point<Real, 3> coord) const noexcept -> Point<Real, 3>
  {
    const auto to_point = coord.x * u() + coord.y * v() + coord.z * w();
    return Point<Real, 3>{to_point.x, to_point.y, to_point.z};
  }

  /**
   * @brief Transform a vector from local onb into a point in world onb
   */
  constexpr auto to_world(Vector<Real, 3> a) const noexcept -> Vector<Real, 3>
  {
    return a.x * u() + a.y * v() + a.z * w();
  }

private:
  Vector<Real, 3> u_ = Vector<Real, 3>{1, 0, 0};
  Vector<Real, 3> v_ = Vector<Real, 3>{0, 1, 0};
  Vector<Real, 3> w_ = Vector<Real, 3>{0, 0, 1};

  // Unsafely constructs ONB from three vector
  constexpr ONB(Vector<Real, 3> u, Vector<Real, 3> v,
                Vector<Real, 3> w) noexcept
      : u_{u}, v_{v}, w_{w}
  {
  }
};

#endif // ONB_HPP
