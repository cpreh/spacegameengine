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


#ifndef SGE_SRC_SYSTEMS_DETAIL_CUSTOM_CURSOR_HPP_INCLUDED
#define SGE_SRC_SYSTEMS_DETAIL_CUSTOM_CURSOR_HPP_INCLUDED

#include <sge/input/cursor/object_fwd.hpp>
#include <sge/input/cursor/optional_position_fwd.hpp>
#include <sge/input/cursor/position_unit.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/sprite/object_decl.hpp>
#include <sge/sprite/buffers/single_decl.hpp>
#include <sge/sprite/buffers/with_declaration_decl.hpp>
#include <sge/sprite/config/choices.hpp>
#include <sge/sprite/config/float_type.hpp>
#include <sge/sprite/config/normal_size.hpp>
#include <sge/sprite/config/pos.hpp>
#include <sge/sprite/config/pos_option.hpp>
#include <sge/sprite/config/texture_coordinates.hpp>
#include <sge/sprite/config/texture_level_count.hpp>
#include <sge/sprite/config/texture_ownership.hpp>
#include <sge/sprite/config/texture_size_option.hpp>
#include <sge/sprite/config/type_choices.hpp>
#include <sge/sprite/config/unit_type.hpp>
#include <sge/sprite/config/with_texture.hpp>
#include <sge/sprite/state/all_choices.hpp>
#include <sge/sprite/state/object_decl.hpp>
#include <sge/sprite/state/parameters_fwd.hpp>
#include <sge/systems/cursor_hotspot.hpp>
#include <sge/systems/detail/custom_cursor_fwd.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional/object_decl.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace systems
{
namespace detail
{

class custom_cursor
{
	FCPPT_NONCOPYABLE(
		custom_cursor
	);
public:
	custom_cursor(
		sge::renderer::device::ffp &,
		sge::input::cursor::object &,
		sge::texture::part const &,
		sge::systems::cursor_hotspot
	);

	~custom_cursor();

	void
	draw(
		sge::renderer::context::ffp &
	);

	sge::systems::cursor_hotspot
	hotspot() const;
private:
	sge::texture::part const &texture_;

	sge::systems::cursor_hotspot const hotspot_;

	typedef
	sge::sprite::config::choices<
		sge::sprite::config::type_choices<
			sge::sprite::config::unit_type<
				sge::input::cursor::position_unit
			>,
			sge::sprite::config::float_type<
				float
			>
		>,
		sge::sprite::config::pos<
			sge::sprite::config::pos_option::pos
		>,
		sge::sprite::config::normal_size<
			sge::sprite::config::texture_size_option::always
		>,
		boost::mpl::vector1<
			sge::sprite::config::with_texture<
				sge::sprite::config::texture_level_count<
					1u
				>,
				sge::sprite::config::texture_coordinates::automatic,
				sge::sprite::config::texture_ownership::reference
			>
		>
	>
	sprite_choices;

	typedef
	sge::sprite::buffers::with_declaration<
		sge::sprite::buffers::single<
			sprite_choices
		>
	>
	sprite_buffers;

	sprite_buffers sprite_buffers_;

	typedef
	sge::sprite::state::all_choices
	sprite_state_choices;

	typedef
	sge::sprite::state::object<
		sprite_state_choices
	>
	sprite_state;

	typedef
	sge::sprite::state::parameters<
		sprite_state_choices
	>
	sprite_state_parameters;

	sprite_state sprite_state_;

	typedef
	sge::sprite::object<
		sprite_choices
	>
	sprite_object;

	typedef
	fcppt::optional::object<
		sprite_object
	>
	optional_sprite;

	optional_sprite sprite_;

	optional_sprite
	make_sprite(
		sge::input::cursor::optional_position
	) const;

	fcppt::signal::auto_connection const move_connection_;
};

}
}
}

#endif
