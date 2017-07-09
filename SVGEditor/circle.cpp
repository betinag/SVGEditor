#include "circle.h"

Circle::Circle(const Point& center, double radius, const std::string& fillColor)
    : m_center(center)
    , m_radius(radius)
    , m_fillColor(fillColor)
{
    if (m_radius <= 0)
    {
        throw std::invalid_argument("Non-positive circle radius.");
    }
}

void Circle::translate(double dx, double dy)
{
    m_center.x += dx;
    m_center.y += dy;
}

bool Circle::setAttribute(const std::string& name, const std::string& value)
{
    if (name == "cx")
	{
        return SVGUtils::toDouble(value, m_center.x);
	}
	else if (name == "cy")
	{
        return SVGUtils::toDouble(value, m_center.y);
	}
	else if (name == "r")
	{
        return SVGUtils::toDouble(value, m_radius);
	}
	else if (name == "fill")
	{
		m_fillColor = value;
	}
	return true;
}

bool Circle::serialize(std::ostream& os) const
{
    startSerialize(os);
    os  << "cx=\"" << m_center.x << "\" ";
    os  << "cy=\"" << m_center.y << "\" ";
    os  << "r=\"" << m_radius << "\" ";

    if (!m_fillColor.empty())
    {
        os  << "fill=\"" << m_fillColor << "\" ";
    }
	endSerialize(os);

	return os.good();
}

void Circle::print() const
{
    std::cout << "circle " << m_center << " " << m_radius << " " << m_fillColor << '\n';
}
