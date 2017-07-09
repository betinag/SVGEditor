#include "shape.h"

bool Shape::deserialize(std::istream& is)
{
    char c, quote;
    std::string name, value;

    while (is)
    {
        name = value = "";

        while (is.get(c) && SVGUtils::isWhiteSpace(c));

        if (c == '/')
        {
            return true;
        }

        while (is && !SVGUtils::isWhiteSpace(c) && c != '=')
        {
            name += c;
            is.get(c);
        }

        while (is.get(c) && c != '\"' && c != '\'');

        quote = c;

        while (is.get(c) && c != quote)
        {
            value += c;
        }

        if (is)
        {
            if (!setAttribute(name, value))
            {
                return false;
            }
        }
    }
    return false;
}
