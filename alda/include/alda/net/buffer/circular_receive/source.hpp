#ifndef ALDA_NET_BUFFER_CIRCULAR_RECEIVE_SOURCE_HPP_INCLUDED
#define ALDA_NET_BUFFER_CIRCULAR_RECEIVE_SOURCE_HPP_INCLUDED

#include <alda/net/value_type.hpp>
#include <alda/net/buffer/circular_receive/object_fwd.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/iostreams/concepts.hpp>
#include <ios>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace net
{
namespace buffer
{
namespace circular_receive
{

class receive_buffer_source
{
	FCPPT_NONASSIGNABLE(
		receive_buffer_source
	);
public:
	typedef
	alda::net::value_type char_type;

	struct category
	:
		boost::iostreams::input_seekable,
		boost::iostreams::device_tag
	{
	};

	explicit
	receive_buffer_source(
		alda::net::buffer::circular_receive::object &
	);

	std::streamsize
	read(
		char *,
		std::streamsize
	);

	std::streampos
	seek(
		boost::iostreams::stream_offset,
		std::ios_base::seekdir
	);
private:
	alda::net::buffer::circular_receive::object &container_;

	std::streampos read_count_;
};

}
}
}
}

#endif
