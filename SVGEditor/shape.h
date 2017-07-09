#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED

#include <memory>
#include <exception>

#include "xml_serializable.h"
#include "svg_utils.h"
#include "point.h"

class Shape : public XMLSerializable
{
public:
    virtual void translate(double, double) = 0;
    virtual void print() const = 0;
    bool deserialize(std::istream&);

    virtual ~Shape() {}

protected:
    virtual bool setAttribute(const std::string&, const std::string&) = 0;
};

#endif // SHAPE_H_INCLUDED
