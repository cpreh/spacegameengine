//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RUCKSACK_TESTBED_IMPL_OBJECT_IMPL_HPP_INCLUDED
#define SGE_RUCKSACK_TESTBED_IMPL_OBJECT_IMPL_HPP_INCLUDED

#include <sge/image/color/rgba8_format.hpp>
#include <sge/image/color/any/object_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/scalar.hpp>
#include <sge/rucksack/testbed/systems.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/sprite/object_decl.hpp>
#include <sge/sprite/buffers/single_decl.hpp>
#include <sge/sprite/buffers/with_declaration_decl.hpp>
#include <sge/sprite/config/choices.hpp>
#include <sge/sprite/config/normal_size.hpp>
#include <sge/sprite/config/pos.hpp>
#include <sge/sprite/config/pos_option.hpp>
#include <sge/sprite/config/texture_size_option.hpp>
#include <sge/sprite/config/type_choices.hpp>
#include <sge/sprite/config/with_color.hpp>
#include <sge/sprite/state/all_choices.hpp>
#include <sge/sprite/state/object_decl.hpp>
#include <sge/sprite/state/parameters_fwd.hpp>
#include <sge/window/title.hpp>
#include <awl/main/exit_code.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <utility>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace rucksack
{
namespace testbed
{

class object_impl
{
	FCPPT_NONCOPYABLE(
		object_impl
	);
public:
	explicit
	object_impl(
		sge::window::title const &
	);

	void
	add_widget(
		sge::rucksack::widget::base &,
		sge::image::color::any::object const &
	);

	awl::main::exit_code
	run();

	void
	update();

	void
	render(
		sge::renderer::context::ffp &
	);

	sge::rucksack::testbed::systems const &
	systems() const;

	~object_impl();
private:
	typedef
	sge::image::color::rgba8_format
	color_format;

	typedef
	sge::sprite::config::choices<
		sge::sprite::config::type_choices<
			sge::sprite::config::unit_type<
				sge::rucksack::scalar
			>,
			sge::sprite::config::float_type<
				float
			>
		>,
		sge::sprite::config::pos<
			sge::sprite::config::pos_option::pos
		>,
		sge::sprite::config::normal_size<
			sge::sprite::config::texture_size_option::never
		>,
		metal::list<
			sge::sprite::config::with_color<
				color_format
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

	typedef
	sge::sprite::object<
		sprite_choices
	>
	sprite_object;

	typedef
	sge::sprite::state::all_choices
	sprite_state_choices;

	typedef
	sge::sprite::state::object<
		sprite_state_choices
	>
	sprite_state_object;

	typedef
	sge::sprite::state::parameters<
		sprite_state_choices
	>
	sprite_state_parameters;

	typedef
	std::vector<
		std::pair<
			fcppt::reference<
				sge::rucksack::widget::base
			>,
			sprite_object
		>
	>
	sprite_list;

	sge::rucksack::testbed::systems const systems_;

	sprite_buffers buffers_;

	sprite_state_object sprite_states_;

	sprite_list sprites_;
};

}
}
}

#endif
