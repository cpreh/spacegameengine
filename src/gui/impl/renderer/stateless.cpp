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


#include <sge/font/draw/set_matrices.hpp>
#include <sge/font/draw/set_states.hpp>
#include <sge/font/draw/static_text.hpp>
#include <sge/gui/impl/draw_image.hpp>
#include <sge/gui/impl/draw_image_repeat.hpp>
#include <sge/gui/impl/fill_rect.hpp>
#include <sge/gui/impl/renderer/stateless.hpp>
#include <sge/gui/renderer/base.hpp>
#include <sge/image/color/any/object_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/rect.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/texture/part_fwd.hpp>


sge::gui::impl::renderer::stateless::stateless(
	sge::renderer::device::ffp &_renderer
)
:
	sge::gui::renderer::base(),
	renderer_(
		_renderer
	)
{
}

sge::gui::impl::renderer::stateless::~stateless()
{
}

void
sge::gui::impl::renderer::stateless::fill_rect(
	sge::renderer::context::ffp &_context,
	sge::rucksack::rect const _rect,
	sge::image::color::any::object const &_color
)
{
	sge::gui::impl::fill_rect(
		renderer_,
		_context,
		_rect,
		_color
	);
}

void
sge::gui::impl::renderer::stateless::draw_image(
	sge::renderer::context::ffp &_context,
	sge::texture::part const &_texture,
	sge::rucksack::vector const _pos
)
{
	sge::gui::impl::draw_image(
		renderer_,
		_context,
		_texture,
		_pos
	);
}

void
sge::gui::impl::renderer::stateless::draw_image_repeat(
	sge::renderer::context::ffp &_context,
	sge::texture::part const &_texture,
	sge::rucksack::rect const _area
)
{
	sge::gui::impl::draw_image_repeat(
		renderer_,
		_context,
		_texture,
		_area
	);
}

void
sge::gui::impl::renderer::stateless::draw_static_text(
	sge::renderer::context::ffp &_context,
	sge::font::draw::static_text const &_static_text
)
{
	_static_text.draw_advanced(
		_context,
		sge::font::draw::set_matrices(
			false
		),
		sge::font::draw::set_states(
			false
		)
	);
}
