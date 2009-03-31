#include "string_square.hpp"
#include <sge/gui/unit.hpp>

sge::string const sge::gui::utility::string_square(dim const &s)
{
	string const line(
		static_cast<string::size_type>(s.w()),
		SGE_TEXT('W'));
	string result;
	for (unit i = 0; i < s.h(); ++i)
		result += line;
	return result;
}
