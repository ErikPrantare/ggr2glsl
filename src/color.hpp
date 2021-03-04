#ifndef GGR2GLSL_COLOR_HPP
#define GGR2GLSL_COLOR_HPP

#include <iostream>

struct Color {
    double r;
    double g;
    double b;
    double a;
};

auto
operator<<(std::ostream& out, Color const& color) -> std::ostream&;

auto
operator>>(std::istream& in, Color& color) -> std::istream&;

#endif
