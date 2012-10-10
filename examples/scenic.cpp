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


#include <sge/camera/coordinate_system/identity.hpp>
#include <sge/camera/first_person/object.hpp>
#include <sge/camera/first_person/parameters.hpp>
#include <sge/config/media_path.hpp>
#include <sge/graph/color_schemes.hpp>
#include <sge/graph/object.hpp>
#include <sge/image/capabilities_field.hpp>
#include <sge/image/colors.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/context/scoped_ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/parameters/object.hpp>
#include <sge/renderer/parameters/vsync.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/scenic/grid/object.hpp>
#include <sge/scenic/render_context/base.hpp>
#include <sge/scenic/scene/from_blender_file.hpp>
#include <sge/scenic/scene/manager.hpp>
#include <sge/scenic/scene/object.hpp>
#include <sge/scenic/scene/prototype.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/image2d.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/keyboard_collector.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/mouse_collector.hpp>
#include <sge/systems/quit_on_escape.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/renderer_caps.hpp>
#include <sge/systems/window.hpp>
#include <sge/systems/with_charconv.hpp>
#include <sge/systems/with_image2d.hpp>
#include <sge/systems/with_input.hpp>
#include <sge/systems/with_renderer.hpp>
#include <sge/systems/with_window.hpp>
#include <sge/timer/basic.hpp>
#include <sge/timer/elapsed_and_reset.hpp>
#include <sge/timer/parameters.hpp>
#include <sge/timer/clocks/standard.hpp>
#include <sge/viewport/center_on_resize.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/parameters.hpp>
#include <sge/window/system.hpp>
#include <sge/window/title.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/exit_success.hpp>
#include <awl/main/function_context.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/bitfield/object_impl.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/math/dim/object_impl.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/program_options.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <example_main.hpp>
#include <exception>
#include <iostream>
#include <ostream>
#include <fcppt/config/external_end.hpp>


