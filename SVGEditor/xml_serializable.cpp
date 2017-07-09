#include "xml_serializable.h"

void XMLSerializable::startSerialize(std::ostream& os) const
{
	os << "<" << getType() << " ";
}


void XMLSerializable::endSerialize(std::ostream& os) const
{
	os << "/>\n";
}
