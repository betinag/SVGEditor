#include "svg_editor.h"

void SVGEditor::run()
{
    printCommands();
    std::string input;
	while (true)
	{
		std::cout << "> ";
		std::getline(std::cin, input);
		ArgsVector args;
		if (!parseInput(input, args))
		{
		    std::cout << "Invalid input\n";
		    continue;
		}

		std::string command = args[0];
		if (command == "print")
		{
			print();
		}
		else if (command == "create")
		{
			createShape(args);
		}
		else if (command == "erase")
		{
			erase(args);
		}
		else if (command == "translate")
		{
			translate(args);
		}
		else if (command == "save")
		{
			save();
		}
		else if (command == "saveas")
		{
			saveAs(args);
		}
		else if (command == "open")
		{
			open(args);
		}
		else if (command == "close")
		{
			close();
		}
		else if (command == "exit")
		{
			exit();
			return;
		}
		else if (command == "help")
		{
			printCommands();
		}
		else
		{
			std::cout << "Invalid command\n";
		}
	}
}

void SVGEditor::open(ArgsVector& args)
{
    if (args.size() != 2)
    {
        std::cout << "Wrong number of arguments\n";
        return;
    }

    if (!m_fileName.empty())
    {
        std::cout << "Closing file " << m_fileName << "...\n";
    }

    clear();

    std::ifstream ifs(args[1]);
    if (!ifs.is_open())
    {
        ifs.clear();
        std::ofstream ofs(args[1]);
        if (ofs.is_open())
        {
            ofs.close();
            ifs.open(args[1]);
        }
    }

    if (!ifs.is_open())
    {
        std::cout << "Failed to open file " << args[1] << '\n';
        return;
    }

    m_fileName = args[1];
    std::cout << "Successfully opened file " << m_fileName << '\n';
    if (ifs.peek() != std::ifstream::traits_type::eof())
    {
        if (!read(ifs))
        {
            std::cout << "Error while reading file\n";
            clear();
        }
    }
}

std::ifstream& SVGEditor::getTag(std::ifstream& ifs, std::string& tag)
{
    tag = "";
    char c;
    while (ifs.get(c) && c != '<');

    while (ifs.get(c) && !SVGUtils::isWhiteSpace(c) && c != '>')
    {
        tag += c;
    }

    return ifs;
}

std::ifstream& SVGEditor::read(std::ifstream& ifs)
{
    std::string tag;
    while (getTag(ifs, tag) && tag != "svg");

    while (getTag(ifs, tag) && tag != "/svg")
    {
        ShapePtr shape = createShape(tag);
        if (shape)
        {
            if (shape->deserialize(ifs))
            {
                shapes.push_back(shape);
            }
        }
    }

    return ifs;
}

void SVGEditor::save()
{
    if (m_fileName.empty())
    {
        std::cout << "There is no opened file\n";
        return;
    }

    std::ofstream ofs(m_fileName, std::ofstream::out | std::ofstream::trunc);
    if (!ofs.is_open())
    {
        std::cout << "Failed to open file " << m_fileName << '\n';
        return;
    }

    ofs << XMLDeclaration << "<svg>\n";
    for(size_t i = 0; i < shapes.size(); ++i)
    {
        if (!shapes[i]->serialize(ofs))
        {
            break;
        }
    }
    ofs << "</svg>";

    if (!ofs)
    {
        std::cout << "Error while saving file\n";
        return;
    }

	hasChanges = false;
	std::cout << "Successfully saved " << m_fileName << '\n';
}

void SVGEditor::saveAs(ArgsVector& args)
{
    if (args.size() != 2)
    {
        std::cout << "Wrong number of arguments\n";
        return;
    }

    m_fileName = args[1];
    save();
}

void SVGEditor::close()
{
    if (m_fileName.empty())
    {
        std::cout << "There is no opened file\n";
        return;
    }

    if (hasChanges)
    {
        std::cout << "The file has changes. Are you sure you want to exit? (Y/N): ";
        char choice;
        do
        {
            std::cin >> choice;
        }
        while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n');

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 'N' || choice == 'n')
        {
            return;
        }
    }
    std::cout << "Closed file " << m_fileName << '\n';
    clear();
}

void SVGEditor::exit()
{
    std::cout << "Exiting the program...\n";
    clear();
}

SVGEditor::ShapePtr SVGEditor::createShape(const std::string& type)
{
    if (type == "line")
    {
        return std::make_shared<Line>();
    }
    else if (type == "circle")
    {
        return std::make_shared<Circle>();
    }
    else if (type == "rect")
    {
        return std::make_shared<Rectangle>();
    }

    return nullptr;
}

bool SVGEditor::parseInput(const std::string& input, ArgsVector& args)
{
    if (input.empty())
    {
        return false;
    }

    std::string token;
    char c, quote;
    for (size_t i = 0; i < input.length(); ++i)
    {
        c = input[i];
        if (SVGUtils::isWhiteSpace(c))
        {
            if (!token.empty())
            {
                args.push_back(token);
                token = "";
            }
        }
        else if (c == '\"' || c == '\'')
        {
            quote = c;
            ++i;
            while (i < input.length() && input[i] != quote)
            {
                token += input[i];
                ++i;
            }
            if (i == input.length())
            {
                return false;
            }
            args.push_back(token);
            token = "";
        }
        else
        {
            token += input[i];
        }
    }
    if (!token.empty())
    {
        args.push_back(token);
    }
    return true;
}

