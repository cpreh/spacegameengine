/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/image/color/predef.hpp>
#include <sge/image/color/rgba8_format.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/input/cursor/button_code.hpp>
#include <sge/input/cursor/button_event.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/optional_position.hpp>
#include <sge/input/cursor/position.hpp>
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/context/scoped_ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/display_mode/parameters.hpp>
#include <sge/renderer/display_mode/vsync.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/object.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/parameters.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/single.hpp>
#include <sge/sprite/buffers/with_declaration.hpp>
#include <sge/sprite/compare/default.hpp>
#include <sge/sprite/config/choices.hpp>
#include <sge/sprite/config/float_type.hpp>
#include <sge/sprite/config/normal_size.hpp>
#include <sge/sprite/config/type_choices.hpp>
#include <sge/sprite/config/unit_type.hpp>
#include <sge/sprite/config/with_color.hpp>
#include <sge/sprite/geometry/make_random_access_range.hpp>
#include <sge/sprite/process/all.hpp>
#include <sge/sprite/state/all_choices.hpp>
#include <sge/sprite/state/object.hpp>
#include <sge/systems/cursor_demuxer.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/keyboard_collector.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/original_window.hpp>
#include <sge/systems/quit_on_escape.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/renderer_caps.hpp>
#include <sge/systems/window.hpp>
#include <sge/systems/with_input.hpp>
#include <sge/systems/with_renderer.hpp>
#include <sge/systems/with_window.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/viewport/manager.hpp>
#include <sge/window/object.hpp>
#include <sge/window/system.hpp>
#include <sge/window/title.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context_fwd.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/maybe_void.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/cast/to_signed_fun.hpp>
#include <fcppt/cast/to_unsigned_fun.hpp>
#include <fcppt/container/grid/in_range.hpp>
#include <fcppt/container/grid/make_pos_range.hpp>
#include <fcppt/container/grid/object.hpp>
#include <fcppt/container/grid/pos.hpp>
#include <fcppt/container/grid/resize_preserve_init.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/math/bresenham.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/dim.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <example_main.hpp>
#include <exception>
#include <iostream>
#include <ostream>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


