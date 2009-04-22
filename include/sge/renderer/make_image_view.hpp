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


#ifndef SGE_RENDERER_MAKE_IMAGE_VIEW_HPP_INCLUDED
#define SGE_RENDERER_MAKE_IMAGE_VIEW_HPP_INCLUDED

#include <sge/renderer/color_format.hpp>
#include <sge/renderer/image_view.hpp>
#include <sge/renderer/dim_type.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/export.hpp>
#include <sge/optional.hpp>

namespace sge
{
namespace renderer
{

typedef optional<
	size_type
> optional_image_pitch;

SGE_SYMBOL image_view const
make_image_view(
	unsigned char *data,
	dim_type const &,
	color_format::type,
	optional_image_pitch pitch
		= optional_image_pitch());

SGE_SYMBOL const_image_view const
make_image_view(
	unsigned char const *data,
	dim_type const &,
	color_format::type,
	optional_image_pitch pitch
		= optional_image_pitch());

}
}

#endif
