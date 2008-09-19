#ifndef SGE_MAD_STREAM_HPP_INCLUDED
#define SGE_MAD_STREAM_HPP_INCLUDED

#include "timer.hpp"
#include <mad.h>
#include <sge/raw_vector.hpp>
#include <sge/string.hpp>
#include <iosfwd>

namespace sge
{
namespace mad
{
class frame;

class stream
{
	public:
	stream(std::istream &);
	void sync();
	void decode(frame &);
	bool eof() const;
	~stream();

	private:
	typedef unsigned char byte_type;
	typedef sge::raw_vector<byte_type> byte_container;
	typedef byte_container::size_type size_type;

	static size_type const input_size,mad_buffer_guard_size;

	mad_stream madstream;
	std::istream &stdstream;
	byte_container input_buffer;
	timer time;

	string const error_string() const;
};
}
}

#endif
