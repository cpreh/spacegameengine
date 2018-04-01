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


#include <sge/gui/impl/draw_sprite.hpp>
#include <sge/gui/impl/fill_rect.hpp>
#include <sge/gui/impl/sprite_type_choices.hpp>
#include <sge/image/color/rgba8_format.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/image/color/any/object_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/rect.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/config/choices.hpp>
#include <sge/sprite/config/normal_size.hpp>
#include <sge/sprite/config/pos.hpp>
#include <sge/sprite/config/pos_option.hpp>
#include <sge/sprite/config/texture_size_option.hpp>
#include <sge/sprite/config/with_color.hpp>
#include <sge/sprite/roles/color.hpp>
#include <sge/sprite/roles/pos.hpp>
#include <sge/sprite/roles/size.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/sequences/list.hpp>
#include <fcppt/config/external_end.hpp>


void
sge::gui::impl::fill_rect(
	sge::renderer::device::ffp &_renderer,
	sge::renderer::context::ffp &_context,
	sge::rucksack::rect const &_rect,
	sge::image::color::any::object const &_color
)
{
	{
		sge::rucksack::dim const size(
			_rect.size()
		);

		if(
			size.w() <= -0
			||
			size.h() <= 0
		)
			return;
	}

	typedef
	sge::image::color::rgba8_format
	color_format;

	typedef
	sge::sprite::config::choices<
		sge::gui::impl::sprite_type_choices,
		sge::sprite::config::pos<
			sge::sprite::config::pos_option::pos
		>,
		sge::sprite::config::normal_size<
			sge::sprite::config::texture_size_option::never
		>,
		brigand::list<
			sge::sprite::config::with_color<
				color_format
			>
		>
	>
	choices;

	sge::gui::impl::draw_sprite(
		_renderer,
		_context,
		sge::sprite::object<
			choices
		>(
			sge::sprite::roles::pos{} =
				_rect.pos(),
			sge::sprite::roles::size{} =
				_rect.size(),
			sge::sprite::roles::color{} =
				sge::image::color::any::convert<
					color_format
				>(
					_color
				)
		)
	);
}
