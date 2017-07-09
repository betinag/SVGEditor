#ifndef SVG_EDITOR_H_INCLUDED
#define SVG_EDITOR_H_INCLUDED

#include <vector>
#include <limits>
#include "line.h"
#include "circle.h"
#include "rectangle.h"
#include "svg_utils.h"

class SVGEditor
{
public:
    void run();

private:
    std::string XMLDeclaration = "<?xml version=\"1.0\" standalone=\"no\"?>\n<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n";

    using ShapePtr = std::shared_ptr<Shape>;
    using ArgsVector = std::vector<std::string>;

    void open(ArgsVector&);
    std::ifstream& getTag(std::ifstream&, std::string&);
    std::ifstream& read(std::ifstream& is);
    void save();
    void saveAs(ArgsVector&);
    void close();
    void exit();

    ShapePtr createShape(const std::string&);
    bool parseInput(const std::string&, ArgsVector&);
    ShapePtr createLine(ArgsVector&);
    ShapePtr createCircle(ArgsVector&);
    ShapePtr createRectangle(ArgsVector&);
    void createShape(ArgsVector&);
    void translate(ArgsVector&);
    void within(ArgsVector&);
    void erase(ArgsVector&);
    void print() const;
    void printCommands();
    void clear();

private:
    std::string m_fileName;
    std::vector<ShapePtr> shapes;
    bool hasChanges = false;
};

#endif // SVG_EDITOR_H_INCLUDED
