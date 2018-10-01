#include "angle.hpp"

std::ostream& operator<<(std::ostream& os, Radian radian)
{
  os << radian.value() / pi << "_radians";
  return os;
}

std::ostream& operator<<(std::ostream& os, Degree degree)
{
  os << degree.value() << "_degrees";
  return os;
}
