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

#ifndef GGR2GLSL_SEGMENT_HPP
#define GGR2GLSL_SEGMENT_HPP

#include <iostream>
#include <vector>

#include "color.hpp"

struct Segment {
    double left;
    double middle;
    double right;
    Color leftColor;
    Color rightColor;
    int blendType;
    int colorType;
};

struct Segments {
    std::vector<double> left;
    std::vector<double> middle;
    std::vector<double> right;
    std::vector<Color> leftColor;
    std::vector<Color> rightColor;
    std::vector<int> blendType;
    std::vector<int> colorType;

    auto
    add(Segment const& segment) -> void;

    [[nodiscard]] auto
    size() const noexcept -> size_t {
        return left.size();
    }
};

auto
operator>>(std::istream& in, Segment& segment) -> std::istream&;

[[nodiscard]] auto
parseSegments(std::istream& in) -> Segments;

#endif
