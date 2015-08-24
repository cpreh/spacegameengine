/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SRC_RENDERER_BASIC_BUFFER_IMPL_HPP_INCLUDED
#define SGE_SRC_RENDERER_BASIC_BUFFER_IMPL_HPP_INCLUDED

#include <sge/image/view/const_object.hpp>
#include <sge/image/view/object.hpp>
#include <sge/renderer/basic_buffer.hpp>
#include <sge/renderer/basic_dim.hpp>
#include <sge/renderer/basic_lock_box.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <fcppt/math/dim/contents.hpp>
#include <fcppt/math/vector/null.hpp>


template<
	typename Tag
>
sge::renderer::basic_buffer<
	Tag
>::basic_buffer()
{
}

template<
	typename Tag
>
sge::renderer::basic_buffer<
	Tag
>::~basic_buffer()
{
}

template<
	typename Tag
>
typename sge::renderer::basic_buffer<
	Tag
>::const_view const
sge::renderer::basic_buffer<
	Tag
>::lock() const
{
	return
		this->lock(
			this->area()
		);
}

template<
	typename Tag
>
typename sge::renderer::basic_buffer<
	Tag
>::view const
sge::renderer::basic_buffer<
	Tag
>::lock(
	sge::renderer::lock_mode const _mode
)
{
	return
		this->lock(
			this->area(),
			_mode
		);
}

template<
	typename Tag
>
typename sge::renderer::basic_buffer<
	Tag
>::lock_area const
sge::renderer::basic_buffer<
	Tag
>::area() const
{
	return
		lock_area(
			fcppt::math::vector::null<
				typename
				lock_area::vector
			>(),
			this->size()
		);
}

template<
	typename Tag
>
typename sge::renderer::basic_buffer<
	Tag
>::size_type
sge::renderer::basic_buffer<
	Tag
>::content() const
{
	return
		fcppt::math::dim::contents(
			this->size()
		);
}

#endif
