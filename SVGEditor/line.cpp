#include "line.h"

Line::Line(const Point& start, const Point& end, const std::string& stroke)
    : m_start(start)
    , m_end(end)
    , m_stroke(stroke)
{
}

void Line::translate(double dx, double dy)
{
    m_start.x += dx;
    m_start.y += dy;
    m_end.x += dx;
    m_end.y += dy;
}

bool Line::setAttribute(const std::string& name, const std::string& value)
{
    if (name == "x1")
	{
        return SVGUtils::toDouble(value, m_start.x);
	}
	else if (name == "y1")
	{
        return SVGUtils::toDouble(value, m_start.y);
	}
    else if (name == "x2")
	{
        return SVGUtils::toDouble(value, m_end.x);
	}
	else if (name == "y2")
	{
        return SVGUtils::toDouble(value, m_end.y);
	}
	else if (name == "stroke")
	{
        m_stroke = value;
	}

	return true;
}

bool Line::serialize(std::ostream& os) const
{
    startSerialize(os);
    os  << "x1=\"" << m_start.x << "\" ";
    os  << "y1=\"" << m_start.y << "\" ";
    os  << "x2=\"" << m_end.x << "\" ";
    os  << "y2=\"" << m_end.y << "\" ";

    if (!m_stroke.empty())
    {
        os  << "stroke=\"" << m_stroke << "\" ";
    }
	endSerialize(os);

	return os.good();
}

void Line::print() const
{
    std::cout << "line " << m_start << " " << m_end << " " << m_stroke << '\n';;
}
