#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

struct Color {
    double r;
    double g;
    double b;
    double a;
};

struct Segment {
    double left;
    double middle;
    double right;
    Color leftColor;
    Color rightColor;
    int blendType;
    int colorType;
};

auto
operator>>(std::istream& in, Color& color) -> std::istream&
{
    in >> color.r;
    if(!in) {
        return in;
    }

    in >> color.g;
    if(!in) {
        return in;
    }

    in >> color.b;
    if(!in) {
        return in;
    }

    in >> color.a;

    return in;
}

auto
operator>>(std::istream& in, Segment& segment) -> std::istream&
{
    in >> segment.left;
    if(!in) {
        return in;
    }

    in >> segment.middle;
    if(!in) {
        return in;
    }

    in >> segment.right;
    if(!in) {
        return in;
    }

    in >> segment.leftColor;
    if(!in) {
        return in;
    }

    in >> segment.rightColor;
    if(!in) {
        return in;
    }

    in >> segment.blendType;
    if(!in) {
        return in;
    }

    in >> segment.colorType;

    return in;
}

auto
parseSegments(std::istream& in) -> std::vector<Segment>
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
        if(!(in >> segment)) {
            std::cerr
                << "Error on line " << currentLine << ": "
                << "Wrong format or wrong number of segments" << std::endl;

            std::exit(1);
        }

        ++currentLine;
    }

    return segments;
}

auto
main() -> int
{
    auto const segments = parseSegments(std::cin);
    
    std::cout.precision(5);
    std::cout.setf(std::ios::fixed);
    std::cout << "vec4 color(float value) {\n";

    for(auto const& segment : segments) {
        std::cout << "if(value < " << segment.right << ") {\n";
        std::cout
            << "return vec4(" 
            << segment.leftColor.r << ", "
            << segment.leftColor.g << ", "
            << segment.leftColor.b << ", "
            << segment.leftColor.a << ");\n";
        std::cout << "}\n";
    }

    // Closing function bracket
    std::cout << "}\n";
}