awl::main::exit_code const
example_main(
	awl::main::function_context const &_context
)
try
{
	std::string scene_name_narrow;

	boost::program_options::options_description allowed_options_description("Allowed options");
	allowed_options_description.add_options()
		(
			"help",
			"produce help message")
		(
			"scene-name",
			boost::program_options::value<std::string>(&scene_name_narrow)->required(),
			"Scene name (denotes a path below media/scenes)")
		(
			"ffp",
			"Use an ffp context instead of a shader context");

	boost::program_options::variables_map compiled_options;
	boost::program_options::store(
		boost::program_options::parse_command_line(
			_context.argc(),
			_context.argv(),
			allowed_options_description),
		compiled_options);

	if(compiled_options.count("help"))
	{
		std::cout << allowed_options_description << "\n";
		return
			awl::main::exit_success();
	}

	boost::program_options::notify(
		compiled_options);


	fcppt::string const scene_name(
		fcppt::from_std_string(
			scene_name_narrow));

	sge::window::dim const window_dim(
		1024,
		768);

	sge::systems::instance<
		boost::mpl::vector5<
			sge::systems::with_window,
			sge::systems::with_renderer<
				sge::systems::renderer_caps::ffp
			>,
			sge::systems::with_input<
				boost::mpl::vector2<
					sge::systems::keyboard_collector,
					sge::systems::mouse_collector
				>
			>,
			sge::systems::with_charconv,
			sge::systems::with_image2d
		>
	> const sys(
		sge::systems::make_list
			(sge::systems::window(
				sge::window::parameters(
					sge::window::title(
						FCPPT_TEXT("sge scenic example")),
					window_dim)))
			(sge::systems::renderer(
				sge::renderer::parameters::object(
					sge::renderer::pixel_format::object(
						sge::renderer::pixel_format::color::depth32,
						sge::renderer::pixel_format::depth_stencil::d24s8,
						sge::renderer::pixel_format::optional_multi_samples(),
						sge::renderer::pixel_format::srgb::yes
					),
					sge::renderer::parameters::vsync::on,
					sge::renderer::display_mode::optional_object()),
				sge::viewport::center_on_resize(
					window_dim)))
			(sge::systems::input(
				sge::systems::cursor_option_field(
					sge::systems::cursor_option::exclusive)))
			(sge::systems::image2d(
				sge::image::capabilities_field::null(),
				sge::media::optional_extension_set(
					fcppt::assign::make_container<sge::media::extension_set>(
						sge::media::extension(
							FCPPT_TEXT("png")))))));

	fcppt::signal::scoped_connection const escape_connection(
		sge::systems::quit_on_escape(
			sys));

	sge::camera::first_person::object camera(
		sge::camera::first_person::parameters(
			sys.keyboard_collector(),
			sys.mouse_collector(),
			sge::camera::first_person::is_active(
				true),
			sge::camera::first_person::movement_speed(
				4.0f),
			sge::camera::coordinate_system::identity()));

	sge::scenic::scene::manager scene_manager(
		sys.renderer_core(),
		sys.image_system(),
		sge::scenic::scene::prefer_cg_context(
			!compiled_options.count(
				"ffp")));

	sge::scenic::scene::object test_scene(
		scene_manager,
		sys.viewport_manager(),
		sys.charconv_system(),
		camera,
		sge::scenic::scene::from_blender_file(
			sge::config::media_path() / FCPPT_TEXT("scenes") / scene_name / FCPPT_TEXT("description.json"),
			sys.charconv_system()));

	sge::timer::basic<sge::timer::clocks::standard> camera_timer(
		sge::timer::parameters<sge::timer::clocks::standard>(
			sge::camera::update_duration(
				1.0f)));

	sge::scenic::grid::object simple_grid_xz(
		sys.renderer_ffp(),
		camera,
		sge::scenic::grid::orientation::xz,
		sge::scenic::grid::rect(
			sge::scenic::grid::rect::vector(
				-10.0f,
				-10.0f),
			sge::scenic::grid::rect::dim(
				20.0f,
				20.0f)),
			sge::scenic::grid::spacing(
				sge::scenic::grid::dim(
					1.0f,
					1.0f)),
		sge::scenic::grid::distance_to_origin(
			0.0f),
		sge::image::colors::white());

	/*
	sge::scenic::sky::dome::object skydome(
		sys.renderer_core(),
		scene_manager.shader_context(),
		scene_manager.texture_manager(),
		sge::scenic::sky::dome::texture_path(
			sge::config::media_path() / FCPPT_TEXT("scenes") / scene_name / FCPPT_TEXT("sky.png")),
		camera,
		sge::scenic::sky::dome::longitude(
			30u),
		sge::scenic::sky::dome::latitude(
			30u),
		sge::scenic::sky::dome::y_translation(
			0.0f));
	*/

	sge::graph::object graph(
		sge::graph::position(
			sge::renderer::vector2(
				0.0f,
				0.0f)),
		sge::renderer::dim2(
			256u,
			64u),
		sys.renderer_ffp(),
		sge::graph::baseline(
			1.0f/30.0f),
		sge::graph::optional_axis_constraint(
			sge::graph::axis_constraint(
				0.0f,
				0.1f)),
		sge::graph::color_schemes::default_()
	);

	while(
		sys.window_system().poll())
	{
		sge::camera::update_duration const difference_since_last_frame(
			sge::timer::elapsed_and_reset<sge::camera::update_duration>(
				camera_timer));

		camera.update(
			difference_since_last_frame);

		graph.push(
			difference_since_last_frame.count());

		sge::renderer::context::scoped_ffp const scoped_block(
			sys.renderer_ffp(),
			sys.renderer_ffp().onscreen_target());

		scoped_block.get().clear(
			sge::renderer::clear::parameters()
				.back_buffer(
					sge::image::colors::black())
				.depth_buffer(
					1.0f));

		/*
		skydome.render(
			scoped_block.get());
		*/

		{
			sge::scenic::render_context::base_unique_ptr wrapped_context(
				scene_manager.create_render_context(
					scoped_block.get()));

			test_scene.render(
				*wrapped_context);
		}

		simple_grid_xz.render(
			scoped_block.get(),
			sge::scenic::grid::depth_test(
				true));

		graph.render(
			scoped_block.get());
	}

	return
		sys.window_system().exit_code();
}
catch(
	fcppt::exception const &_error)
{
	fcppt::io::cerr()
		<< _error.string()
		<< FCPPT_TEXT('\n');

	return
		awl::main::exit_failure();
}
catch(
	std::exception const &_error)
{
	std::cerr
		<< _error.what()
		<< '\n';

	return
		awl::main::exit_failure();
}
