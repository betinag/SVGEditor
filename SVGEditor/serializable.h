#ifndef SERIALIZABLE_H_INCLUDED
#define SERIALIZABLE_H_INCLUDED

#include <iostream>
#include <string>

class Serializable
{
public:
	virtual bool serialize(std::ostream&) const = 0;
	virtual bool deserialize(std::istream&) = 0;

	virtual ~Serializable() {}
};

#endif // SERIALIZABLE_H_INCLUDED
