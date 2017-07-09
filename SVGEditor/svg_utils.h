#ifndef SVG_UTILS_H_INCLUDED
#define SVG_UTILS_H_INCLUDED

#include <cctype>
#include <string>
#include <fstream>

class SVGUtils
{
public:
    static bool toInt(const std::string& str, int& result)
    {
        try
        {
            std::size_t pos;
            result = std::stoi(str, &pos, 10);
            return pos == str.size();
        }
        catch (...)
        {
        }

        return false;
    }

    static bool toDouble(const std::string& str, double& result)
    {
        try
        {
            std::size_t pos;
            result = std::stod(str, &pos);
            std::string unit = str.substr(pos);
            return unit.empty() || isSVGUnit(unit);
        }
        catch(...)
        {
        }

        return false;
    }

    static bool isSVGUnit(const std::string& str)
    {
        return str == "em" || str == "ex" || str == "px" || str == "pt"
            || str == "pc" || str == "mm" || str == "cm" || str == "in";
    }

    static bool isWhiteSpace(char c)
    {
        return std::isspace(static_cast<unsigned char>(c));
    }
};

#endif // SVG_UTILS_H_INCLUDED
