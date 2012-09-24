/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/image/colors.hpp>
#include <sge/log/global.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/context/scoped_ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/parameters/object.hpp>
#include <sge/renderer/pixel_format/object.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/parameters_impl.hpp>
#include <sge/sprite/buffers/single_impl.hpp>
#include <sge/sprite/buffers/with_declaration_impl.hpp>
#include <sge/sprite/compare/default.hpp>
#include <sge/sprite/config/float_type.hpp>
#include <sge/sprite/config/unit_type.hpp>
#include <sge/sprite/geometry/make_random_access_range.hpp>
#include <sge/sprite/process/all.hpp>
#include <sge/sprite/state/object_impl.hpp>
#include <sge/sprite/state/parameters_impl.hpp>
#include <sge/src/rucksack/testbed/object_impl.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/input_helper.hpp>
#include <sge/systems/input_helper_field.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/quit_on_escape.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/window.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/window/parameters.hpp>
#include <sge/window/system.hpp>
#include <awl/main/exit_code.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/activate_levels.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/signal/auto_connection.hpp>


sge::rucksack::testbed::object_impl::object_impl(
	sge::window::title const &_window_title)
:
	systems_(
		sge::systems::list()
		(sge::systems::window(
				sge::window::parameters(
					_window_title,
					sge::window::dim(
						1024,
						768))))
		(sge::systems::renderer(
				sge::renderer::parameters::object(
					sge::renderer::pixel_format::object(
						sge::renderer::pixel_format::color::depth32,
						sge::renderer::pixel_format::depth_stencil::off,
						sge::renderer::pixel_format::optional_multi_samples(),
						sge::renderer::pixel_format::srgb::no),
					sge::renderer::parameters::vsync::on,
					sge::renderer::display_mode::optional_object()),
				sge::viewport::fill_on_resize()))
		(sge::systems::input(
				sge::systems::input_helper_field(
					sge::systems::input_helper::keyboard_collector),
				sge::systems::cursor_option_field::null()))),
	buffers_(
		systems_.renderer_ffp(),
		sge::sprite::buffers::option::dynamic),
	sprite_states_(
		systems_.renderer_ffp(),
		sge::rucksack::testbed::object_impl::sprite_state_parameters(
			systems_.viewport_manager())),
	sprites_(),
	quit_connection_(
		sge::systems::quit_on_escape(
			systems_))
{
	fcppt::log::activate_levels(
		sge::log::global(),
		fcppt::log::level::debug);
}

void
sge::rucksack::testbed::object_impl::add_widget(
	sge::rucksack::widget::base &_widget,
	sge::image::color::any::object const &_color)
{
	sprites_.push_back(
		std::make_pair(
			&_widget,
			sprite_object(
				sprite_parameters()
					.any_color(
						_color))));
}

awl::main::exit_code const
sge::rucksack::testbed::object_impl::run()
{
	while(
		systems_.window_system().poll())
	{
		this->update();

		sge::renderer::context::scoped_ffp const scoped_block(
			systems_.renderer_ffp(),
			systems_.renderer_ffp().onscreen_target());

		this->render(
			scoped_block.get());
	}

	return
		systems_.window_system().exit_code();
}

void
sge::rucksack::testbed::object_impl::update()
{
	for(
		sprite_list::iterator it =
			sprites_.begin();
		it != sprites_.end();
		++it)
	{
		it->second.pos(
			it->first->position());
		it->second.size(
			it->first->size());
	}
}

void
sge::rucksack::testbed::object_impl::render(
	sge::renderer::context::ffp &_render_context)
{
	/*
	sge::renderer::state::scoped scoped_state(
		systems_.renderer(),
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_back_buffer = true)
			(sge::renderer::state::color::back_buffer_clear_color = sge::image::colors::black()));
			*/

	typedef
	std::vector<sprite_object>
	sprite_sequence;

	sprite_sequence raw_sprites;

	for(
		sprite_list::const_iterator it =
			sprites_.begin();
		it != sprites_.end();
		++it)
		raw_sprites.push_back(
			it->second);

	sge::sprite::process::all(
		_render_context,
		sge::sprite::geometry::make_random_access_range(
			raw_sprites.begin(),
			raw_sprites.end()),
		buffers_,
		sge::sprite::compare::default_(),
		sprite_states_);
}

sge::systems::instance const &
sge::rucksack::testbed::object_impl::systems() const
{
	return systems_;
}

sge::rucksack::testbed::object_impl::~object_impl()
{
}
