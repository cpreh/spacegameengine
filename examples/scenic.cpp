//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/camera/base.hpp>
#include <sge/camera/optional_projection_matrix.hpp>
#include <sge/camera/coordinate_system/identity.hpp>
#include <sge/camera/first_person/movement_speed.hpp>
#include <sge/camera/first_person/object.hpp>
#include <sge/camera/first_person/parameters.hpp>
#include <sge/camera/matrix_conversion/world.hpp>
#include <sge/camera/tracking/is_looping.hpp>
#include <sge/camera/tracking/object.hpp>
#include <sge/camera/tracking/json/interval_exporter.hpp>
#include <sge/camera/tracking/json/key_press_exporter.hpp>
#include <sge/camera/tracking/json/keyframes_from_json.hpp>
#include <sge/config/media_path.hpp>
#include <sge/graph/color_schemes.hpp>
#include <sge/graph/object.hpp>
#include <sge/graph/scalar.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/input/event_base.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/parse/json/parse_file_exn.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/context/core.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/context/scoped_ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/display_mode/parameters.hpp>
#include <sge/renderer/display_mode/vsync.hpp>
#include <sge/renderer/event/render.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/target/base.hpp>
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
#include <sge/timer/basic.hpp>
#include <sge/timer/elapsed_and_reset.hpp>
#include <sge/timer/parameters.hpp>
#include <sge/timer/clocks/standard.hpp>
#include <sge/viewport/center_on_resize.hpp>
#include <sge/viewport/optional_resize_callback.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/loop.hpp>
#include <sge/window/loop_function.hpp>
#include <sge/window/title.hpp>
#include <awl/show_error.hpp>
#include <awl/show_error_narrow.hpp>
#include <awl/show_message.hpp>
#include <awl/event/base.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/exit_success.hpp>
#include <awl/main/function_context.hpp>
#include <fcppt/args_from_second.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/output_to_fcppt_string.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/string.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/either/match.hpp>
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
#include <fcppt/record/object_impl.hpp>
#include <fcppt/record/permute.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/variant/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <example_main.hpp>
#include <chrono>
#include <exception>
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
fcppt::record::object<
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
		awl::show_error(
			FCPPT_TEXT("You specified to record a file and use the tracking camera, that doesn't make sense.\n")
		);

		return
			awl::main::exit_failure();
	}

	sge::window::dim const window_dim(
		1024u,
		768u
	);

	sge::systems::instance<
		sge::systems::with_window,
		sge::systems::with_renderer<
			sge::systems::renderer_caps::ffp
		>,
		sge::systems::with_input,
		sge::systems::with_image2d
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

	fcppt::unique_ptr<
		sge::camera::base
	> const camera(
		fcppt::optional::maybe(
			fcppt::record::get<
				track_from_file_label
			>(
				_options
			),
			[]{
				return
					fcppt::unique_ptr_to_base<
						sge::camera::base
					>(
						fcppt::make_unique_ptr<
							sge::camera::first_person::object
						>(
							sge::camera::first_person::parameters(
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
									std::filesystem::path(
										_track_from_file
									)
								).array()
							),
							sge::camera::tracking::is_looping(
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
						fcppt::make_cref(
							*camera
						),
						sge::camera::update_duration{
							fcppt::record::get<
								recording_interval_label
							>(
								_options
							)
						},
						std::filesystem::path(
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
		sge::image::color::any::object{
			sge::image::color::predef::white()
		}
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
			fcppt::literal<
				sge::graph::scalar
			>(
				1.f
				/
				30.f
			)
		},
		sge::graph::optional_axis_constraint{
			sge::graph::axis_constraint{
				fcppt::literal<
					sge::graph::scalar
				>(
					0.f
				),
				fcppt::literal<
					sge::graph::scalar
				>(
					0.1f
				)
			}
		},
		sge::graph::color_schemes::default_()
	};

	/*
	camera.update_coordinate_system(
		sge::camera::coordinate_system::identity());
	*/

	auto const draw(
		[
			&camera,
			&camera_timer,
			&exporter,
			&graph,
			&scene_manager,
			&simple_grid_xz,
			&sys,
			&test_scene
		]{
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
				fcppt::cast::size<
					sge::graph::scalar
				>(
					difference_since_last_frame.count()
				)
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
				fcppt::make_ref(
					sys.renderer_device_ffp()
				),
				fcppt::reference_to_base<
					sge::renderer::target::base
				>(
					fcppt::make_ref(
						sys.renderer_device_ffp().onscreen_target()
					)
				)
			};

			scoped_block.get().clear(
				sge::renderer::clear::parameters()
					.back_buffer(
						sge::image::color::any::object{
							sge::image::color::predef::black()
						}
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
						fcppt::reference_to_base<
							sge::renderer::context::core
						>(
							fcppt::make_ref(
								scoped_block.get()
							)
						)
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
	);

	return
		sge::window::loop(
			sys.window_system(),
			sge::window::loop_function{
				[
					&sys,
					&camera,
					&draw
				](
					awl::event::base const &_event
				)
				{
					sge::systems::quit_on_escape(
						sys,
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

					fcppt::optional::maybe_void(
						fcppt::cast::dynamic<
							sge::input::event_base const
						>(
							_event
						),
						[
							&camera
						](
							fcppt::reference<
								sge::input::event_base const
							> const _input_event
						)
						{
							camera->process_event(
								_input_event.get()
							);
						}
					);

				}
			}
		);
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
							awl::show_error(
								fcppt::output_to_fcppt_string(
									_error
								)
							);

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
				awl::show_message(
					fcppt::output_to_fcppt_string(
						_help_text
					)
				);

				return
					awl::main::exit_success();
			}
		);
}
catch(
	fcppt::exception const &_error
)
{
	awl::show_error(
		_error.string()
	);

	return
		awl::main::exit_failure();
}
catch(
	std::exception const &_error
)
{
	awl::show_error_narrow(
		_error.what()
	);

	return
		awl::main::exit_failure();
}
