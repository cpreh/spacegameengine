//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CURSOR_IMPL_DETAIL_OBJECT_HPP_INCLUDED
#define SGE_CURSOR_IMPL_DETAIL_OBJECT_HPP_INCLUDED

#include <sge/cursor/hotspot.hpp>
#include <sge/cursor/detail/object_fwd.hpp>
#include <sge/input/const_processor_ref.hpp>
#include <sge/input/cursor/optional_position_fwd.hpp>
#include <sge/input/cursor/position_unit.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
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
#include <sge/texture/const_part_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/mpl/list/object.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sge
{
namespace cursor
{
namespace detail
{

class object
{
	FCPPT_NONMOVABLE(
		object
	);
public:
	object(
		sge::input::const_processor_ref,
		sge::renderer::device::ffp_ref,
		sge::texture::const_part_ref,
		sge::cursor::hotspot
	);

	~object();

	void
	draw(
		sge::renderer::context::ffp & // NOLINT(google-runtime-references)
	); // NOLINT(google-runtime-references)

	[[nodiscard]]
	sge::cursor::hotspot
	hotspot() const;
private:
	sge::input::const_processor_ref const processor_;

	sge::texture::const_part_ref const texture_;

	sge::cursor::hotspot const hotspot_;

	using
	sprite_choices
	=
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
		fcppt::mpl::list::object<
			sge::sprite::config::with_texture<
				sge::sprite::config::texture_level_count<
					1U
				>,
				sge::sprite::config::texture_coordinates::automatic,
				sge::sprite::config::texture_ownership::reference
			>
		>
	>;

	using
	sprite_buffers
	=
	sge::sprite::buffers::with_declaration<
		sge::sprite::buffers::single<
			sprite_choices
		>
	>;

	sprite_buffers sprite_buffers_;

	using
	sprite_state_choices
	=
	sge::sprite::state::all_choices;

	using
	sprite_state
	=
	sge::sprite::state::object<
		sprite_state_choices
	>;

	using
	sprite_state_parameters
	=
	sge::sprite::state::parameters<
		sprite_state_choices
	>;

	sprite_state sprite_state_;

	using
	sprite_object
	=
	sge::sprite::object<
		sprite_choices
	>;

	using
	optional_sprite
	=
	fcppt::optional::object<
		sprite_object
	>;

	[[nodiscard]]
	optional_sprite
	make_sprite(
		sge::input::cursor::optional_position const &
	) const;
};

}
}
}

#endif
