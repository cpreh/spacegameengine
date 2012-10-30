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


#include <sge/font/object_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text_parameters_fwd.hpp>
#include <sge/font/vector_fwd.hpp>
#include <sge/font/draw/simple.hpp>
#include <sge/font/draw/static_text.hpp>
#include <sge/image/color/any/object_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>


void
sge::font::draw::simple(
	sge::renderer::device::ffp &_renderer,
	sge::renderer::context::ffp &_render_context,
	sge::font::object &_font,
	sge::font::string const &_string,
	sge::font::text_parameters const &_parameters,
	sge::font::vector const &_pos,
	sge::image::color::any::object const &_color,
	sge::renderer::texture::emulate_srgb::type const _emulate_srgb
)
{
	sge::font::draw::static_text text(
		_renderer,
		_font,
		_string,
		_parameters,
		_pos,
		_color,
		_emulate_srgb
	);

	text.draw(
		_render_context
	);
}
