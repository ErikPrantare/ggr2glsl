#include "segment.hpp"

#include <sstream>

auto
Segments::add(Segment const& segment) -> void {
    left.push_back(segment.left);
    middle.push_back(segment.middle);
    right.push_back(segment.right);
    leftColor.push_back(segment.leftColor);
    rightColor.push_back(segment.rightColor);
    blendType.push_back(segment.blendType);
    colorType.push_back(segment.colorType);
}

auto
operator>>(std::istream& in, Segment& segment) -> std::istream&
{
    Segment input;
    in >> input.left;
    if(!in) {
        return in;
    }

    in >> input.middle;
    if(!in) {
        return in;
    }

    in >> input.right;
    if(!in) {
        return in;
    }

    in >> input.leftColor;
    if(!in) {
        return in;
    }

    in >> input.rightColor;
    if(!in) {
        return in;
    }

    in >> input.blendType;
    if(!in) {
        return in;
    }

    in >> input.colorType;
    if(!in) {
        return in;
    }

    segment = input;
    return in;
}

auto
collect(std::vector<Segment> const& segments) -> Segments
{
    auto collected = Segments();

    for(auto const& segment : segments) {
        collected.add(segment);
    }

    return collected;
}

auto
parseSegments(std::istream& in) -> Segments
{
    auto line = std::string{};
    int currentLine = 1;

    // Gimp Gradient
    std::getline(in, line);
    ++currentLine;
    // Name: <gradient-name>
    std::getline(in, line);
    ++currentLine;

    // Number of segments
    std::getline(in, line);
    int const numSegments = [&line, currentLine](){
        try {
            return std::stoi(line);
        }
        catch(std::exception const& e) {
            std::cerr
                << "Error on line " << currentLine << ": "
                << e.what() << std::endl;
            std::exit(1);
        }
    }();
    ++currentLine;

    auto segments = std::vector<Segment>(numSegments);

    for(auto& segment : segments) {
        // Newer gradiens may contain additional data per segment,
        // reading whole line allows us to ignore these.
        std::getline(in, line);
        auto ss = std::stringstream(line);

        if(!(ss >> segment)) {
            std::cerr
                << "Error on line " << currentLine << ": "
                << "Wrong format or wrong number of segments" << std::endl;

            std::exit(1);
        }

        ++currentLine;
    }

    return collect(segments);
}
