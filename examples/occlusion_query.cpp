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


#include <sge/camera/perspective_projection_from_viewport.hpp>
#include <sge/camera/coordinate_system/object.hpp>
#include <sge/camera/coordinate_system/identity.hpp>
#include <sge/camera/matrix_conversion/world.hpp>
#include <sge/camera/first_person/object.hpp>
#include <sge/camera/first_person/parameters.hpp>
#include <sge/camera/matrix_conversion/world.hpp>
#include <sge/config/media_path.hpp>
#include <sge/font/metrics.hpp>
#include <sge/font/metrics_scoped_ptr.hpp>
#include <sge/font/rect.hpp>
#include <sge/font/size_type.hpp>
#include <sge/font/system.hpp>
#include <sge/renderer/scoped_transform.hpp>
#include <sge/font/text/align_h.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/scoped.hpp>
#include <sge/renderer/state/bool.hpp>
#include <fcppt/assign/make_container.hpp>
#include <sge/renderer/occlusion_query/scoped.hpp>
#include <sge/renderer/occlusion_query/object.hpp>
#include <sge/renderer/occlusion_query/object_scoped_ptr.hpp>
#include <sge/font/text/align_v.hpp>
#include <sge/font/text/draw.hpp>
#include <sge/font/text/drawer_3d.hpp>
#include <sge/font/text/flags_none.hpp>
#include <sge/font/text/from_fcppt_string.hpp>
#include <sge/font/text/lit.hpp>
#include <sge/font/text/part.hpp>
#include <sge/font/text/string.hpp>
#include <sge/image/colors.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/model/manager/instance/object.hpp>
#include <sge/model/manager/object.hpp>
#include <sge/input/keyboard/key_code_to_digit.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/input/keyboard/optional_digit.hpp>
#include <sge/renderer/aspect.hpp>
#include <sge/renderer/bit_depth.hpp>
#include <sge/renderer/depth_stencil_buffer.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/matrix_mode.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/light/object.hpp>
#include <sge/renderer/light/variant.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/vsync.hpp>
#include <sge/renderer/windowed.hpp>
#include <sge/renderer/caps/device.hpp>
#include <sge/media/all_extensions.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/context/object.hpp>
#include <sge/renderer/context/scoped.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/fov.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/target/viewport_size.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <sge/systems/cursor_option.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/font.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/input_helper.hpp>
#include <sge/systems/input_helper_field.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/quit_on_escape.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/window.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/timer/basic.hpp>
#include <sge/timer/elapsed_and_reset.hpp>
#include <sge/timer/parameters.hpp>
#include <sge/timer/clocks/standard.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/viewport/manager.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/parameters.hpp>
#include <sge/window/system.hpp>
#include <sge/window/title.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context_fwd.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/insert_to_std_wstring.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/array.hpp>
#include <fcppt/container/bitfield/object_impl.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/math/deg_to_rad.hpp>
#include <fcppt/math/box/object_impl.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/object_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/math/pi.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <example_main.hpp>
#include <exception>
#include <iostream>
#include <ostream>
#include <utility>
#include <fcppt/config/external_end.hpp>


