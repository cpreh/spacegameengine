/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/config/media_path.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/file_unique_ptr.hpp>
#include <sge/image2d/load_exn.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/vector2.hpp>
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
#include <sge/renderer/state/ffp/lighting/ambient_color.hpp>
#include <sge/renderer/state/ffp/lighting/diffuse_color.hpp>
#include <sge/renderer/state/ffp/lighting/diffuse_from_vertex.hpp>
#include <sge/renderer/state/ffp/lighting/enabled.hpp>
#include <sge/renderer/state/ffp/lighting/object.hpp>
#include <sge/renderer/state/ffp/lighting/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/lighting/parameters.hpp>
#include <sge/renderer/state/ffp/lighting/scoped.hpp>
#include <sge/renderer/state/ffp/lighting/specular_color.hpp>
#include <sge/renderer/state/ffp/lighting/variant.hpp>
#include <sge/renderer/state/ffp/lighting/light/attenuation.hpp>
#include <sge/renderer/state/ffp/lighting/light/const_object_ref_vector.hpp>
#include <sge/renderer/state/ffp/lighting/light/constant_attenuation.hpp>
#include <sge/renderer/state/ffp/lighting/light/linear_attenuation.hpp>
#include <sge/renderer/state/ffp/lighting/light/object.hpp>
#include <sge/renderer/state/ffp/lighting/light/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/lighting/light/parameters.hpp>
#include <sge/renderer/state/ffp/lighting/light/point.hpp>
#include <sge/renderer/state/ffp/lighting/light/position.hpp>
#include <sge/renderer/state/ffp/lighting/light/quadratic_attenuation.hpp>
#include <sge/renderer/state/ffp/lighting/light/scoped.hpp>
#include <sge/renderer/state/ffp/lighting/light/variant.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/texture/create_planar_from_view.hpp>
#include <sge/renderer/texture/emulate_srgb_from_caps.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/planar_unique_ptr.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/single.hpp>
#include <sge/sprite/buffers/with_declaration.hpp>
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
#include <sge/sprite/process/one.hpp>
#include <sge/sprite/roles/pos.hpp>
#include <sge/sprite/roles/texture0.hpp>
#include <sge/sprite/state/all_choices.hpp>
#include <sge/sprite/state/object.hpp>
#include <sge/sprite/state/parameters.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/image2d.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/keyboard_collector.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/original_window.hpp>
#include <sge/systems/quit_on_escape.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/renderer_caps.hpp>
#include <sge/systems/window.hpp>
#include <sge/systems/window_source.hpp>
#include <sge/systems/with_image2d.hpp>
#include <sge/systems/with_input.hpp>
#include <sge/systems/with_renderer.hpp>
#include <sge/systems/with_window.hpp>
#include <sge/texture/part_raw_ref.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/viewport/optional_resize_callback.hpp>
#include <sge/window/system.hpp>
#include <sge/window/title.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context_fwd.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/int_to_float_fun.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/math/vector/construct.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <example_main.hpp>
#include <exception>
#include <iostream>
#include <ostream>
#include <fcppt/config/external_end.hpp>


