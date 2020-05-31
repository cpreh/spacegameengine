//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_IMPL_BUFFER_CONST_SCOPED_LOCK_IMPL_HPP_INCLUDED
#define SGE_RENDERER_IMPL_BUFFER_CONST_SCOPED_LOCK_IMPL_HPP_INCLUDED

#include <sge/renderer/buffer/const_scoped_lock.hpp>


template<
	typename Tag
>
sge::renderer::buffer::const_scoped_lock<
	Tag
>::const_scoped_lock(
	buffer_ref const _buffer
)
:
	buffer_(
		_buffer
	),
	view_(
		buffer_.get().lock_c()
	)
{
}

template<
	typename Tag
>
sge::renderer::buffer::const_scoped_lock<
	Tag
>::const_scoped_lock(
	buffer_ref const _buffer,
	lock_area const &_area
)
:
	buffer_(
		_buffer
	),
	view_(
		buffer_.get().lock_c(
			_area
		)
	)
{
}

template<
	typename Tag
>
typename
sge::renderer::buffer::const_scoped_lock<
	Tag
>::const_view
sge::renderer::buffer::const_scoped_lock<
	Tag
>::value() const
{
	return
		view_;
}

template<
	typename Tag
>
sge::renderer::buffer::const_scoped_lock<
	Tag
>::~const_scoped_lock()
{
	buffer_.get().unlock();
}

#endif
