#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/parameters/object.hpp>
#include <sge/renderer/context/scoped.hpp>
#include <sge/renderer/device.hpp>
#include <sge/sprite/geometry/make_random_access_range.hpp>
#include <sge/sprite/process/all.hpp>
#include "testbed_impl.hpp"
#include <rucksack/widget/base.hpp>
#include <sge/image/colors.hpp>
#include <sge/renderer/parameters/object.hpp>
#include <sge/renderer/pixel_format/object.hpp>
#include <sge/window/system.hpp>
#include <sge/sprite/config/unit_type.hpp>
#include <sge/sprite/config/float_type.hpp>
#include <sge/log/global.hpp>
#include <sge/sprite/compare/default.hpp>
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
#include <awl/main/exit_code.hpp>
#include <fcppt/container/bitfield/object_impl.hpp>
#include <fcppt/log/activate_levels.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/text.hpp>

rucksack::examples::testbed_impl::testbed_impl(
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
		systems_.renderer(),
		sge::sprite::buffers::option::dynamic),
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
rucksack::examples::testbed_impl::add_widget(
	widget::base &_widget,
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
rucksack::examples::testbed_impl::run()
{
	while(
		systems_.window_system().poll())
	{
		this->update();

		sge::renderer::context::scoped const scoped_block(
			systems_.renderer(),
			systems_.renderer().onscreen_target());

		this->render(
			scoped_block.get());
	}

	return
		systems_.window_system().exit_code();
}

void
rucksack::examples::testbed_impl::update()
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
rucksack::examples::testbed_impl::render(
	sge::renderer::context::object &_render_context)
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
		sge::sprite::compare::default_());
}

sge::systems::instance const &
rucksack::examples::testbed_impl::systems() const
{
	return systems_;
}

rucksack::examples::testbed_impl::~testbed_impl()
{
}
