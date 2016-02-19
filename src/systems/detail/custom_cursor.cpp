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


#include <sge/input/cursor/move_callback.hpp>
#include <sge/input/cursor/move_event.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/optional_position.hpp>
#include <sge/input/cursor/position.hpp>
#include <sge/input/cursor/position_unit.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/single_impl.hpp>
#include <sge/sprite/buffers/with_declaration_impl.hpp>
#include <sge/sprite/process/one.hpp>
#include <sge/sprite/roles/pos.hpp>
#include <sge/sprite/roles/texture0.hpp>
#include <sge/sprite/state/object_impl.hpp>
#include <sge/sprite/state/parameters_impl.hpp>
#include <sge/src/systems/detail/custom_cursor.hpp>
#include <sge/systems/cursor_hotspot.hpp>
#include <sge/texture/const_part_ref.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/object_impl.hpp>
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
			sge::input::cursor::move_callback{
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
	fcppt::optional::maybe_void(
		sprite_,
		[
			&_context,
			this
		](
			sprite_object const &_sprite
		)
		{
			sge::sprite::process::one(
				_context,
				_sprite,
				sprite_buffers_,
				sprite_state_
			);
		}
	);
}

sge::systems::cursor_hotspot
sge::systems::detail::custom_cursor::hotspot() const
{
	return
		hotspot_;
}

sge::systems::detail::custom_cursor::optional_sprite
sge::systems::detail::custom_cursor::make_sprite(
	sge::input::cursor::optional_position const _opt_pos
) const
{
	return
		fcppt::optional::map(
			_opt_pos,
			[
				this
			](
				sge::input::cursor::position const _pos
			)
			{
				return
					sprite_object{
						sge::sprite::roles::pos{} =
							_pos
							-
							fcppt::math::vector::structure_cast<
								sge::input::cursor::position,
								fcppt::cast::size_fun
							>(
								fcppt::math::vector::to_signed(
									hotspot_.get()
								)
							),
						sge::sprite::roles::texture0{} =
							sge::texture::const_part_ref{
								texture_
							}
					};
			}
		);
}
