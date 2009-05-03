#include <sge/io/tabbing_streambuf.hpp>
#include <sge/io/tabbing_filter.hpp>

sge::io::tabbing_streambuf::tabbing_streambuf(
	ostream &s)
	: tabs(0),
		s(s),
	  old(s.rdbuf())
{
	push(
		tabbing_filter(
			tabs));
	push(
		s);
	s.rdbuf(
		this);
}

void sge::io::tabbing_streambuf::indent()
{
	++tabs;
}

void sge::io::tabbing_streambuf::unindent()
{
	if (!tabs)
		throw exception(
			SGE_TEXT("unindented too much"));
	--tabs;
}

sge::io::tabbing_streambuf::~tabbing_streambuf()
{
	s.rdbuf(
		old);
}
