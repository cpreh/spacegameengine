//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/log/location.hpp>
#include <sge/log/option.hpp>
#include <sge/log/option_container.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/context/scoped_ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/display_mode/parameters.hpp>
#include <sge/renderer/display_mode/vsync.hpp>
#include <sge/renderer/event/render.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/object.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/target/base.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/rucksack/testbed/systems.hpp>
#include <sge/rucksack/testbed/impl/object_impl.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/buffers/single_impl.hpp>
#include <sge/sprite/buffers/with_declaration_impl.hpp>
#include <sge/sprite/compare/default.hpp>
#include <sge/sprite/config/float_type.hpp>
#include <sge/sprite/config/unit_type.hpp>
#include <sge/sprite/geometry/make_random_access_range.hpp>
#include <sge/sprite/process/all.hpp>
#include <sge/sprite/roles/color.hpp>
#include <sge/sprite/roles/pos.hpp>
#include <sge/sprite/roles/size.hpp>
#include <sge/sprite/state/object_impl.hpp>
#include <sge/sprite/state/parameters_impl.hpp>
#include <sge/systems/config.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/log_settings.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/original_window.hpp>
#include <sge/systems/quit_on_escape.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/window.hpp>
#include <sge/systems/window_source.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/viewport/optional_resize_callback.hpp>
#include <sge/window/loop.hpp>
#include <sge/window/loop_function.hpp>
#include <sge/window/title.hpp>
#include <awl/event/base.hpp>
#include <awl/main/exit_code.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/math/dim/null.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <vector>
#include <fcppt/config/external_end.hpp>


sge::rucksack::testbed::object_impl::object_impl(
	sge::window::title const &_window_title
)
:
	systems_(
		sge::systems::make_list
		(
			sge::systems::window(
				sge::systems::window_source(
					sge::systems::original_window(
						_window_title
					)
				)
			)
		)
		(
			sge::systems::renderer(
				sge::renderer::pixel_format::object(
					sge::renderer::pixel_format::color::depth32,
					sge::renderer::pixel_format::depth_stencil::off,
					sge::renderer::pixel_format::optional_multi_samples(),
					sge::renderer::pixel_format::srgb::no
				),
				sge::renderer::display_mode::parameters(
					sge::renderer::display_mode::vsync::on,
					sge::renderer::display_mode::optional_object()
				),
				sge::viewport::optional_resize_callback{
					sge::viewport::fill_on_resize()
				}
			)
		)
		(
			sge::systems::input(
				sge::systems::cursor_option_field::null()
			)
		)
		(
			sge::systems::config()
			.log_settings(
				sge::systems::log_settings(
					sge::log::option_container{
						sge::log::option{
							sge::log::location(),
							fcppt::log::level::debug
						}
					}
				)
			)
		)
	),
	buffers_(
		systems_.renderer_device_ffp(),
		sge::sprite::buffers::option::dynamic
	),
	sprite_states_(
		systems_.renderer_device_ffp(),
		sge::rucksack::testbed::object_impl::sprite_state_parameters()
	),
	sprites_()
{
}

void
sge::rucksack::testbed::object_impl::add_widget(
	sge::rucksack::widget::base &_widget,
	sge::image::color::any::object const &_color
)
{
	sprites_.push_back(
		std::make_pair(
			fcppt::make_ref(
				_widget
			),
			sprite_object(
				sge::sprite::roles::pos{} =
					fcppt::math::vector::null<
						sprite_object::vector
					>(),
				sge::sprite::roles::size{} =
					fcppt::math::dim::null<
						sprite_object::dim
					>(),
				sge::sprite::roles::color{} =
					sge::image::color::any::convert<
						color_format
					>(
						_color
					)
			)
		)
	);
}

awl::main::exit_code
sge::rucksack::testbed::object_impl::run()
{
	auto const draw(
		[
			this
		]{
			this->update();

			sge::renderer::context::scoped_ffp const scoped_block(
				fcppt::make_ref(
					this->systems_.renderer_device_ffp()
				),
				fcppt::reference_to_base<
					sge::renderer::target::base
				>(
					fcppt::make_ref(
						this->systems_.renderer_device_ffp().onscreen_target()
					)
				)
			);

			this->render(
				scoped_block.get()
			);
		}
	);

	return
		sge::window::loop(
			this->systems_.window_system(),
			sge::window::loop_function{
				[
					this,
					&draw
				](
					awl::event::base const &_event
				)
				{
					sge::systems::quit_on_escape(
						this->systems_,
						_event
					);

					fcppt::optional::maybe_void(
						fcppt::cast::dynamic<
							sge::renderer::event::render const
						>(
							_event
						),
						[
							&draw
						](
							fcppt::reference<
								sge::renderer::event::render const
							>
						)
						{
							draw();
						}
					);
				}
			}
		);
}

void
sge::rucksack::testbed::object_impl::update()
{
	for(
		auto &entry
		:
		sprites_
	)
	{
		entry.second.pos(
			entry.first.get().position()
		);

		entry.second.size(
			entry.first.get().size()
		);
	}
}

void
sge::rucksack::testbed::object_impl::render(
	sge::renderer::context::ffp &_render_context
)
{
	_render_context.clear(
		sge::renderer::clear::parameters()
		.back_buffer(
			sge::image::color::any::object{
				sge::image::color::predef::black()
			}
		)
	);

	sge::sprite::process::all(
		_render_context,
		sge::sprite::geometry::make_random_access_range(
			fcppt::algorithm::map<
				std::vector<
					sprite_object
				>
			>(
				sprites_,
				[](
					sprite_list::value_type const &_element
				)
				{
					return
						_element.second;
				}
			)
		),
		buffers_,
		sge::sprite::compare::default_(),
		sprite_states_
	);
}

sge::rucksack::testbed::systems const &
sge::rucksack::testbed::object_impl::systems() const
{
	return
		systems_;
}

sge::rucksack::testbed::object_impl::~object_impl()
{
}
