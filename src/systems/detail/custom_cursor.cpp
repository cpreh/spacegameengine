/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/input/cursor/move_event.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/optional_position.hpp>
#include <sge/input/cursor/position.hpp>
#include <sge/input/cursor/position_unit.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/parameters_impl.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/single_impl.hpp>
#include <sge/sprite/buffers/with_declaration_impl.hpp>
#include <sge/sprite/process/one.hpp>
#include <sge/sprite/state/object_impl.hpp>
#include <sge/sprite/state/parameters_impl.hpp>
#include <sge/src/systems/detail/custom_cursor.hpp>
#include <sge/systems/cursor_hotspot.hpp>
#include <sge/texture/const_optional_part_ref.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/optional_bind_construct.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/vector/to_signed.hpp>
#include <fcppt/signal/auto_connection.hpp>


sge::systems::detail::custom_cursor::custom_cursor(
	sge::renderer::device::ffp &_renderer,
	sge::input::cursor::object &_cursor,
	sge::texture::part const &_texture,
	sge::systems::cursor_hotspot const _hotspot
)
:
	texture_(
		_texture
	),
	hotspot_{
		_hotspot
	},
	sprite_buffers_{
		_renderer,
		sge::sprite::buffers::option::dynamic
	},
	sprite_state_{
		_renderer,
		sprite_state_parameters()
	},
	sprite_{
		this->make_sprite(
			_cursor.position()
		)
	},
	move_connection_{
		_cursor.move_callback(
			[
				this
			](
				sge::input::cursor::move_event const &_event
			)
			{
				sprite_ =
					this->make_sprite(
						_event.position()
					);
			}
		)
	}
{
}

sge::systems::detail::custom_cursor::~custom_cursor()
{
}

void
sge::systems::detail::custom_cursor::draw(
	sge::renderer::context::ffp &_context
)
{
	if(
		sprite_
	)
		sge::sprite::process::one(
			_context,
			*sprite_,
			sprite_buffers_,
			sprite_state_
		);
}

sge::systems::cursor_hotspot const
sge::systems::detail::custom_cursor::hotspot() const
{
	return
		hotspot_;
}

sge::systems::detail::custom_cursor::optional_sprite
sge::systems::detail::custom_cursor::make_sprite(
	sge::input::cursor::optional_position const _pos
) const
{
	return
		fcppt::optional_bind_construct(
			_pos,
			[
				this
			](
				sge::input::cursor::position const &_npos
			)
			{
				return
					sprite_object{
						sprite_parameters{}
						.pos(
							_npos
							-
							fcppt::math::vector::structure_cast<
								sge::input::cursor::position,
								fcppt::cast::size_fun
							>(
								fcppt::math::vector::to_signed(
									hotspot_.get()
								)
							)
						)
						.texture(
							sge::texture::const_optional_part_ref{
								texture_
							}
						)
						.texture_size()
					};
			}
		);
}
