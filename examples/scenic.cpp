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


#include <sge/camera/base.hpp>
#include <sge/camera/coordinate_system/identity.hpp>
#include <sge/camera/first_person/object.hpp>
#include <sge/camera/first_person/parameters.hpp>
#include <sge/camera/matrix_conversion/world.hpp>
#include <sge/camera/tracking/object.hpp>
#include <sge/camera/tracking/json/interval_exporter.hpp>
#include <sge/camera/tracking/json/key_press_exporter.hpp>
#include <sge/camera/tracking/json/keyframes_from_json.hpp>
#include <sge/config/media_path.hpp>
#include <sge/graph/color_schemes.hpp>
#include <sge/graph/object.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/parse/json/parse_file_exn.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/context/scoped_ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/display_mode/parameters.hpp>
#include <sge/renderer/display_mode/vsync.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/scenic/grid/object.hpp>
#include <sge/scenic/grid/orientation.hpp>
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
#include <sge/timer/basic.hpp>
#include <sge/timer/elapsed_and_reset.hpp>
#include <sge/timer/parameters.hpp>
#include <sge/timer/clocks/standard.hpp>
#include <sge/viewport/center_on_resize.hpp>
#include <sge/viewport/optional_resize_callback.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/system.hpp>
#include <sge/window/title.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/exit_success.hpp>
#include <awl/main/function_context.hpp>
#include <fcppt/args_from_second.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/string.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/either/match.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/math/matrix/output.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/optional/make.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/options/apply.hpp>
#include <fcppt/options/argument.hpp>
#include <fcppt/options/default_help_switch.hpp>
#include <fcppt/options/error.hpp>
#include <fcppt/options/help_text.hpp>
#include <fcppt/options/long_name.hpp>
#include <fcppt/options/make_default_value.hpp>
#include <fcppt/options/make_optional.hpp>
#include <fcppt/options/no_default_value.hpp>
#include <fcppt/options/option.hpp>
#include <fcppt/options/optional_help_text.hpp>
#include <fcppt/options/optional_short_name.hpp>
#include <fcppt/options/parse_help.hpp>
#include <fcppt/options/result.hpp>
#include <fcppt/options/result_of.hpp>
#include <fcppt/options/switch.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/record/make_label.hpp>
#include <fcppt/record/permute.hpp>
#include <fcppt/record/variadic.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/variant/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <chrono>
#include <example_main.hpp>
#include <exception>
#include <iostream>
#include <ostream>
#include <string>
#include <fcppt/config/external_end.hpp>


