#ifndef CIRCLE_H_INCLUDED
#define CIRCLE_H_INCLUDED

#include "shape.h"

class Circle : public Shape
{
public:
    Circle(const Point& = Point(), double = 1.0, const std::string& = "");

    std::string getType() const { return "circle"; }
    Point center() const { return m_center; }
    double radius() const { return m_radius; }

    void translate(double, double);
    bool serialize(std::ostream&) const;
    void print() const;

protected:
    bool setAttribute(const std::string&, const std::string&);

private:
    Point m_center;
    double m_radius;
    std::string m_fillColor;
};

#endif // CIRCLE_H_INCLUDED
