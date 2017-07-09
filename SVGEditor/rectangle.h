#ifndef RECTANGLE_H_INCLUDED
#define RECTANGLE_H_INCLUDED

#include "shape.h"

class Rectangle : public Shape
{
public:
    Rectangle(const Point& = Point(), double = 1.0, double = 1.0, const std::string& = "");

    std::string getType() const { return "rect"; }
    Point topPoint() const { return m_point; }
    double width() const { return m_width; }
    double height() const { return m_height; }

    void translate(double, double);
    bool serialize(std::ostream&) const;
    void print() const;

protected:
    bool setAttribute(const std::string&, const std::string&);

private:
    Point m_point;
    double m_width;
    double m_height;
    std::string m_fillColor;
};

#endif // RECTANGLE_H_INCLUDED
