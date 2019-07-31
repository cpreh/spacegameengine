//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cegui/cursor_visibility.hpp>
#include <sge/cegui/default_cursor.hpp>
#include <sge/cegui/default_focus.hpp>
#include <sge/cegui/duration.hpp>
#include <sge/cegui/load_context.hpp>
#include <sge/cegui/log_location.hpp>
#include <sge/cegui/syringe.hpp>
#include <sge/cegui/system.hpp>
#include <sge/cegui/unit.hpp>
#include <sge/cegui/toolbox/scoped_gui_sheet.hpp>
#include <sge/cegui/toolbox/scoped_layout.hpp>
#include <sge/config/app_name.hpp>
#include <sge/config/media_path.hpp>
#include <sge/config/own_log_path.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/input/event_base.hpp>
#include <sge/log/option.hpp>
#include <sge/log/option_container.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_set.hpp>
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
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/systems/config.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/image2d.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/log_settings.hpp>
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
#include <sge/timer/elapsed.hpp>
#include <sge/timer/parameters.hpp>
#include <sge/timer/clocks/standard.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/viewport/optional_resize_callback.hpp>
#include <sge/window/loop.hpp>
#include <sge/window/loop_function.hpp>
#include <sge/window/title.hpp>
#include <awl/show_error.hpp>
#include <awl/show_error_narrow.hpp>
#include <awl/event/base.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context_fwd.hpp>
#include <awl/main/scoped_output.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/dynamic_fun.hpp>
#include <fcppt/io/clog.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/variant/dynamic_cast.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/sequences/list.hpp>
#include <chrono>
#include <example_main.hpp>
#include <exception>
#include <fcppt/config/external_end.hpp>


awl::main::exit_code const
example_main(
	awl::main::function_context const &
)
try
{
	fcppt::string const app_name(
		FCPPT_TEXT("simple gui test")
	);

	awl::main::scoped_output const output(
		fcppt::io::clog(),
		sge::config::own_log_path(
			sge::config::app_name(
				app_name
			)
		)
	);

	sge::systems::instance<
		brigand::list<
			sge::systems::with_renderer<
				sge::systems::renderer_caps::ffp
			>,
			sge::systems::with_window,
			sge::systems::with_input,
			sge::systems::with_image2d
		>
	> const sys(
		sge::systems::make_list
		(
			sge::systems::window(
				sge::systems::window_source(
					sge::systems::original_window(
						sge::window::title(
							app_name
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
		)(
			sge::systems::config()
			.log_settings(
				sge::systems::log_settings(
					sge::log::option_container{
						sge::log::option{
							sge::cegui::log_location(),
							fcppt::log::level::verbose
						}
					}
				)
			)
		)
	);

	sge::cegui::system gui_sys(
		sys.log_context(),
		sge::cegui::load_context(
			sge::config::media_path()
			/
			FCPPT_TEXT("gui")
			/
			FCPPT_TEXT("TaharezLook.scheme")
		)
		.font_directory(
			sge::config::media_path()
			/
			FCPPT_TEXT("fonts")
		),
		sys.renderer_device_ffp(),
		sys.image_system(),
		sys.viewport_manager(),
		sge::cegui::cursor_visibility::visible,
		sge::renderer::texture::emulate_srgb::yes
	);

	sge::cegui::syringe gui_syringe(
		sys.log_context(),
		gui_sys
	);

	sge::cegui::default_cursor gui_cursor{
		gui_syringe
	};

	sge::cegui::default_focus gui_focus{
		gui_syringe
	};

	sge::timer::basic<
		sge::timer::clocks::standard
	> frame_timer(
		sge::timer::parameters<
			sge::timer::clocks::standard
		>(
			std::chrono::seconds(
				1
			)
		)
	);

	sge::cegui::toolbox::scoped_layout scoped_layout(
		gui_sys,
		sge::config::media_path()
		/
		FCPPT_TEXT("gui")
		/
		FCPPT_TEXT("text_demo.layout")
	);

	sge::cegui::toolbox::scoped_gui_sheet const scoped_gui_sheet(
		gui_sys,
		scoped_layout.window()
	);

	auto const draw(
		[
			&frame_timer,
			&gui_sys,
			&sys
		]{
			gui_sys.update(
				std::chrono::duration_cast<
					sge::cegui::duration
				>(
					sge::timer::elapsed(
						frame_timer
					)
				)
			);

			frame_timer.reset();

			sge::renderer::context::scoped_ffp const scoped_block(
				sys.renderer_device_ffp(),
				sys.renderer_device_ffp().onscreen_target()
			);

			scoped_block.get().clear(
				sge::renderer::clear::parameters()
				.back_buffer(
					sge::image::color::any::object{
						sge::image::color::predef::red()
					}
				)
			);

			gui_sys.render(
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
					&draw,
					&gui_cursor,
					&gui_focus
				](
					awl::event::base const &_event
				)
				{

					sge::systems::quit_on_escape(
						sys,
						_event
					);

					fcppt::optional::maybe_void(
						fcppt::variant::dynamic_cast_<
							brigand::list<
								sge::renderer::event::render const,
								sge::input::event_base const
							>,
							fcppt::cast::dynamic_fun
						>(
							_event
						),
						[
							&draw,
							&gui_cursor,
							&gui_focus
						](
							auto const &_variant
						)
						{
							fcppt::variant::match(
								_variant,
								[
									&draw
								](
									fcppt::reference<
										sge::renderer::event::render const
									>
								)
								{
									draw();
								},
								[
									&gui_cursor,
									&gui_focus
								](
									fcppt::reference<
										sge::input::event_base const
									> const _input_event
								)
								{
									gui_cursor.process_event(
										_input_event.get()
									);

									gui_focus.process_event(
										_input_event.get()
									);
								}
							);
						}
					);
				}
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
