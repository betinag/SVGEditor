#ifndef LINE_H_INCLUDED
#define LINE_H_INCLUDED

#include "shape.h"

class Line : public Shape
{
public:
    Line(const Point& = Point(), const Point& = Point(), const std::string& = "black");

    std::string getType() const { return "line"; }
    Point startPoint() const { return m_start; }
    Point endPoint() const { return m_end; }

    void translate(double, double);
    bool serialize(std::ostream&) const;
    void print() const;

protected:
    bool setAttribute(const std::string&, const std::string&);

private:
    Point m_start;
    Point m_end;
    std::string m_stroke;
};


#endif // LINE_H_INCLUDED
