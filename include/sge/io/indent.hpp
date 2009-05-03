#ifndef SGE_IO_INDENT_HPP_INCLUDED
#define SGE_IO_INDENT_HPP_INCLUDED

#include <sge/ostream.hpp>

namespace sge
{
namespace io
{
class indent_type {};

extern indent_type const indent;

ostream &operator<<(
	ostream &,
	indent_type const &);
}
}

#endif
