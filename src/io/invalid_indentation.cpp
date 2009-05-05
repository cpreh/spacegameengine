#include <sge/io/invalid_indentation.hpp>

sge::io::invalid_indentation::invalid_indentation(
	string const &s)
:
	sge::io::exception(s)
{
}
