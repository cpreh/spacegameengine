//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_IMPL_DETAIL_CUSTOM_CURSOR_HPP_INCLUDED
#define SGE_SYSTEMS_IMPL_DETAIL_CUSTOM_CURSOR_HPP_INCLUDED

#include <sge/input/processor_fwd.hpp>
#include <sge/input/cursor/optional_position_fwd.hpp>
#include <sge/input/cursor/position_unit.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/sprite/object_fwd.hpp>
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
#include <fcppt/optional/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
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
		sge::input::processor const &,
		sge::renderer::device::ffp &,
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
	sge::input::processor const &processor_;

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
		metal::list<
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

	optional_sprite
	make_sprite(
		sge::input::cursor::optional_position
	) const;
};

}
}
}

#endif