awl::main::exit_code const
example_main(
	awl::main::function_context const &
)
try
{
	sge::systems::instance<
		boost::mpl::vector3<
			sge::systems::with_window,
			sge::systems::with_renderer<
				sge::systems::renderer_caps::ffp
			>,
			sge::systems::with_input<
				boost::mpl::vector2<
					sge::systems::cursor_demuxer,
					sge::systems::keyboard_collector
				>
			>
		>
	> const sys(
		sge::systems::make_list
		(
			sge::systems::window(
				sge::systems::original_window(
					sge::window::title(
						FCPPT_TEXT("sge line of sight example")
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
				sge::viewport::fill_on_resize()
			)
		)
		(
			sge::systems::input(
				sge::systems::cursor_option_field::null()
			)
		)
	);

	typedef
	sge::image::color::rgba8_format
	color_format;

	typedef
	sge::sprite::config::choices<
		sge::sprite::config::type_choices<
			sge::sprite::config::unit_type<
				int
			>,
			sge::sprite::config::float_type<
				float
			>
		>,
		sge::sprite::config::normal_size,
		boost::mpl::vector1<
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
	sprite_buffers_type;

	typedef
	sge::sprite::object<
		sprite_choices
	>
	sprite_object;

	typedef
	sge::sprite::parameters<
		sprite_choices
	>
	sprite_parameters;

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

	sprite_state_object sprite_state(
		sys.renderer_device_ffp(),
		sprite_state_parameters()
	);

	sprite_buffers_type sprite_buffers(
		sys.renderer_device_ffp(),
		sge::sprite::buffers::option::dynamic
	);

	typedef
	fcppt::container::grid::object<
		sprite_object,
		2
	>
	sprite_grid;

	sprite_object::dim const cell_size(
		32,
		32
	);

	auto const make_sprite_parameters(
		[
			cell_size
		]()
		{
			return
				sprite_parameters()
				.pos(
					sprite_object::vector::null()
				)
				.size(
					cell_size
				)
				.any_color(
					sge::image::color::predef::white()
				);
		}
	);

	sprite_grid sprites(
		fcppt::math::dim::structure_cast<
			sprite_grid::dim,
			fcppt::cast::size_fun
		>(
			// TODO: Use something else here
			sys.window().size()
		)
		/
		fcppt::math::dim::structure_cast<
			sprite_grid::dim,
			fcppt::cast::size_fun
		>(
			cell_size
		),
		sprite_object(
			make_sprite_parameters()
		)
	);

	auto const update_positions(
		[
			cell_size
		](
			sprite_grid &_sprites
		)
		{
			for(
				auto item
				:
				fcppt::container::grid::make_pos_range(
					_sprites
				)
			)
				item.value().pos(
					fcppt::math::vector::structure_cast<
						sprite_object::vector,
						fcppt::cast::size_fun
					>(
						item.pos()
					)
					*
					cell_size
				);
		}
	);

	update_positions(
		sprites
	);

	typedef
	std::make_signed<
		sprite_grid::size_type
	>::type
	difference_type;

	typedef
	fcppt::container::grid::pos<
		difference_type,
		2
	>
	signed_pos;

	fcppt::signal::scoped_connection const manage_connection(
		sys.viewport_manager().manage_callback(
			[
				&sprites,
				update_positions,
				make_sprite_parameters,
				cell_size
			](
				sge::renderer::target::viewport const &_viewport
			)
			{
				fcppt::container::grid::resize_preserve_init(
					sprites,
					fcppt::math::dim::structure_cast<
						sprite_grid::dim,
						fcppt::cast::size_fun
					>(
						fcppt::math::dim::structure_cast<
							sge::renderer::screen_size,
							fcppt::cast::to_unsigned_fun
						>(
							_viewport.get().size()
						)
					)
					/
					fcppt::math::dim::structure_cast<
						sprite_grid::dim,
						fcppt::cast::size_fun
					>(
						cell_size
					),
					sprite_object(
						make_sprite_parameters()
					)
				);

				update_positions(
					sprites
				);
			}
		)
	);

	fcppt::signal::scoped_connection const escape_connection(
		sge::systems::quit_on_escape(
			sys
		)
	);

	sge::input::cursor::optional_position last_position;

	fcppt::signal::scoped_connection const click_connection(
		sys.cursor_demuxer().button_callback(
			[
				&sprites,
				&last_position,
				&sys,
				cell_size
			](
				sge::input::cursor::button_event const &_event
			)
			{
				if(
					!_event.pressed()
					||
					_event.button_code()
					!=
					sge::input::cursor::button_code::left
				)
					return;

				fcppt::maybe_void(
					sys.cursor_demuxer().position(),
					[
						&sprites,
						&last_position,
						cell_size
					](
						sge::input::cursor::position const _cur_position
					)
					{
						sprite_grid::dim const cell_size_dim(
							fcppt::math::dim::structure_cast<
								sprite_grid::dim,
								fcppt::cast::size_fun
							>(
								cell_size
							)
						);

						sprite_grid::pos const cur_grid_position(
							fcppt::math::vector::structure_cast<
								sprite_grid::pos,
								fcppt::cast::size_fun
							>(
								_cur_position
							)
							/
							cell_size_dim
						);

						if(
							!fcppt::container::grid::in_range(
								sprites,
								cur_grid_position
							)
						)
							return;

						fcppt::maybe(
							last_position,
							[
								&last_position,
								_cur_position
							]{
								last_position =
									sge::input::cursor::optional_position{
										_cur_position
									};
							},
							[
								&last_position,
								&sprites,
								cell_size_dim,
								cur_grid_position
							](
								sge::input::cursor::position const _last_position
							)
							{
								sprite_grid::pos const last_grid_position(
									fcppt::math::vector::structure_cast<
										sprite_grid::pos,
										fcppt::cast::to_unsigned_fun
									>(
										fcppt::math::vector::structure_cast<
											signed_pos,
											fcppt::cast::size_fun
										>(
											_last_position
										)
									)
									/
									cell_size_dim
								);

								fcppt::math::bresenham(
									fcppt::math::vector::structure_cast<
										signed_pos,
										fcppt::cast::to_signed_fun
									>(
										cur_grid_position
									),
									fcppt::math::vector::structure_cast<
										signed_pos,
										fcppt::cast::to_signed_fun
									>(
										last_grid_position
									),
									[
										&sprites
									](
										signed_pos const _pos
									)
									{
										sprites[
											fcppt::math::vector::structure_cast<
												sprite_grid::pos,
												fcppt::cast::to_unsigned_fun
											>(
												_pos
											)
										].color(
											sge::image::color::any::convert<
												color_format
											>(
												sge::image::color::predef::red()
											)
										);

										return
											true;
									}
								);

								last_position =
									sge::input::cursor::optional_position{};
							}
						);
					}
				);
			}
		)
	);

	fcppt::signal::scoped_connection const clear_connection(
		sys.keyboard_collector().key_callback(
			sge::input::keyboard::action(
				sge::input::keyboard::key_code::c,
				[
					&sprites
				]()
				{
					for(
						auto &element
						:
						sprites
					)
						element.color(
							sge::image::color::any::convert<
								color_format
							>(
								sge::image::color::predef::white()
							)
						);
				}
			)
		)
	);

	while(
		sys.window_system().poll()
	)
	{
		sge::renderer::context::scoped_ffp const scoped_block(
			sys.renderer_device_ffp(),
			sys.renderer_device_ffp().onscreen_target()
		);

		scoped_block.get().clear(
			sge::renderer::clear::parameters()
			.back_buffer(
				sge::image::color::predef::black()
			)
		);

		sge::sprite::process::all(
			scoped_block.get(),
			sge::sprite::geometry::make_random_access_range(
				sprites
			),
			sprite_buffers,
			sge::sprite::compare::default_(),
			sprite_state
		);
	}

	return
		sys.window_system().exit_code();
}
catch(
	fcppt::exception const &_error
)
{
	fcppt::io::cerr()
		<< _error.string()
		<< FCPPT_TEXT('\n');

	return
		awl::main::exit_failure();
}
catch(
	std::exception const &_error
)
{
	std::cerr
		<< _error.what()
		<< '\n';

	return
		awl::main::exit_failure();
}
