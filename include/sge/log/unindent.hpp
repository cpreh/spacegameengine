#ifndef SGE_LOG_UNINDENT_HPP_INCLUDED
#define SGE_LOG_UNINDENT_HPP_INCLUDED

#include <sge/ostream.hpp>

namespace sge
{
namespace log
{
class unindent_type {};

extern unindent_type const unindent;

ostream &operator<<(
	ostream &,
	unindent_type const &);
}
}

#endif
