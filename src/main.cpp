#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
//#include <format>

#include "color.hpp"
#include "segment.hpp"

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
main() -> int
{
    Segments const segments = parseSegments(std::cin);
    
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
