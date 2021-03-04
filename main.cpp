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

struct Segments {
    std::vector<double> left;
    std::vector<double> middle;
    std::vector<double> right;
    std::vector<Color> leftColor;
    std::vector<Color> rightColor;
    std::vector<int> blendType;
    std::vector<int> colorType;

    auto
    add(Segment const& segment) -> void {
        left.push_back(segment.left);
        middle.push_back(segment.middle);
        right.push_back(segment.right);
        leftColor.push_back(segment.leftColor);
        rightColor.push_back(segment.rightColor);
        blendType.push_back(segment.blendType);
        colorType.push_back(segment.colorType);
    }

    [[nodiscard]] auto
    size() const noexcept -> size_t {
        return left.size();
    }
};

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
printJoined(
        std::ostream& out,
        std::vector<auto> const& v,
        std::string const& delim)
    -> void
{
    if(v.size() == 0) {
        return;
    }

    out << v[0];
    for(int i = 1; i < v.size(); ++i) {
        out << delim << v[i];
    }
}

auto
toSegments(std::vector<Segment> const& segments) -> Segments
{
    auto collected = Segments();

    for(auto const& segment : segments) {
        collected.add(segment);
    }

    return collected;
}

auto
main() -> int
{
    auto const segments = toSegments(parseSegments(std::cin));
    
    // TODO: learn std fmt library
    std::cout.precision(5);
    std::cout.setf(std::ios::fixed);
    std::cout << "vec4 gen(float value) {\n";

    std::cout << "float left[" << segments.size() << "] = float[](\n";
    printJoined(std::cout, segments.left, ",");
    std::cout << "\n);\n";

    std::cout << "float middle[" << segments.size() << "] = float[](\n";
    printJoined(std::cout, segments.middle, ",");
    std::cout << "\n);\n";

    std::cout << "float right[" << segments.size() << "] = float[](\n";
    printJoined(std::cout, segments.right, ",");
    std::cout << "\n);\n";

    std::cout << "vec4 leftColor[" << segments.size() << "] = vec4[](\n";
    printJoined(std::cout, segments.leftColor, ",");
    std::cout << "\n);\n";

    std::cout << "vec4 rightColor[" << segments.size() << "] = vec4[](\n";
    printJoined(std::cout, segments.rightColor, ",");
    std::cout << "\n);\n";

    std::cout << "int blendType[" << segments.size() << "] = int[](\n";
    printJoined(std::cout, segments.blendType, ",");
    std::cout << "\n);\n";

    std::cout << "int colorType[" << segments.size() << "] = int[](\n";
    printJoined(std::cout, segments.colorType, ",");
    std::cout << "\n);\n";

    std::cout << "int first = 0;\n int last = " << segments.size()-1 << ";\n";

    std::cout << R"(while(first != last) {
    int i = (first+last) / 2;
    if(value <= right[i]) {
        last = i;
    }
    else {
        first = i + 1;
    }
}
int index = first;

float normalized = (value - left[index]) / (right[index] - left[index]);
return mix(leftColor[index], rightColor[index], normalized);
)";


    // Closing function bracket
    std::cout << "}\n";
}
