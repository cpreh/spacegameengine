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
#include <sge/renderer/transform.hpp>
#include <sge/renderer/texture.hpp>
#include <sge/math/compare.hpp>
#include <sge/math/rect_impl.hpp>
#include <sge/log/headers.hpp>
#include <ostream>

sge::texture::part::~part()
{}

sge::math::rect const
sge::texture::part::area_texc(
	const space_unit repeat) const
{
	if(!math::compare(repeat, static_cast<space_unit>(1)) && !repeatable())
		SGE_LOG_WARNING(
			log::global(),
			log::_1 << SGE_TEXT("texture not repeatable but repetition is ")
			        << repeat
			        << SGE_TEXT('!'));

	renderer::const_texture_ptr const tex = my_texture();
	return tex
		? renderer::tex_size_to_space_rect(
			area(),
			tex->dim(),
			repeat)
		: math::rect();
}
