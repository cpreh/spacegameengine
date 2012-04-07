#include <alda/net/buffer/max_size.hpp>
#include <alda/net/buffer/circular_receive/object.hpp>
#include <alda/net/buffer/circular_receive/part.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/next_prior.hpp>
#include <cstddef>
#include <fcppt/config/external_end.hpp>


alda::net::buffer::circular_receive::object::object(
	alda::net::buffer::max_size const _max_size
)
:
	impl_(
		_max_size.get()
	),
	begin_(
		impl_.data()
	),
	end_(
		impl_.data()
	)
{
}

alda::net::buffer::circular_receive::object::~object()
{
}

alda::net::buffer::circular_receive::part const
alda::net::buffer::circular_receive::object::next_receive_part()
{
	return
		begin_ <= end_
		?
			alda::net::buffer::circular_receive::part(
				end_,
				begin_ == impl_.data()
				?
					boost::prior(
						impl_.data_end()
					)
				:
					impl_.data_end()
			)
		:
			alda::net::buffer::circular_receive::part(
				end_,
				boost::prior(
					begin_
				)
			);
}

void
alda::net::buffer::circular_receive::object::bytes_received(
	size_type const _size
)
{
	FCPPT_ASSERT_PRE(
		static_cast<
			size_type
		>
		(
			impl_.data_end() - end_
		)
		>= _size
	);

	end_ += _size;

	if(
		end_ == impl_.end()
	)
		end_ = impl_.begin();

	FCPPT_ASSERT_ERROR(
		begin_ != end_
	);
}

alda::net::buffer::circular_receive::object::joined_range const
alda::net::buffer::circular_receive::object::range() const
{
	return
		begin_ <= end_
		?
			alda::net::buffer::circular_receive::object::joined_range(
				alda::net::buffer::circular_receive::object::iterator_range(
					static_cast<
						const_pointer
					>(
						begin_
					),
					static_cast<
						const_pointer
					>(
						end_
					)
				),
				alda::net::buffer::circular_receive::object::iterator_range()
			)
		:
			alda::net::buffer::circular_receive::object::joined_range(
				alda::net::buffer::circular_receive::object::iterator_range(
					static_cast<
						const_pointer
					>(
						begin_
					),
					impl_.data_end()
				),
				alda::net::buffer::circular_receive::object::iterator_range(
					impl_.data(),
					static_cast<
						const_pointer
					>(
						end_
					)
				)
			);
}

void
alda::net::buffer::circular_receive::object::erase(
	size_type const _size
)
{
	begin_ =
		impl_.data()
		+
		(
			(
				begin_
				-
				impl_.data()
				+
				static_cast<
					std::ptrdiff_t
				>(
					_size
				)
			)
			%
			static_cast<
				std::ptrdiff_t
			>(
				impl_.size()
			)
		);
}


alda::net::buffer::circular_receive::object::size_type
alda::net::buffer::circular_receive::object::read_size() const
{
	return
		static_cast<
			size_type
		>(
			this->range().size()
		);
}

alda::net::buffer::circular_receive::object::size_type
alda::net::buffer::circular_receive::object::capacity() const
{
	return
		impl_.size() - 1u;
}

void
alda::net::buffer::circular_receive::object::clear()
{
	begin_ = end_ = impl_.begin();
}