awl::main::exit_code const
example_main(
	awl::main::function_context const &
)
try
{
	sge::systems::instance<
		boost::mpl::vector4<
			sge::systems::with_renderer<
				sge::systems::renderer_caps::ffp
			>,
			sge::systems::with_window,
			sge::systems::with_input<
				boost::mpl::vector1<
					sge::systems::keyboard_collector
				>
			>,
			sge::systems::with_image2d
		>
	> const sys(
		sge::systems::make_list
		(
			sge::systems::window(
				sge::systems::window_source(
					sge::systems::original_window(
						sge::window::title(
							FCPPT_TEXT("sge lighting example")
						)
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
			sge::systems::image2d(
				sge::media::optional_extension_set(
					sge::media::extension_set{
						sge::media::extension(
							FCPPT_TEXT("png")
						)
					}
				)
			)
		)
		(
			sge::systems::input(
				sge::systems::cursor_option_field::null()
			)
		)
	);

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
		sge::sprite::config::pos<
			sge::sprite::config::pos_option::pos
		>,
		sge::sprite::config::normal_size<
			sge::sprite::config::texture_size_option::always
		>,
		boost::mpl::vector1<
			sge::sprite::config::with_texture<
				sge::sprite::config::texture_level_count<
					1u
				>,
				sge::sprite::config::texture_coordinates::automatic,
				sge::sprite::config::texture_ownership::reference
			>
		>
	>
	sprite_choices;

	typedef
	sge::sprite::object<
		sprite_choices
	>
	sprite_object;

	typedef
	sge::sprite::buffers::with_declaration<
		sge::sprite::buffers::single<
			sprite_choices
		>
	>
	sprite_buffers_type;

	sprite_buffers_type sprite_buffers(
		sys.renderer_device_ffp(),
		sge::sprite::buffers::option::dynamic
	);

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

	sge::image2d::file_unique_ptr const image(
		sge::image2d::load_exn(
			sys.image_system(),
			sge::config::media_path()
			/ FCPPT_TEXT("images")
			/ FCPPT_TEXT("grass.png")
		)
	);

	sge::renderer::texture::planar_unique_ptr const image_texture(
		sge::renderer::texture::create_planar_from_view(
			sys.renderer_device_ffp(),
			image->view(),
			sge::renderer::texture::mipmap::off(),
			sge::renderer::resource_flags_field::null(),
			sge::renderer::texture::emulate_srgb_from_caps(
				sys.renderer_device_ffp().caps()
			)
		)
	);

	sge::texture::part_raw_ref const texture_part(
		*image_texture
	);

	sprite_object const my_object(
		sge::sprite::roles::pos{} =
			fcppt::math::vector::null<
				sprite_object::vector
			>(),
		sge::sprite::roles::texture0{} =
			sprite_object::texture_type{
				texture_part
			}
	);

	fcppt::signal::auto_connection const escape_connection{
		sge::systems::quit_on_escape(
			sys
		)
	};

	sge::renderer::state::ffp::lighting::object_unique_ptr const light_state{
		sys.renderer_device_ffp().create_lighting_state(
			sge::renderer::state::ffp::lighting::parameters{
				sge::renderer::state::ffp::lighting::variant{
					sge::renderer::state::ffp::lighting::enabled{
						sge::renderer::state::ffp::lighting::ambient_color{
							sge::image::color::predef::black()
						},
						sge::renderer::state::ffp::lighting::diffuse_from_vertex{
							false
						}
					}
				}
			}
		)
	};

	sge::renderer::state::ffp::lighting::light::object_unique_ptr const light{
		sys.renderer_device_ffp().create_light_state(
			sge::renderer::state::ffp::lighting::light::parameters{
				sge::renderer::state::ffp::lighting::diffuse_color{
					sge::image::color::predef::black()
				},
				sge::renderer::state::ffp::lighting::specular_color{
					sge::image::color::predef::black()
				},
				sge::renderer::state::ffp::lighting::ambient_color{
					sge::image::color::predef::yellow()
				},
				sge::renderer::state::ffp::lighting::light::variant{
					sge::renderer::state::ffp::lighting::light::point{
						sge::renderer::state::ffp::lighting::light::position{
							fcppt::math::vector::construct(
								fcppt::math::vector::structure_cast<
									sge::renderer::vector2,
									fcppt::cast::int_to_float_fun
								>(
									my_object.center()
								),
								-1.f
							)
						},
						sge::renderer::state::ffp::lighting::light::attenuation{
							sge::renderer::state::ffp::lighting::light::constant_attenuation{
								1.f
							},
							sge::renderer::state::ffp::lighting::light::linear_attenuation{
								0.f
							},
							sge::renderer::state::ffp::lighting::light::quadratic_attenuation{
								0.f
							}
						}
					}
				}
			}
		)
	};

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

		sge::renderer::state::ffp::lighting::scoped const scoped_lighting{
			scoped_block.get(),
			*light_state
		};

		sge::renderer::state::ffp::lighting::light::scoped const scoped_lights{
			scoped_block.get(),
			sge::renderer::state::ffp::lighting::light::const_object_ref_vector{
				fcppt::make_cref(
					*light
				)
			}
		};

		sge::sprite::process::one(
			scoped_block.get(),
			my_object,
			sprite_buffers,
			sprite_state
		);
	}

	return
		sys.window_system().exit_code();
}
catch(
	fcppt::exception const &_exception
)
{
	fcppt::io::cerr()
		<< FCPPT_TEXT("caught sge exception: ")
		<< _exception.string()
		<< FCPPT_TEXT('\n');

	return
		awl::main::exit_failure();
}
catch(
	std::exception const &_exception
)
{
	std::cerr
		<< "caught std exception: "
		<< _exception.what()
		<< '\n';

	return
		awl::main::exit_failure();
}
