/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/gui/impl/draw_image_repeat.hpp>
#include <sge/gui/impl/draw_sprite.hpp>
#include <sge/gui/impl/image_sprite_choices.hpp>
#include <sge/gui/impl/sprite_type_choices.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/rect.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/config/texture_coordinates.hpp>
#include <sge/sprite/config/texture_size_option.hpp>
#include <sge/sprite/roles/pos.hpp>
#include <sge/sprite/roles/repetition.hpp>
#include <sge/sprite/roles/size.hpp>
#include <sge/sprite/roles/texture0.hpp>
#include <sge/sprite/types/repetition.hpp>
#include <sge/texture/const_part_ref.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/cast/int_to_float_fun.hpp>
#include <fcppt/math/dim/to_vector.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/structure_cast.hpp>


void
sge::gui::impl::draw_image_repeat(
	sge::renderer::device::ffp &_renderer,
	sge::renderer::context::ffp &_context,
	sge::texture::part const &_texture,
	sge::rucksack::rect const _rect
)
{
	typedef
	sge::sprite::types::repetition<
		sge::gui::impl::sprite_type_choices
	>
	repetition_type;

	sge::gui::impl::draw_sprite(
		_renderer,
		_context,
		sge::sprite::object<
			sge::gui::impl::image_sprite_choices<
				sge::sprite::config::texture_coordinates::repetition,
				sge::sprite::config::texture_size_option::never
			>
		>(
			sge::sprite::roles::pos{} =
				_rect.pos(),
			sge::sprite::roles::texture0{} =
				sge::texture::const_part_ref(
					_texture
				),
			sge::sprite::roles::repetition{} =
				fcppt::math::vector::structure_cast<
					repetition_type,
					fcppt::cast::int_to_float_fun
				>(
					fcppt::math::dim::to_vector(
						_rect.size()
					)
				)
				/
				fcppt::math::vector::structure_cast<
					repetition_type,
					fcppt::cast::int_to_float_fun
				>(
					fcppt::math::dim::to_vector(
						_texture.size()
					)
				),
			sge::sprite::roles::size{} =
				_rect.size()
		)
	);
}