namespace
{

FCPPT_RECORD_MAKE_LABEL(
	record_to_file_label
);

FCPPT_RECORD_MAKE_LABEL(
	track_from_file_label
);

FCPPT_RECORD_MAKE_LABEL(
	recording_interval_label
);

FCPPT_RECORD_MAKE_LABEL(
	ffp_label
);

FCPPT_RECORD_MAKE_LABEL(
	scene_name_label
);

typedef
fcppt::record::variadic<
	fcppt::record::element<
		record_to_file_label,
		fcppt::optional::object<
			fcppt::string
		>
	>,
	fcppt::record::element<
		track_from_file_label,
		fcppt::optional::object<
			fcppt::string
		>
	>,
	fcppt::record::element<
		recording_interval_label,
		sge::camera::update_duration::rep
	>,
	fcppt::record::element<
		ffp_label,
		bool
	>,
	fcppt::record::element<
		scene_name_label,
		fcppt::string
	>
>
options_record;

awl::main::exit_code
main_program(
	options_record const &_options
)
{
	if(
		fcppt::record::get<
			record_to_file_label
		>(
			_options
		).has_value()
		&&
		fcppt::record::get<
			track_from_file_label
		>(
			_options
		).has_value()
	)
	{
		fcppt::io::cerr() <<
			FCPPT_TEXT("You specified to record a file and use the tracking camera, that doesn't make sense.\n");
		return
			awl::main::exit_failure();
	}

	sge::window::dim const window_dim(
		1024u,
		768u
	);

	sge::systems::instance<
		boost::mpl::vector4<
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
			sge::systems::with_image2d
		>
	> const sys(
		sge::systems::make_list(
			sge::systems::window{
				sge::systems::window_source{
					sge::systems::original_window{
						sge::window::title{
							FCPPT_TEXT("sge scenic example")
						}
					}
				}
			}
		)(
			sge::systems::renderer{
				sge::renderer::pixel_format::object{
					sge::renderer::pixel_format::color::depth32,
					sge::renderer::pixel_format::depth_stencil::d24s8,
					sge::renderer::pixel_format::optional_multi_samples(),
					sge::renderer::pixel_format::srgb::no
				},
				sge::renderer::display_mode::parameters{
					sge::renderer::display_mode::vsync::on,
					sge::renderer::display_mode::optional_object()
				},
				sge::viewport::optional_resize_callback{
					sge::viewport::center_on_resize(
						window_dim
					)
				}
			}
		)(
			sge::systems::input{
				sge::systems::cursor_option_field{
					sge::systems::cursor_option::exclusive
				}
			}
		)(
			sge::systems::image2d{
				sge::media::optional_extension_set{
					sge::media::extension_set{
						sge::media::extension{
							FCPPT_TEXT("png")
						}
					}
				}
			}
		)
	);

	fcppt::signal::auto_connection const escape_connection(
		sge::systems::quit_on_escape(
			sys
		)
	);

	fcppt::unique_ptr<
		sge::camera::base
	> const camera(
		fcppt::optional::maybe(
			fcppt::record::get<
				track_from_file_label
			>(
				_options
			),
			[
				&sys
			]{
				return
					fcppt::unique_ptr_to_base<
						sge::camera::base
					>(
						fcppt::make_unique_ptr<
							sge::camera::first_person::object
						>(
							sge::camera::first_person::parameters(
								sys.keyboard_collector(),
								sys.mouse_collector(),
								sge::camera::is_active(
									true
								),
								sge::camera::first_person::movement_speed(
									4.0f
								),
								sge::camera::coordinate_system::identity()
							)
						)
					);
			},
			[](
				fcppt::string const &_track_from_file
			)
			{
				return
					fcppt::unique_ptr_to_base<
						sge::camera::base
					>(
						fcppt::make_unique_ptr<
							sge::camera::tracking::object
						>(
							sge::camera::optional_projection_matrix(),
							sge::camera::tracking::json::keyframes_from_json(
								sge::parse::json::parse_file_exn(
									boost::filesystem::path(
										_track_from_file
									)
								).array()
							),
							sge::camera::tracking::is_looping(
								true
							),
							sge::camera::is_active(
								true
							)
						)
					);
			}
		)
	);

	typedef
	fcppt::unique_ptr<
		sge::camera::tracking::json::interval_exporter
	>
	exporter_unique_ptr;

	typedef
	fcppt::optional::object<
		exporter_unique_ptr
	>
	optional_exporter_unique_ptr;

	optional_exporter_unique_ptr const exporter(
		fcppt::optional::map(
			fcppt::record::get<
				record_to_file_label
			>(
				_options
			),
			[
				&_options,
				&camera
			](
				fcppt::string const &_record_to_file
			)
			{
				return
					fcppt::make_unique_ptr<
						sge::camera::tracking::json::interval_exporter
					>(
						*camera,
						sge::camera::update_duration{
							fcppt::record::get<
								recording_interval_label
							>(
								_options
							)
						},
						boost::filesystem::path(
							_record_to_file
						)
					);
			}
		)
	);

	sge::scenic::scene::manager scene_manager(
		sys.renderer_device_core(),
		sys.image_system(),
		sge::scenic::scene::prefer_cg_context(
			!fcppt::record::get<
				ffp_label
			>(
				_options
			)
		)
	);

	sge::scenic::scene::object test_scene(
		sys.log_context(),
		scene_manager,
		sys.viewport_manager(),
		*camera,
		sge::scenic::scene::from_blender_file(
			sge::config::media_path()
			/
			FCPPT_TEXT("scenes")
			/
			fcppt::record::get<
				scene_name_label
			>(
				_options
			)
			/
			FCPPT_TEXT("description.json")
		)
	);

	sge::timer::basic<
		sge::timer::clocks::standard
	> camera_timer(
		sge::timer::parameters<
			sge::timer::clocks::standard
		>(
			std::chrono::seconds(
				1
			)
		)
	);

	sge::scenic::grid::object simple_grid_xz{
		sys.renderer_device_ffp(),
		*camera,
		sge::scenic::grid::orientation::xz,
		sge::scenic::grid::rect{
			sge::scenic::grid::rect::vector{
				-10.0f,
				-10.0f
			},
			sge::scenic::grid::rect::dim{
				20.0f,
				20.0f
			}
		},
		sge::scenic::grid::spacing{
			sge::scenic::grid::dim{
				1.0f,
				1.0f
			}
		},
		sge::scenic::grid::distance_to_origin{
			0.0f
		},
		sge::image::color::predef::white()
	};

	/*
	sge::scenic::sky::dome::object skydome(
		sys.renderer_device_core(),
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

	sge::graph::object graph{
		sge::graph::position{
			sge::renderer::vector2{
				0.0f,
				0.0f
			}
		},
		sge::renderer::dim2{
			256u,
			64u
		},
		sys.renderer_device_ffp(),
		sge::graph::baseline{
			1.0f
			/
			30.0f
		},
		sge::graph::optional_axis_constraint{
			sge::graph::axis_constraint{
				0.0f,
				0.1f
			}
		},
		sge::graph::color_schemes::default_()
	};

	/*
	camera.update_coordinate_system(
		sge::camera::coordinate_system::identity());
	*/

	while(
		sys.window_system().poll())
	{
		sge::camera::update_duration const difference_since_last_frame(
			std::chrono::duration_cast<
				sge::camera::update_duration
			>(
				sge::timer::elapsed_and_reset(
					camera_timer
				)
			)
		);

		dynamic_cast<
			sge::camera::is_dynamic &
		>(
			*camera
		).update(
			difference_since_last_frame
		);

		graph.push(
			difference_since_last_frame.count()
		);

		fcppt::optional::maybe_void(
			exporter,
			[](
				exporter_unique_ptr const &_exporter
			)
			{
				_exporter->update();
			}
		);

		sge::renderer::context::scoped_ffp const scoped_block{
			sys.renderer_device_ffp(),
			sys.renderer_device_ffp().onscreen_target()
		};

		scoped_block.get().clear(
			sge::renderer::clear::parameters()
				.back_buffer(
					sge::image::color::predef::black()
				)
				.depth_buffer(
					1.0f
				)
		);

		/*
		skydome.render(
			scoped_block.get());
		*/

		{
			sge::scenic::render_context::base_unique_ptr const wrapped_context{
				scene_manager.create_render_context(
					scoped_block.get()
				)
			};

			test_scene.render(
				*wrapped_context
			);
		}

		simple_grid_xz.render(
			scoped_block.get(),
			sge::scenic::grid::depth_test{
				true
			}
		);

		graph.render(
			scoped_block.get()
		);
	}

	return
		sys.window_system().exit_code();
}

}