SVGEditor::ShapePtr SVGEditor::createLine(ArgsVector& args)
{
    if (args.size() < 6 || args.size() > 7)
    {
        std::cout << "Wrong number of arguments\n";
        return nullptr;
    }

    double x1, y1, x2, y2;
    std::string stroke = "black";

    if (!SVGUtils::toDouble(args[2], x1) || !SVGUtils::toDouble(args[3], y1)
        || !SVGUtils::toDouble(args[4], x2) || !SVGUtils::toDouble(args[5], y2)
        || (x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0))
    {
        std::cout << "Invalid input\n";
        return nullptr;
    }

    if (args.size() == 7)
    {
        stroke = args[6];
    }

    return std::make_shared<Line>(Point(x1, y1), Point(x2, y2), stroke);
}

SVGEditor::ShapePtr SVGEditor::createCircle(ArgsVector& args)
{
    if (args.size() < 5 || args.size() > 6)
    {
        std::cout << "Wrong number of arguments\n";
        return nullptr;
    }

    double cx, cy, r;
    std::string fillColor;

    if (!SVGUtils::toDouble(args[2], cx) || !SVGUtils::toDouble(args[3], cy)
        || !SVGUtils::toDouble(args[4], r) || (cx < 0 || cy < 0 || r < 0))
    {
        std::cout << "Invalid input\n";
        return nullptr;
    }

    if (args.size() == 6)
    {
        fillColor = args[5];
    }

    return std::make_shared<Circle>(Point(cx, cy), r, fillColor);
}

SVGEditor::ShapePtr SVGEditor::createRectangle(ArgsVector& args)
{
    if (args.size() < 6 || args.size() > 7)
    {
        std::cout << "Wrong number of arguments\n";
        return nullptr;
    }

    double x, y, width, height;
    std::string fillColor;

    if (!SVGUtils::toDouble(args[2], x) || !SVGUtils::toDouble(args[3], y)
        || !SVGUtils::toDouble(args[4], width) || !SVGUtils::toDouble(args[5], height)
        || (x < 0 || y < 0 || width < 0 || height < 0))
    {
        std::cout << "Invalid input\n";
        return nullptr;
    }

    if (args.size() == 7)
    {
        fillColor = args[6];
    }

    return std::make_shared<Rectangle>(Point(x, y), width, height, fillColor);
}

void SVGEditor::createShape(ArgsVector& args)
{
    if (m_fileName.empty())
    {
        std::cout << "There is no opened file\n";
        return;
    }

    if (args.size() < 2)
    {
        std::cout << "Wrong number of arguments\n";
        return;
    }

    ShapePtr shape;
    if (args[1] == "line")
    {
        shape = createLine(args);
    }
    else if (args[1] == "circle")
    {
        shape = createCircle(args);
    }
    else if (args[1] == "rectangle")
    {
        shape = createRectangle(args);
    }
    else
    {
        std::cout << "Unknown shape type\n";
        return;
    }

    if (shape)
    {
        shapes.push_back(shape);
        std::cout << "Successfully created " << shape->getType() << " (" << shapes.size() << ")\n";
        hasChanges = true;
    }
}

void SVGEditor::translate(ArgsVector& args)
{
    if (m_fileName.empty())
    {
        std::cout << "There is no opened file\n";
        return;
    }

    if (args.size() < 3 || args.size() > 4)
    {
        std::cout << "Wrong number of arguments\n";
        return;
    }

    double dy, dx;

    if (!SVGUtils::toDouble(args[1], dy) || !SVGUtils::toDouble(args[2], dx))
    {
        std::cout << "Invalid input\n";
        return;
    }

    if (args.size() == 3)
    {
        for (size_t i = 0; i < shapes.size(); ++i)
        {
            shapes[i]->translate(dx, dy);
        }
        std::cout << "Translated all figures\n";
        hasChanges = true;
        return;
    }

    int id;
    if (!SVGUtils::toInt(args[3], id))
    {
        std::cout << "Invalid input\n";
        return;
    }

    if (id < 1 || static_cast<unsigned>(id) > shapes.size())
    {
        std::cout << "There is no figure with id " << id << '\n';
        return;
    }

    shapes[id - 1]->translate(dx, dy);
    std::cout << "Translated figure " << id << '\n';
    hasChanges = true;
}

void SVGEditor::erase(ArgsVector& args)
{
    if (m_fileName.empty())
    {
        std::cout << "There is no opened file\n";
        return;
    }

    if (args.size() != 2)
    {
        std::cout << "Wrong number of arguments\n";
        return;
    }

    int id;
    if (!SVGUtils::toInt(args[1], id))
    {
        std::cout << "Invalid input\n";
        return;
    }

    if (id < 1 || static_cast<unsigned>(id) > shapes.size())
    {
        std::cout << "There is no figure with id " << id << '\n';
        return;
    }

    std::string type = shapes[id - 1]->getType();
    shapes.erase(shapes.begin() + id - 1);
    std::cout << "Erased " << type << " (" << id << ")\n";
    hasChanges = true;
}

void SVGEditor::print() const
{
    if (m_fileName.empty())
    {
        std::cout << "There is no opened file\n";
        return;
    }

    for (size_t i = 0; i < shapes.size(); ++i)
    {
        std::cout << i + 1 << ". ";
        shapes[i]->print();
    }
}

void SVGEditor::printCommands()
{
    std::cout << "List of available commands:\n";
    std::cout << "- help\n";
    std::cout << "- print\n";
	std::cout << "- create <shape-type> <args...>\n";
	std::cout << "- erase <id>\n";
	std::cout << "- translate <vertical> <horizontal> [id]\n";
	std::cout << "- save\n";
	std::cout << "- saveas <filename>\n";
	std::cout << "- open <filename>\n";
	std::cout << "- close\n";
	std::cout << "- exit\n\n";
}

void SVGEditor::clear()
{
    hasChanges = false;
    m_fileName = "";
    shapes.clear();
}
