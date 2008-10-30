/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/texture/part.hpp>
#include <sge/texture/atlasing.hpp>
#include <sge/renderer/texture.hpp>
#include <sge/math/compare.hpp>
#include <sge/math/rect_impl.hpp>
#include <sge/log/headers.hpp>
#include <ostream>

namespace
{

template<
	typename T
>
sge::math::basic_rect<T> const
tex_size_to_space_rect(
	sge::renderer::lock_rect const &l,
	sge::renderer::dim_type const &dim,
	T repeat);

}

sge::texture::part::~part()
{}

sge::math::rect const
sge::texture::part::area_texc(
	space_unit const repeat) const
{
	if(!math::compare(repeat, static_cast<space_unit>(1)) && !repeatable())
		SGE_LOG_WARNING(
			log::global(),
			log::_1 << SGE_TEXT("texture not repeatable but repetition is ")
			        << repeat
			        << SGE_TEXT('!'));

	renderer::const_texture_ptr const tex = my_texture();
	return tex
		? tex_size_to_space_rect(
			area(),
			tex->dim(),
			repeat)
		: math::rect();
}

namespace
{

template<
	typename T
>
sge::math::basic_rect<T> const
tex_size_to_space_rect(
	sge::renderer::lock_rect const &l,
	sge::renderer::dim_type const &dim,
	T const repeat)
{
	return sge::math::basic_rect<T>(
		static_cast<T>(l.left()) / static_cast<T>(dim.w()),
		static_cast<T>(l.top()) / static_cast<T>(dim.h()),
		repeat * static_cast<T>(l.right()) / static_cast<T>(dim.w()),
		repeat * static_cast<T>(l.bottom()) / static_cast<T>(dim.h()));
}

}
