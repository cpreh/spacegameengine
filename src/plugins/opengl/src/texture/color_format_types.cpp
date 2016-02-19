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


#include <sge/opengl/convert/color_to_format.hpp>
#include <sge/opengl/convert/color_to_format_type.hpp>
#include <sge/opengl/convert/color_to_internal_format.hpp>
#include <sge/opengl/texture/best_color_format.hpp>
#include <sge/opengl/texture/color_format_types.hpp>
#include <sge/renderer/texture/color_format.hpp>
#include <sge/renderer/texture/translate_srgb_emulation.hpp>


sge::opengl::texture::color_format_types::format
sge::opengl::texture::color_format_types::best_format(
	sge::renderer::texture::color_format const &_format
)
{
	return
		sge::opengl::texture::best_color_format(
			_format.format()
		);
}

sge::opengl::texture::color_format_types::convert_format_function_type
sge::opengl::texture::color_format_types::convert_format()
{
	return
		&sge::opengl::convert::color_to_format;
}

sge::opengl::texture::color_format_types::convert_format_type_function
sge::opengl::texture::color_format_types::convert_format_type()
{
	return
		&sge::opengl::convert::color_to_format_type;
}

sge::opengl::texture::color_format_types::convert_internal_format_function
sge::opengl::texture::color_format_types::convert_internal_format()
{
	return
		&sge::opengl::convert::color_to_internal_format;
}

sge::opengl::texture::color_format_types::format
sge::opengl::texture::color_format_types::translate_format(
	sge::opengl::texture::color_format_types::format const _format,
	sge::renderer::texture::color_format const &_original_format
)
{
	return
		sge::renderer::texture::translate_srgb_emulation(
			sge::renderer::texture::color_format(
				_format,
				_original_format.emulate_srgb()
			)
		);
}
