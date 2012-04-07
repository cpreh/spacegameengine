#include <alda/net/buffer/circular_receive/for_asio.hpp>
#include <alda/net/buffer/circular_receive/object.hpp>
#include <alda/net/buffer/circular_receive/part.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/asio/buffer.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


boost::asio::mutable_buffers_1 const
alda::net::buffer::circular_receive::for_asio(
	alda::net::buffer::circular_receive::object &_buffer
)
{
	alda::net::buffer::circular_receive::part const part(
		_buffer.next_receive_part()
	);

	return
		boost::asio::mutable_buffers_1(
			part.begin(),
			std::min(
				part.size(),
				static_cast<
					alda::net::buffer::circular_receive::object::size_type
				>(
					4096u
				)
			)
		);
}
