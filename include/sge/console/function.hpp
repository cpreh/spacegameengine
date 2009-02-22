#ifndef SGE_CONSOLE_FUNCTION_HPP_INCLUDED
#define SGE_CONSOLE_FUNCTION_HPP_INCLUDED

#include <sge/console/signals.hpp>
#include <sge/export.hpp>
#include <sge/string.hpp>

namespace sge
{
namespace console
{
class SGE_CLASS_SYMBOL function
{
	public:
	SGE_SYMBOL function(string const &);

	SGE_SYMBOL sge::console::signal &signal();
	SGE_SYMBOL string const &description() const;

	private:
	sge::console::signal signal_;
	string description_;
};
}
}

#endif
