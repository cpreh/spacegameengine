//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_IMPL_BUFFER_SCOPED_LOCK_IMPL_HPP_INCLUDED
#define SGE_RENDERER_IMPL_BUFFER_SCOPED_LOCK_IMPL_HPP_INCLUDED

#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/buffer/scoped_lock.hpp>
#include <sge/renderer/buffer/writable.hpp>


template<
	typename Tag
>
sge::renderer::buffer::scoped_lock<
	Tag
>::scoped_lock(
	buffer_ref const _buffer,
	sge::renderer::lock_mode const _mode
)
:
	buffer_(
		_buffer
	),
	view_(
		buffer_.get().lock(
			_mode
		)
	)
{
}

template<
	typename Tag
>
sge::renderer::buffer::scoped_lock<
	Tag
>::scoped_lock(
	buffer_ref const _buffer,
	lock_area const &_area,
	sge::renderer::lock_mode const _mode
)
:
	buffer_(
		_buffer
	),
	view_(
		buffer_.get().lock(
			_area,
			_mode
		)
	)
{
}

template<
	typename Tag
>
typename
sge::renderer::buffer::scoped_lock<
	Tag
>::view
sge::renderer::buffer::scoped_lock<
	Tag
>::value() const
{
	return
		view_;
}

template<
	typename Tag
>
sge::renderer::buffer::scoped_lock<
	Tag
>::~scoped_lock<
	Tag
>()
{
	buffer_.get().unlock();
}

#endif
