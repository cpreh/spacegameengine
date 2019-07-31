//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/processor.hpp>
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
#include <sge/sprite/compare/default.hpp>
#include <sge/sprite/geometry/make_random_access_range.hpp>
#include <sge/sprite/process/all.hpp>
#include <sge/sprite/roles/pos.hpp>
#include <sge/sprite/roles/texture0.hpp>
#include <sge/sprite/state/object_impl.hpp>
#include <sge/sprite/state/parameters_impl.hpp>
#include <sge/systems/cursor_hotspot.hpp>
#include <sge/systems/impl/detail/custom_cursor.hpp>
#include <sge/texture/const_part_ref.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/algorithm/map_optional.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/vector/to_signed.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


sge::systems::detail::custom_cursor::custom_cursor(
	sge::input::processor const &_processor,
	sge::renderer::device::ffp &_renderer,
	sge::texture::part const &_texture,
	sge::systems::cursor_hotspot const _hotspot
)
:
	processor_{
		_processor
	},
	texture_{
		_texture
	},
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
	typedef
	std::vector<
		sprite_object
	>
	sprite_vector;

	sprite_vector sprites(
		fcppt::algorithm::map_optional<
			sprite_vector
		>(
			processor_.cursors(),
			[
				this
			](
				sge::input::cursor::shared_ptr const &_cursor
			)
			{
				return
					this->make_sprite(
						_cursor->position()
					);
			}
		)
	);

	sge::sprite::process::all(
		_context,
		sge::sprite::geometry::make_random_access_range(
			sprites
		),
		sprite_buffers_,
		sge::sprite::compare::default_(),
		sprite_state_
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
									this->hotspot_.get()
								)
							),
						sge::sprite::roles::texture0{} =
							sge::texture::const_part_ref{
								this->texture_
							}
					};
			}
		);
}
