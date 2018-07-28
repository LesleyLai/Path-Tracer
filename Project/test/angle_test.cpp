#include <catch.hpp>
#include <sstream>

#include "angle.hpp"

TEST_CASE("[angle] Radian arithmetics")
{
  Radian pi_o_4{pi / 4};
  Radian pi_o_2{pi / 2};

  SECTION("Radian unary addition operator")
  {
    auto pp = pi_o_4;
    pp += pi_o_4;
    REQUIRE(pp.value() == Approx(pi_o_2.value()));
  }

  SECTION("Radian unary subtraction operator")
  {
    auto pp = pi_o_2;
    pp -= pi_o_4;
    REQUIRE(pp.value() == Approx(pi_o_4.value()));
  }

  SECTION("Radian unary multiplication operator")
  {
    auto pp = pi_o_4;
    pp *= 2;
    REQUIRE(pp.value() == Approx(pi_o_2.value()));
  }

  SECTION("Radian unary division operator")
  {
    auto pp = pi_o_2;
    pp /= 2;
    REQUIRE(pp.value() == Approx(pi_o_4.value()));
  }

  SECTION("Negation of radian")
  {
    REQUIRE((-pi_o_2).value() == Approx(-pi_o_2.value()));
  }

  SECTION("Radian binary addition operator")
  {
    REQUIRE((pi_o_4 + pi_o_2).value() == Approx(pi / 4 * 3));
  }

  SECTION("Radian binary minus operator")
  {
    REQUIRE((pi_o_2 - pi_o_4).value() == Approx(pi / 4));
  }

  SECTION("Radian binary multiply operator")
  {
    REQUIRE((pi_o_2 * 2).value() == Approx(pi));
    REQUIRE((2 * pi_o_2).value() == Approx(pi));
  }

  SECTION("Radian binary divide operator")
  {
    REQUIRE((pi_o_2 / 2).value() == Approx(pi / 4));
    REQUIRE(pi_o_2 / pi_o_2 == Approx(1));
  }
}

TEST_CASE("[angle] degree arithmetics")
{
  Radian degree_30{30};
  Radian degree_60{60};

  SECTION("Degree unary addition operator")
  {
    auto pp = degree_30;
    pp += degree_30;
    REQUIRE(pp.value() == Approx(degree_60.value()));
  }

  SECTION("Degree unary subtraction operator")
  {
    auto pp = degree_60;
    pp -= degree_30;
    REQUIRE(pp.value() == Approx(degree_30.value()));
  }

  SECTION("Degree unary multiplication operator")
  {
    auto pp = degree_30;
    pp *= 2;
    REQUIRE(pp.value() == Approx(degree_60.value()));
  }

  SECTION("Negation of degree")
  {
    REQUIRE((-degree_30).value() == Approx(-degree_30.value()));
  }

  SECTION("Degree binary addition operator")
  {
    REQUIRE((degree_30 + degree_60).value() == Approx(90));
  }

  SECTION("Degree binary minus operator")
  {
    REQUIRE((degree_60 - degree_30).value() == Approx(30));
  }

  SECTION("Degree binary multiply operator")
  {
    REQUIRE((degree_60 * 2).value() == Approx(120));
    REQUIRE((2 * degree_60).value() == Approx(120));
  }

  SECTION("Degree binary divide operator")
  {
    REQUIRE((degree_60 / 2).value() == Approx(30));
    REQUIRE(degree_60 / degree_30 == Approx(2));
  }
}

TEST_CASE("[angle] Convert between degree and radian")
{
  SECTION("Degree to radian")
  {
    Degree d{45};
    Radian r = d;
    REQUIRE(r.value() == Approx(pi / 4));
  }

  SECTION("Radian to degree")
  {
    Radian r{pi / 2};
    Degree d = r;
    REQUIRE(d.value() == Approx(90));
  }
}

TEST_CASE("[angle] Comparison of degree and radian")
{
  SECTION("equal")
  {
    REQUIRE(Radian{1} == Radian{1});
    REQUIRE(Degree{1} == Degree{1});
  }

  SECTION("not equal")
  {
    REQUIRE(Radian{2} != Radian{1});
    REQUIRE(Degree{2} != Degree{1});
  }

  SECTION("greater than")
  {
    REQUIRE(Radian{2} > Radian{1});
    REQUIRE(Degree{2} > Degree{1});
  }

  SECTION("greater or equal")
  {
    REQUIRE(Radian{2} >= Radian{1});
    REQUIRE(Degree{2} >= Degree{2});
  }

  SECTION("less than")
  {
    REQUIRE(Radian{1} < Radian{2});
    REQUIRE(Degree{1} < Degree{2});
  }

  SECTION("less or equal")
  {
    REQUIRE(Radian{1} <= Radian{1});
    REQUIRE(Degree{1} <= Degree{2});
  }
}

TEST_CASE("[angle] String conversions")
{
  std::stringstream ss;

  SECTION("Radian string conversion")
  {
    ss << Radian{pi};
    REQUIRE(ss.str() == "1_radians");
  }

  SECTION("Degree string conversion")
  {
    ss << Degree{45};
    REQUIRE(ss.str() == "45_degrees");
  }
}
