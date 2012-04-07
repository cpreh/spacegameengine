#ifndef ALDA_NET_BUFFER_CIRCULAR_RECEIVE_PART_HPP_INCLUDED
#define ALDA_NET_BUFFER_CIRCULAR_RECEIVE_PART_HPP_INCLUDED

#include <alda/symbol.hpp>
#include <alda/net/size_type.hpp>
#include <alda/net/value_type.hpp>
#include <alda/net/buffer/circular_receive/part_fwd.hpp>
#include <fcppt/nonassignable.hpp>


namespace alda
{
namespace net
{
namespace buffer
{
namespace circular_receive
{

class part
{
	FCPPT_NONASSIGNABLE(
		part
	);
public:
	typedef alda::net::value_type *pointer;

	typedef alda::net::size_type size_type;

	ALDA_SYMBOL
	part(
		pointer begin,
		pointer end
	);

	ALDA_SYMBOL
	pointer
	begin() const;

	ALDA_SYMBOL
	pointer
	end() const;

	ALDA_SYMBOL
	size_type
	size() const;

	ALDA_SYMBOL
	bool
	empty() const;
private:
	pointer const
		begin_,
		end_;
};

}
}
}
}

#endif
