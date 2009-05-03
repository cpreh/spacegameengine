#include <sge/io/unindent.hpp>
#include <sge/io/tabbing_streambuf.hpp>
#include <sge/text.hpp>

sge::io::unindent_type const sge::io::unindent;

sge::ostream &operator<<(
	ostream &s,
	unindent_type const &)
{
	tabbing_streambuf * const ss = 
		dynamic_cast<tabbing_streambuf *>(
			s.rdbuf());
	if (!ss)
		throw exception(
			SGE_TEXT("tried to indent a non-indentable stream"));
	ss->unindent();
	return s;
}