awl::main::exit_code const
example_main(
	awl::main::function_context const &
)
try
{
	sge::systems::instance const sys(
		sge::systems::list()
		(
			sge::systems::window(
				sge::window::parameters(
					sge::window::title(
						FCPPT_TEXT("sge occlusion query example")
					),
					sge::window::dim(
						1024,
						768
					)
				)
			)
		)
		(
			sge::systems::image2d(
				sge::image::capabilities_field::null(),
				sge::media::all_extensions
			)
		)
		(
			sge::systems::renderer(
				sge::renderer::parameters(
					sge::renderer::windowed(
						sge::renderer::bit_depth::depth32
					),
					sge::renderer::depth_stencil_buffer::d24s8,
					sge::renderer::vsync::on,
					sge::renderer::no_multi_sampling
				),
				sge::viewport::fill_on_resize()
			)
		)
		(
			sge::systems::input(
				sge::systems::input_helper_field(
					sge::systems::input_helper::keyboard_collector
				)
				| sge::systems::input_helper::mouse_collector,
				sge::systems::cursor_option_field(
					sge::systems::cursor_option::exclusive
				)
			)
		)
		(
			sge::systems::font()
		)
	);

	sge::camera::first_person::object camera(
		sge::camera::first_person::parameters(
			sys.keyboard_collector(),
			sys.mouse_collector(),
			sge::camera::first_person::is_active(
				true
			),
			sge::camera::first_person::movement_speed(
				15.0f
			),
			sge::camera::coordinate_system::identity()
		)
	);

	fcppt::signal::scoped_connection const input_connection(
		sge::systems::quit_on_escape(
			sys
		)
	);

	sge::camera::perspective_projection_from_viewport camera_viewport_connection(
		camera,
		sys.renderer(),
		sys.viewport_manager(),
		sge::renderer::projection::near(
			0.1f
		),
		sge::renderer::projection::far(
			1000.f
		),
		sge::renderer::projection::fov(
			fcppt::math::deg_to_rad(
				90.f
			)
		)
	);

	sge::font::metrics_scoped_ptr const font_metrics(
		sys.font_system().create_font(
			sge::config::media_path()
			/ FCPPT_TEXT("fonts")
			/ FCPPT_TEXT("default.ttf"),
			static_cast<
				sge::font::size_type
			>(
				30
			)
		)
	);

	sge::font::text::drawer_3d font_drawer(
		sys.renderer(),
		sge::image::colors::red(),
		sge::font::text::set_matrices(
			true)
	);

	sge::timer::basic<
		sge::timer::clocks::standard
	> frame_timer(
		sge::timer::parameters<
			sge::timer::clocks::standard
		>(
			sge::camera::update_duration(
				1.0f
			)
		)
	);

	sge::model::manager::object model_manager(
		sys.renderer(),
		sys.image_system(),
		camera,
		sge::model::manager::model_directory(
			sge::config::media_path() / FCPPT_TEXT("objs")),
		sge::model::manager::texture_directory(
			sge::config::media_path() / FCPPT_TEXT("model_textures")));

	sge::model::manager::instance::object const
		brick_wall(
			sge::model::manager::instance::object(
				sge::model::manager::instance::identifier(
					FCPPT_TEXT("brick_wall")),
				sge::model::manager::instance::position(
					sge::renderer::vector3::null()))),
		treasure_chest(
			sge::model::manager::instance::object(
				sge::model::manager::instance::identifier(
					FCPPT_TEXT("treasure_chest")),
				sge::model::manager::instance::position(
					sge::renderer::vector3(
						-12.0f,
						0.0f,
						0.0f))));

	sge::renderer::occlusion_query::object_scoped_ptr current_occlusion_query;
	sge::renderer::occlusion_query::optional_pixel_count last_query_result;

	while(
		sys.window_system().poll()
	)
	{
		camera.update(
			sge::timer::elapsed_and_reset<
				sge::camera::update_duration
			>(
				frame_timer
			)
		);

		sge::renderer::context::scoped const scoped_block(
			sys.renderer(),
			sys.renderer().onscreen_target()
		);


		sge::renderer::context::object &context(
			scoped_block.get());

		{
			sge::renderer::state::scoped scoped_state(
				context,
				sge::renderer::state::list
					(sge::renderer::state::bool_::enable_lighting = true));

			context.enable_light(
				sge::renderer::light::index(
					0u),
				true);

			{
				sge::renderer::scoped_transform scoped_transform(
					context,
					sge::renderer::matrix_mode::world,
					sge::camera::matrix_conversion::world(
						camera.coordinate_system()));

				context.light(
					sge::renderer::light::index(
						0u),
					sge::renderer::light::object(
						sge::renderer::diffuse_color(
							sge::image::colors::white()),
						sge::renderer::specular_color(
							sge::image::colors::white()),
						sge::renderer::ambient_color(
							sge::image::colors::white()),
						sge::renderer::light::variant(
							sge::renderer::light::directional(
								sge::renderer::light::direction(
									sge::renderer::vector3(
										-0.780869f,
										-0.624659f,
										0.0f)),
								sge::renderer::light::cutoff_angle(
									fcppt::math::pi<sge::renderer::scalar>())))));
			}

			context.clear(
				sge::renderer::clear::parameters()
				.back_buffer(
					sge::image::colors::black()
				)
				.depth_buffer(
					1.f)
			);

			model_manager.render(
				context,
				fcppt::assign::make_container<sge::model::manager::instance::sequence>
					(brick_wall));

			sge::renderer::occlusion_query::optional_pixel_count const current_result(
				current_occlusion_query
				?
					current_occlusion_query->result(
						sge::renderer::occlusion_query::blocking_wait(
							false))
				:
					sge::renderer::occlusion_query::optional_pixel_count());

			if(current_result)
				last_query_result =
					current_result;

			if(!current_occlusion_query || current_result)
			{
				current_occlusion_query.take(
					sys.renderer().create_occlusion_query());

				sge::renderer::occlusion_query::scoped scoped_query(
					*current_occlusion_query);

				model_manager.render(
					context,
					fcppt::assign::make_container<sge::model::manager::instance::sequence>
						(treasure_chest));
			}
			else
			{
				model_manager.render(
					context,
					fcppt::assign::make_container<sge::model::manager::instance::sequence>
						(treasure_chest));
			}
		}

		sge::font::rect const font_rect(
			sge::font::rect::vector::null(),
			fcppt::math::dim::structure_cast<
				sge::font::rect::dim
			>(
				sge::renderer::target::viewport_size(
					context.target()
				)
			)
		);

		sge::font::text::draw(
			scoped_block.get(),
			*font_metrics,
			font_drawer,
			SGE_FONT_TEXT_LIT("last query result: ")+
			(last_query_result
			 ?
				fcppt::insert_to_std_wstring(
					last_query_result->get())
			 :
				sge::font::text::string()),
			font_rect,
			sge::font::text::align_h::left,
			sge::font::text::align_v::top,
			sge::font::text::flags::none
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

	return awl::main::exit_failure();
}
catch(
	std::exception const &_error
)
{
	std::cerr
		<< _error.what()
		<< '\n';

	return awl::main::exit_failure();
}
