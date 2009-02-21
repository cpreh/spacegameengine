#ifndef SGE_MAD_STREAM_HPP_INCLUDED
#define SGE_MAD_STREAM_HPP_INCLUDED

#include "frame.hpp"
#include "decoding_mode.hpp"
#include <mad.h>
#include <sge/container/raw_vector_decl.hpp>
#include <sge/string.hpp>
#include <sge/noncopyable.hpp>
#include <iosfwd>

namespace sge
{
namespace mad
{
class stream
{
	SGE_NONCOPYABLE(stream)
	public:
	explicit stream(std::istream &);
	frame &decode(decoding_mode::type);
	bool eof() const;
	void reset();
	~stream();

	private:
	typedef unsigned char byte_type;
	typedef sge::container::raw_vector<byte_type> byte_container;
	typedef byte_container::size_type size_type;

	static size_type const input_size,mad_buffer_guard_size;

	mad_stream madstream;
	frame f;
	std::istream &stdstream;
	byte_container input_buffer;
	bool eof_;

	void sync();
	string const error_string() const;
};
}
}

#endif
