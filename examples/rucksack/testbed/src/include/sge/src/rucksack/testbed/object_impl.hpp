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


#ifndef SGE_SRC_RUCKSACK_TESTBED_OBJECT_IMPL_HPP_INCLUDED
#define SGE_SRC_RUCKSACK_TESTBED_OBJECT_IMPL_HPP_INCLUDED

#include <sge/image/color/rgba8_format.hpp>
#include <sge/image/color/any/object_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/scalar.hpp>
#include <sge/rucksack/testbed/systems.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/sprite/object_decl.hpp>
#include <sge/sprite/parameters_fwd.hpp>
#include <sge/sprite/buffers/single_decl.hpp>
#include <sge/sprite/buffers/with_declaration_decl.hpp>
#include <sge/sprite/config/choices.hpp>
#include <sge/sprite/config/normal_size.hpp>
#include <sge/sprite/config/type_choices.hpp>
#include <sge/sprite/config/with_color.hpp>
#include <sge/sprite/state/all_choices.hpp>
#include <sge/sprite/state/object_decl.hpp>
#include <sge/sprite/state/parameters_fwd.hpp>
#include <sge/window/title.hpp>
#include <awl/main/exit_code.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
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
	object_impl);
public:
	explicit
	object_impl(
		sge::window::title const &);

	void
	add_widget(
		sge::rucksack::widget::base &,
		sge::image::color::any::object const &);

	awl::main::exit_code const
	run();

	void
	update();

	void
	render(
		sge::renderer::context::ffp &);

	sge::rucksack::testbed::systems const &
	systems() const;

	~object_impl();
private:
	typedef
	sge::sprite::config::choices
	<
		sge::sprite::config::type_choices
		<
			sge::sprite::config::unit_type<rucksack::scalar>,
			sge::sprite::config::float_type<float>
		>,
		sge::sprite::config::normal_size,
		boost::mpl::vector1
		<
			sge::sprite::config::with_color<sge::image::color::rgba8_format>
		>
	>
	sprite_choices;

	typedef
	sge::sprite::buffers::with_declaration
	<
		sge::sprite::buffers::single<sprite_choices>
	>
	sprite_buffers;

	typedef
	sge::sprite::object
	<
		sprite_choices
	>
	sprite_object;

	typedef
	sge::sprite::parameters
	<
		sprite_choices
	>
	sprite_parameters;

	typedef
	sge::sprite::state::all_choices
	sprite_state_choices;

	typedef
	sge::sprite::state::object
	<
		sprite_state_choices
	>
	sprite_state_object;

	typedef
	sge::sprite::state::parameters
	<
		sprite_state_choices
	>
	sprite_state_parameters;

	typedef
	std::vector
	<
		std::pair
		<
			sge::rucksack::widget::base*,
			sprite_object
		>
	>
	sprite_list;

	sge::rucksack::testbed::systems const systems_;
	sprite_buffers buffers_;
	sprite_state_object sprite_states_;
	sprite_list sprites_;
	fcppt::signal::scoped_connection const quit_connection_;
};
}
}
}

#endif

