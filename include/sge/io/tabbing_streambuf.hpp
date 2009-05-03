#ifndef SGE_IO_TABBING_STREAMBUF_HPP_INCLUDED
#define SGE_IO_TABBING_STREAMBUF_HPP_INCLUDED

#include <boost/iostreams/filtering_streambuf.hpp>
#include <sge/ostream.hpp>
#include <streambuf>

namespace sge
{
namespace io
{
class tabbing_streambuf 
	: public boost::iostreams::filtering_ostreambuf
{
public:
	tabbing_streambuf(
		ostream &);
	void indent();
	void unindent();
	~tabbing_streambuf();
private:
	unsigned tabs;
	ostream &s;
	std::streambuf * const old;
};
}
}

#endif
