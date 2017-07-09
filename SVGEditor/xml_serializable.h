#ifndef XML_SERIALIZABLE_H_INCLUDED
#define XML_SERIALIZABLE_H_INCLUDED

#include "serializable.h"

class XMLSerializable : public Serializable
{
public:
    virtual std::string getType() const = 0;

	void startSerialize(std::ostream&) const;
	void endSerialize(std::ostream&) const;
};

#endif // XML_SERIALIZABLE_H_INCLUDED
