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
#include <sge/camera/first_person/object.hpp>
#include <sge/camera/first_person/parameters.hpp>
#include <sge/camera/matrix_conversion/world.hpp>
#include <sge/config/media_path.hpp>
#include <sge/image/colors.hpp>
#include <sge/media/all_extensions.hpp>
#include <sge/model/manager/object.hpp>
#include <sge/model/manager/instance/object.hpp>
#include <sge/renderer/aspect.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/matrix_mode.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/scoped_transform.hpp>
#include <sge/renderer/caps/device.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/context/object.hpp>
#include <sge/renderer/context/scoped.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/light/attenuation.hpp>
#include <sge/renderer/light/object.hpp>
#include <sge/renderer/light/point.hpp>
#include <sge/renderer/parameters/object.hpp>
#include <sge/renderer/parameters/vsync.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/fov.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/scoped.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/target/viewport_size.hpp>
#include <sge/systems/cursor_option.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/input_helper.hpp>
#include <sge/systems/input_helper_field.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/quit_on_escape.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/window.hpp>
#include <sge/timer/basic.hpp>
#include <sge/timer/elapsed_and_reset.hpp>
#include <sge/timer/elapsed_fractional_and_reset.hpp>
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
#include <fcppt/insert_to_string.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/array.hpp>
#include <fcppt/container/bitfield/object_impl.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/math/deg_to_rad.hpp>
#include <fcppt/math/pi.hpp>
#include <fcppt/math/twopi.hpp>
#include <fcppt/math/box/object_impl.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/object_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <cmath>
#include <example_main.hpp>
#include <exception>
#include <iostream>
#include <ostream>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace
{
class rotating_light
{
FCPPT_NONCOPYABLE(
	rotating_light);
public:
	rotating_light()
	:
		radius_(
			15.0f),
		current_angle_(
			0.0f),
		timer_(
			sge::timer::parameters<sge::timer::clocks::standard>(
				sge::camera::update_duration(
					1.0f)))
	{
	}

	void
	update()
	{
		current_angle_ +=
			sge::timer::elapsed_fractional_and_reset<sge::renderer::scalar>(
				timer_);

	}

	sge::renderer::light::object const
	object() const
	{
		return
			sge::renderer::light::object(
				sge::renderer::diffuse_color(
					sge::image::colors::red()),
				sge::renderer::specular_color(
					sge::image::colors::white()),
				sge::renderer::ambient_color(
					sge::image::colors::white()),
				sge::renderer::light::variant(
					sge::renderer::light::point(
						sge::renderer::light::position(
							this->position()),
						sge::renderer::light::attenuation(
							sge::renderer::light::constant_attenuation(
								0.0f),
							sge::renderer::light::linear_attenuation(
								0.1f),
							sge::renderer::light::quadratic_attenuation(
								0.0f)))));
	}

	sge::model::manager::instance::object const
	model() const
	{
		return
			sge::model::manager::instance::object(
				sge::model::manager::instance::identifier(
					FCPPT_TEXT("bulb")),
				sge::model::manager::instance::position(
					this->position()));
	}

	sge::renderer::vector3 const
	position() const
	{
		return
			radius_ *
			sge::renderer::vector3(
				std::sin(
					current_angle_),
				0.5f,
				std::cos(
					current_angle_));
	}

	~rotating_light()
	{
	}
private:
	sge::renderer::scalar const radius_;
	sge::renderer::scalar current_angle_;
	sge::timer::basic<sge::timer::clocks::standard> timer_;
};
}

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
						FCPPT_TEXT("sge model loader example")
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
				sge::renderer::parameters::object(
					sge::renderer::pixel_format::object(
						sge::renderer::pixel_format::color::depth32,
						sge::renderer::pixel_format::depth_stencil::d24s8,
						sge::renderer::pixel_format::optional_multi_samples(),
						sge::renderer::pixel_format::srgb::yes
					),
					sge::renderer::parameters::vsync::on,
					sge::renderer::display_mode::optional_object()
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
	);

	sge::camera::first_person::object camera(
		sge::camera::first_person::parameters(
			sys.keyboard_collector(),
			sys.mouse_collector(),
			sge::camera::first_person::is_active(
				true
			),
			sge::camera::first_person::movement_speed(
				8.0f
			),
			sge::camera::coordinate_system::object(
				sge::camera::coordinate_system::right(
					sge::renderer::vector3(
						-0.664409f,
						4.47035e-08f,
						0.747369f
					)
				),
				sge::camera::coordinate_system::up(
					sge::renderer::vector3(
						-0.348429f,
						0.884676f,
						-0.309752f)),
				sge::camera::coordinate_system::forward(
					sge::renderer::vector3(
						-0.661179f,
						-0.466207f,
						-0.587787f
					)
				),
				sge::camera::coordinate_system::position(
					sge::renderer::vector3(
						-17.9035f,
						-14.1667f,
						-14.7512f
					)
				)
			)
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
				60.f
			)
		)
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

	sge::model::manager::instance::sequence model_list;
	model_list.push_back(
		sge::model::manager::instance::object(
			sge::model::manager::instance::identifier(
				FCPPT_TEXT("treasure_chest")),
			sge::model::manager::instance::position(
				sge::renderer::vector3::null())));

	rotating_light light;

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

		light.update();

		sge::renderer::context::scoped const scoped_block(
			sys.renderer(),
			sys.renderer().onscreen_target()
		);


		sge::renderer::context::object &context(
			scoped_block.get());

		context.clear(
			sge::renderer::clear::parameters()
			.back_buffer(
				sge::image::colors::black()
			)
			.depth_buffer(
				1.f)
		);

		{
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
					light.object());
			}

			sge::renderer::state::scoped scoped_state(
				context,
				sge::renderer::state::list
					(sge::renderer::state::bool_::enable_lighting = true));

			model_manager.render(
				context,
				model_list);
		}

		model_manager.render(
			context,
			fcppt::assign::make_container<sge::model::manager::instance::sequence>
				(light.model()));
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
