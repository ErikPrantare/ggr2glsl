#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
//#include <format>

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

    auto const printData = [](
            auto const& data,
            std::string const& name,
            std::string const& type) {
        std::cout << type << " " << name << "[" << data.size() << "]"
            << " = " << type << "[" << data.size() << "](\n";
        /*std::format(
            "{} left[{}] = {}[{}](\n",
            type,
            segments.size(),
            type,
            segments.size());
        */
        printJoined(std::cout, data, ",");
        std::cout << "\n);\n";
    };

    printData(segments.left, "left", "float");
    printData(segments.middle, "middle", "float");
    printData(segments.right, "right", "float");
    printData(segments.leftColor, "leftColor", "vec4");
    printData(segments.rightColor, "rightColor", "vec4");
    printData(segments.blendType, "blendType", "int");
    printData(segments.colorType, "colorType", "int");

    std::cout << "int first = 0;\nint last = " << segments.size()-1 << ";\n";

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
