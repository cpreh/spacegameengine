/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_SRC_RENDERER_COLOR_BUFFER_BASIC_SCOPED_LOCK_IMPL_HPP_INCLUDED
#define SGE_SRC_RENDERER_COLOR_BUFFER_BASIC_SCOPED_LOCK_IMPL_HPP_INCLUDED

#include <sge/image/view/object.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/color_buffer/basic_scoped_lock.hpp>


template<
	typename Buffer
>
sge::renderer::color_buffer::basic_scoped_lock<
	Buffer
>::basic_scoped_lock(
	buffer_type &_buffer,
	sge::renderer::lock_mode const _mode
)
:
	buffer_(
		_buffer
	),
	view_(
		buffer_.lock(
			_mode
		)
	)
{
}

template<
	typename Buffer
>
sge::renderer::color_buffer::basic_scoped_lock<
	Buffer
>::basic_scoped_lock(
	buffer_type &_buffer,
	lock_area const &_area,
	sge::renderer::lock_mode const _mode
)
:
	buffer_(
		_buffer
	),
	view_(
		buffer_.lock(
			_area,
			_mode
		)
	)
{
}

template<
	typename Buffer
>
typename sge::renderer::color_buffer::basic_scoped_lock<
	Buffer
>::view const
sge::renderer::color_buffer::basic_scoped_lock<
	Buffer
>::value() const
{
	return view_;
}

template<
	typename Buffer
>
sge::renderer::color_buffer::basic_scoped_lock<
	Buffer
>::~basic_scoped_lock()
{
	buffer_.unlock();
}

#endif
