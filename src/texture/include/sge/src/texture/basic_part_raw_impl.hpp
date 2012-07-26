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


#ifndef SGE_SRC_TEXTURE_BASIC_PART_RAW_IMPL_HPP_INCLUDED
#define SGE_SRC_TEXTURE_BASIC_PART_RAW_IMPL_HPP_INCLUDED

#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/src/texture/init_basic_part.hpp>
#include <sge/src/texture/dereference_basic_part.hpp>
#include <sge/texture/basic_part_raw.hpp>
#include <sge/texture/sub_data.hpp>


template<
	typename Ref
>
sge::texture::basic_part_raw<
	Ref
>::basic_part_raw(
	ref_type _texture
)
:
	texture_(
		sge::texture::init_basic_part(
			_texture
		)
	)
{
}

template<
	typename Ref
>
sge::texture::basic_part_raw<
	Ref
>::~basic_part_raw()
{
}

template<
	typename Ref
>
void
sge::texture::basic_part_raw<
	Ref
>::data(
	sge::image2d::view::const_object const &_src
)
{
	sge::texture::sub_data(
		this->texture(),
		_src,
		this->area().pos()
	);
}

template<
	typename Ref
>
sge::renderer::lock_rect const
sge::texture::basic_part_raw<
	Ref
>::area() const
{
	return
		this->texture().area();
}

template<
	typename Ref
>
sge::renderer::texture::planar &
sge::texture::basic_part_raw<
	Ref
>::texture()
{
	return
		sge::texture::dereference_basic_part(
			texture_
		);
}

template<
	typename Ref
>
sge::renderer::texture::planar const &
sge::texture::basic_part_raw<
	Ref
>::texture() const
{
	return
		sge::texture::dereference_basic_part(
			texture_
		);
}

template<
	typename Ref
>
bool
sge::texture::basic_part_raw<
	Ref
>::repeatable() const
{
	return
		true;
}

#endif
