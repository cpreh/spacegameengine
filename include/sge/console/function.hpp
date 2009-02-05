#ifndef SGE_CONSOLE_FUNCTION_HPP_INCLUDED
#define SGE_CONSOLE_FUNCTION_HPP_INCLUDED

#include <sge/console/signals.hpp>
#include <sge/string.hpp>

namespace sge
{
namespace console
{
struct function
{
	function(string const &);

	signal signal_;
	string description_;
};
}
}

#endif
