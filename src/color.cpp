#include "color.hpp"

auto
operator<<(std::ostream& out, Color const& color) -> std::ostream&
{
    out << "vec4("
        << color.r << ", "
        << color.g << ", "
        << color.b << ", "
        << color.a << ")";
    return out;
}

auto
operator>>(std::istream& in, Color& color) -> std::istream&
{
    Color input;
    in >> input.r;
    if(!in) {
        return in;
    }

    in >> input.g;
    if(!in) {
        return in;
    }

    in >> input.b;
    if(!in) {
        return in;
    }

    in >> input.a;
    if(!in) {
        return in;
    }

    color = input;
    return in;
}
