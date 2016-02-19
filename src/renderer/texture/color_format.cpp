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


#include <sge/image/color/format.hpp>
#include <sge/renderer/texture/color_format.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>


sge::renderer::texture::color_format::color_format(
	sge::image::color::format const _format,
	sge::renderer::texture::emulate_srgb const _emulate_srgb
)
:
	format_(
		_format
	),
	emulate_srgb_(
		_emulate_srgb
	)
{
}

sge::image::color::format
sge::renderer::texture::color_format::format() const
{
	return format_;
}

sge::renderer::texture::emulate_srgb
sge::renderer::texture::color_format::emulate_srgb() const
{
	return emulate_srgb_;
}
