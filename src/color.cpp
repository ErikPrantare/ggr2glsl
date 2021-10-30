/* ggr2glsl
 * Copyright (C) 2021 Erik Präntare
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
