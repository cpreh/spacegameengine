#ifndef ALDA_NET_BUFFER_CIRCULAR_SEND_OBJECT_HPP_INCLUDED
#define ALDA_NET_BUFFER_CIRCULAR_SEND_OBJECT_HPP_INCLUDED

#include <alda/symbol.hpp>
#include <alda/net/size_type.hpp>
#include <alda/net/buffer/max_size.hpp>
#include <alda/net/buffer/circular_send/boost_type.hpp>
#include <alda/net/buffer/circular_send/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace alda
{
namespace net
{
namespace buffer
{
namespace circular_send
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	typedef alda::net::size_type size_type;

	ALDA_SYMBOL
	explicit
	object(
		alda::net::buffer::max_size
	);

	ALDA_SYMBOL
	~object();

	ALDA_SYMBOL
	alda::net::buffer::circular_send::boost_type::const_array_range const
	send_part() const;

	ALDA_SYMBOL
	void
	erase_front(
		alda::net::buffer::circular_send::object::size_type
	);

	ALDA_SYMBOL
	bool
	empty() const;
private:
	alda::net::buffer::circular_send::boost_type impl_;
};

}
}
}
}

#endif
