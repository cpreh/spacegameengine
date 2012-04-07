#include <alda/net/buffer/max_size.hpp>
#include <alda/net/buffer/circular_send/boost_type.hpp>
#include <alda/net/buffer/circular_send/object.hpp>


alda::net::buffer::circular_send::object::object(
	alda::net::buffer::max_size const _buffer_max_size
)
:
	impl_(
		_buffer_max_size.get()
	)
{
}

alda::net::buffer::circular_send::object::~object()
{
}

alda::net::buffer::circular_send::boost_type::const_array_range const
alda::net::buffer::circular_send::object::send_part() const
{
	return
		impl_.array_two().second == 0u
		?
			impl_.array_one()
		:
			impl_.array_two();
}

void
alda::net::buffer::circular_send::object::erase_front(
	alda::net::buffer::circular_send::object::size_type const _size
)
{
	impl_.erase(
		impl_.begin(),
		impl_.begin()
		+
		static_cast<
			alda::net::buffer::circular_send::boost_type::iterator::difference_type
		>(
			_size
		)
	);
}

bool
alda::net::buffer::circular_send::object::empty() const
{
	return
		impl_.empty();
}
