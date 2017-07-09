#include "rectangle.h"

Rectangle::Rectangle(const Point& point, double width, double height, const std::string& fillColor)
    : m_point(point)
    , m_width(width)
    , m_height(height)
    , m_fillColor(fillColor)
{
    if (m_width <= 0 || m_height <= 0)
    {
        throw std::invalid_argument("Non-positive rectangle width or height.");
    }
}

void Rectangle::translate(double dx, double dy)
{
    m_point.x += dx;
    m_point.y += dy;
}

bool Rectangle::setAttribute(const std::string& name, const std::string& value)
{
    if (name == "x")
	{
        return SVGUtils::toDouble(value, m_point.x);
	}
	else if (name == "y")
	{
        return SVGUtils::toDouble(value, m_point.y);
	}
	else if (name == "width")
	{
        return SVGUtils::toDouble(value, m_width);
	}
	else if (name == "height")
	{
        return SVGUtils::toDouble(value, m_height);
	}
	else if (name == "fill")
	{
		m_fillColor = value;
	}
	return true;
}

bool Rectangle::serialize(std::ostream& os) const
{
    startSerialize(os);
    os  << "x=\"" << m_point.x << "\" ";
    os  << "y=\"" << m_point.y << "\" ";
    os  << "width=\"" << m_width << "\" ";
    os  << "height=\"" << m_height << "\" ";

    if (!m_fillColor.empty())
    {
        os  << "fill=\"" << m_fillColor << "\" ";
    }
	endSerialize(os);

	return os.good();
}

void Rectangle::print() const
{
    std::cout << "rectangle " << m_point << " " << m_width
            << " " << m_height << " " << m_fillColor << '\n';
}
