#ifndef SGE_MAD_STREAM_HPP_INCLUDED
#define SGE_MAD_STREAM_HPP_INCLUDED

#include "frame.hpp"
#include <mad.h>
#include <sge/raw_vector.hpp>
#include <sge/string.hpp>
#include <boost/noncopyable.hpp>
#include <iosfwd>

namespace sge
{
namespace mad
{
class stream : boost::noncopyable
{
	public:
	stream(std::istream &);
	frame &decode();
	bool eof() const;
	~stream();

	private:
	typedef unsigned char byte_type;
	typedef sge::raw_vector<byte_type> byte_container;
	typedef byte_container::size_type size_type;

	static size_type const input_size,mad_buffer_guard_size;

	mad_stream madstream;
	frame f;
	std::istream &stdstream;
	byte_container input_buffer;

	void sync();
	string const error_string() const;
};
}
}

#endif
