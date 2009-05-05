#ifndef SGE_LOG_INDENT_HPP_INCLUDED
#define SGE_LOG_INDENT_HPP_INCLUDED

#include <sge/ostream.hpp>

namespace sge
{
namespace log
{
class indent_type {};

extern indent_type const indent;

ostream &operator<<(
	ostream &,
	indent_type const &);
}
}

#endif
