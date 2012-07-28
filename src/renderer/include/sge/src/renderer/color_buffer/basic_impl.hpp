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


#ifndef SGE_SRC_RENDERER_COLOR_BUFFER_BASIC_IMPL_HPP_INCLUDED
#define SGE_SRC_RENDERER_COLOR_BUFFER_BASIC_IMPL_HPP_INCLUDED

#include <sge/image/view/const_object.hpp>
#include <sge/image/view/object.hpp>
#include <sge/renderer/basic_dim.hpp>
#include <sge/renderer/basic_lock_box.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/color_buffer/basic.hpp>


template<
	sge::renderer::size_type Dim
>
sge::renderer::color_buffer::basic<
	Dim
>::basic()
{
}

template<
	sge::renderer::size_type Dim
>
sge::renderer::color_buffer::basic<
	Dim
>::~basic()
{
}

template<
	sge::renderer::size_type Dim
>
typename sge::renderer::color_buffer::basic<
	Dim
>::const_view const
sge::renderer::color_buffer::basic<
	Dim
>::lock() const
{
	return
		this->lock(
			this->area()
		);
}

template<
	sge::renderer::size_type Dim
>
typename sge::renderer::color_buffer::basic<
	Dim
>::view const
sge::renderer::color_buffer::basic<
	Dim
>::lock(
	sge::renderer::lock_mode::type const _mode
)
{
	return
		this->lock(
			this->area(),
			_mode
		);
}

template<
	sge::renderer::size_type Dim
>
typename sge::renderer::color_buffer::basic<
	Dim
>::lock_area const
sge::renderer::color_buffer::basic<
	Dim
>::area() const
{
	return
		lock_area(
			lock_area::vector::null(),
			this->size()
		);
}

template<
	sge::renderer::size_type Dim
>
typename sge::renderer::color_buffer::basic<
	Dim
>::size_type
sge::renderer::color_buffer::basic<
	Dim
>::content() const
{
	return
		this->size().content();
}

#endif
