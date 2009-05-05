#include <sge/log/unindent.hpp>
#include <sge/io/tabbing_streambuf.hpp>
#include <sge/text.hpp>
#include <sge/exception.hpp>

sge::log::unindent_type const sge::log::unindent = sge::log::unindent_type();

sge::ostream &sge::log::operator<<(
	sge::ostream &s,
	sge::log::unindent_type const &)
{
	io::tabbing_streambuf * const ss = 
		dynamic_cast<io::tabbing_streambuf *>(
			s.rdbuf());
	if (!ss)
		throw exception(
			SGE_TEXT("tried to indent a non-indentable stream"));
	ss->unindent();
	return s;
}
