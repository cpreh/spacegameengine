#include <sge/log/indent.hpp>
#include <sge/io/tabbing_streambuf.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>

sge::log::indent_type const sge::log::indent = sge::log::indent_type();

sge::ostream &sge::log::operator<<(
	ostream &s,
	indent_type const &)
{
	io::tabbing_streambuf * const ss = 
		dynamic_cast<io::tabbing_streambuf *>(
			s.rdbuf());
	if (!ss)
		throw exception(
			SGE_TEXT("tried to indent a non-indentable stream"));
	ss->indent();
	return s;
}
