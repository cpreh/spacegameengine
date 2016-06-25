/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SRC_RENDERER_BUFFER_CONST_SCOPED_LOCK_IMPL_HPP_INCLUDED
#define SGE_SRC_RENDERER_BUFFER_CONST_SCOPED_LOCK_IMPL_HPP_INCLUDED

#include <sge/renderer/buffer/const_scoped_lock.hpp>


template<
	typename Tag
>
sge::renderer::buffer::const_scoped_lock<
	Tag
>::const_scoped_lock(
	buffer_type const &_buffer
)
:
	buffer_(
		_buffer
	),
	view_(
		buffer_.lock_c()
	)
{
}

template<
	typename Tag
>
sge::renderer::buffer::const_scoped_lock<
	Tag
>::const_scoped_lock(
	buffer_type const &_buffer,
	lock_area const &_area
)
:
	buffer_(
		_buffer
	),
	view_(
		buffer_.lock_c(
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
	buffer_.unlock();
}

#endif
