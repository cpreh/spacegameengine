#include <sge/io/indent.hpp>
#include <sge/io/tabbing_streambuf.hpp>
#include <sge/text.hpp>

sge::io::indent_type const sge::io::indent;

sge::ostream &operator<<(
	ostream &s,
	indent_type const &)
{
	tabbing_streambuf * const ss = 
		dynamic_cast<tabbing_streambuf *>(
			s.rdbuf());
	if (!ss)
		throw exception(
			SGE_TEXT("tried to indent a non-indentable stream"));
	ss->indent();
	return s;
}
