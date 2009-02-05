#include <sge/console/function.hpp>

sge::console::function::function(string const &_description)
	: description_(_description) {}

sge::console::signal &sge::console::function::signal()
{
	return signal_;
}

sge::string const &sge::console::function::description() const
{
	return description_;
}
