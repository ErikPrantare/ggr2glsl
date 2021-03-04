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
