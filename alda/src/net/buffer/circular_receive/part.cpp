#include <alda/net/buffer/circular_receive/part.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iterator>
#include <fcppt/config/external_end.hpp>


alda::net::buffer::circular_receive::part::part(
	pointer const _begin,
	pointer const _end
)
:
	begin_(
		_begin
	),
	end_(
		_end
	)
{
}

alda::net::buffer::circular_receive::part::pointer
alda::net::buffer::circular_receive::part::begin() const
{
	return begin_;
}

alda::net::buffer::circular_receive::part::pointer
alda::net::buffer::circular_receive::part::end() const
{
	return end_;
}

alda::net::buffer::circular_receive::part::size_type
alda::net::buffer::circular_receive::part::size() const
{
	return
		static_cast<
			alda::net::buffer::circular_receive::part::size_type
		>(
			std::distance(
				this->begin(),
				this->end()
			)
		);
}

bool
alda::net::buffer::circular_receive::part::empty() const
{
	return
		this->size() == 0u;
}