awl::main::exit_code const
example_main(
	awl::main::function_context const &_function_context
)
try
{
	auto const argument_parser{
		fcppt::options::apply(
			fcppt::options::make_optional(
				fcppt::options::option<
					record_to_file_label,
					fcppt::string
				>{
					fcppt::options::optional_short_name{},
					fcppt::options::long_name{
						FCPPT_TEXT("record-to-file")
					},
					fcppt::options::no_default_value<
						fcppt::string
					>(),
					fcppt::options::optional_help_text{
						fcppt::options::help_text{
							FCPPT_TEXT("Use a first-person camera and record the keyframes to this file (use recording-interval to control the keyframe interval)")
						}
					}
				}
			),
			fcppt::options::option<
				recording_interval_label,
				sge::camera::update_duration::rep
			>{
				fcppt::options::optional_short_name{},
				fcppt::options::long_name{
					FCPPT_TEXT("recording-interval")
				},
				fcppt::options::make_default_value(
					fcppt::optional::make(
						sge::camera::update_duration::rep{
							fcppt::literal<
								sge::renderer::scalar
							>(
								0.25f
							)
						}
					)
				),
				fcppt::options::optional_help_text{
					fcppt::options::help_text{
						FCPPT_TEXT("Take a keyframe each recording-interval seconds (only makes sense together with record-to-file)")
					}
				}
			},
			fcppt::options::make_optional(
				fcppt::options::option<
					track_from_file_label,
					fcppt::string
				>{
					fcppt::options::optional_short_name{},
					fcppt::options::long_name{
						FCPPT_TEXT("track-from-file")
					},
					fcppt::options::no_default_value<
						fcppt::string
					>(),
					fcppt::options::optional_help_text{
						fcppt::options::help_text{
							FCPPT_TEXT("Use a tracking camera and load keyframes from this file")
						}
					}
				}
			),
			fcppt::options::switch_<
				ffp_label
			>{
				fcppt::options::optional_short_name{},
				fcppt::options::long_name{
					FCPPT_TEXT("ffp")
				},
				fcppt::options::optional_help_text{
					fcppt::options::help_text{
						FCPPT_TEXT("Use an ffp context instead of a shader context")
					}
				}
			},
			fcppt::options::argument<
				scene_name_label,
				fcppt::string
			>{
				fcppt::options::long_name{
					FCPPT_TEXT("scene-name")
				},
				fcppt::options::optional_help_text{
					fcppt::options::help_text{
						FCPPT_TEXT("Scene name (denotes a path below media/scenes)")
					}
				}
			}
		)
	};

	typedef
	fcppt::options::result_of<
		decltype(
			argument_parser
		)
	>
	result_type;

	return
		fcppt::variant::match(
			fcppt::options::parse_help(
				fcppt::options::default_help_switch(),
				argument_parser,
				fcppt::args_from_second(
					_function_context.argc(),
					_function_context.argv()
				)
			),
			[](
				fcppt::options::result<
					result_type
				> const _result
			)
			{
				return
					fcppt::either::match(
						_result,
						[](
							fcppt::options::error const &_error
						)
						{
							fcppt::io::cerr()
								<<
								_error
								<<
								FCPPT_TEXT('\n');

							return
								awl::main::exit_failure();
						},
						[](
							result_type const &_options
						)
						{
							return
								main_program(
									fcppt::record::permute<
										options_record
									>(
										_options
									)
								);
						}
					);
			},
			[](
				fcppt::options::help_text const &_help_text
			)
			{
				fcppt::io::cout()
					<<
					_help_text
					<<
					FCPPT_TEXT('\n');

				return
					awl::main::exit_success();
			}
		);
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
