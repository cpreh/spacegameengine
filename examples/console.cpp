//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/config/media_path.hpp>
#include <sge/console/arg_list.hpp>
#include <sge/console/fallback.hpp>
#include <sge/console/muxing_narrow_streambuf.hpp>
#include <sge/console/object.hpp>
#include <sge/console/prefix.hpp>
#include <sge/console/callback/convenience.hpp>
#include <sge/console/gfx/font_color.hpp>
#include <sge/console/gfx/input_active.hpp>
#include <sge/console/gfx/object.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/object.hpp>
#include <sge/font/object_unique_ptr.hpp>
#include <sge/font/parameters.hpp>
#include <sge/font/rect.hpp>
#include <sge/font/system.hpp>
#include <sge/font/to_fcppt_string.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/system.hpp>
#include <sge/input/focus/event/base.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/renderer/resource_flags_field.hpp>
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
#include <sge/renderer/texture/create_planar_from_path.hpp>
#include <sge/renderer/texture/emulate_srgb_from_caps.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
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
#include <sge/systems/with_font.hpp>
#include <sge/systems/with_image2d.hpp>
#include <sge/systems/with_input.hpp>
#include <sge/systems/with_renderer.hpp>
#include <sge/systems/with_window.hpp>
#include <sge/texture/part_raw_ptr.hpp>
#include <sge/viewport/center_on_resize.hpp>
#include <sge/viewport/optional_resize_callback.hpp>
#include <sge/window/loop.hpp>
#include <sge/window/loop_function.hpp>
#include <sge/window/system.hpp>
#include <sge/window/title.hpp>
#include <awl/show_error.hpp>
#include <awl/show_error_narrow.hpp>
#include <awl/event/base.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/exit_success.hpp>
#include <awl/main/function_context_fwd.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/output_to_string.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/dynamic_fun.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/variant/dynamic_cast.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal/list/list.hpp>
#include <example_main.hpp>
#include <exception>
#include <iostream>
#include <fcppt/config/external_end.hpp>


awl::main::exit_code const
example_main(
	awl::main::function_context const &
)
try
{
	sge::systems::instance<
		metal::list<
			sge::systems::with_renderer<
				sge::systems::renderer_caps::ffp
			>,
			sge::systems::with_window,
			sge::systems::with_input,
			sge::systems::with_image2d,
			sge::systems::with_font
		>
	> const sys(
		sge::systems::make_list
		(
			sge::systems::window(
				sge::systems::window_source(
					sge::systems::original_window(
						sge::window::title(
							FCPPT_TEXT("sge console test")
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
					sge::viewport::center_on_resize(
						sge::window::dim{
							1024u,
							768u
						}
					)
				}
			)
		)
		(
			sge::systems::input(
				sge::systems::cursor_option_field::null()
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
	);

	sge::console::object object(
		sge::console::prefix(
			SGE_FONT_LIT('/')
		)
	);

	fcppt::signal::auto_connection const c0(
		object.insert(
			sge::console::callback::convenience<
				void()
			>(
				[
					&sys
				]{
					sys.window_system().quit(
						awl::main::exit_success()
					);
				},
				sge::console::callback::name(
					SGE_FONT_LIT("quit")
				),
				sge::console::callback::short_description(
					SGE_FONT_LIT("Usage: /quit")
				)
			)
		)
	);

	fcppt::signal::auto_connection const c1(
		object.register_fallback(
			sge::console::fallback{
				[](
					sge::font::string const &_arg
				)
				{
					fcppt::io::cout()
						<<
						FCPPT_TEXT("fallback called with argument:")
						<<
						fcppt::optional::from(
							sge::font::to_fcppt_string(
								_arg
							),
							[]{
								return
									fcppt::string{
										FCPPT_TEXT("Failed to convert fallback text!")
									};
							}
						)
						<<
						FCPPT_TEXT('\n');
				}
			}
		)
	);

	fcppt::signal::auto_connection const c2(
		object.insert(
			sge::console::callback::convenience<
				void(
					float
				)
			>(
				[
					&object
				](
					float const _value
				)
				{
					object.emit_message(
						SGE_FONT_LIT("New value is ")
						+
						fcppt::output_to_string<
							sge::font::string
						>(
							_value
							+
							1.f
						)
					);
				},
				sge::console::callback::name(
					SGE_FONT_LIT("increment")
				),
				sge::console::callback::short_description(
					SGE_FONT_LIT("Usage: /increment <float-value>")
				)
			)
			.long_description(
				SGE_FONT_LIT("Increments the float value (extremely useful!)")
			)
		)
	);

	sge::texture::part_raw_ptr const tex_bg(
		sge::renderer::texture::create_planar_from_path(
			sge::config::media_path()
			/ FCPPT_TEXT("images")
			/ FCPPT_TEXT("grass.png"),
			sys.renderer_device_ffp(),
			sys.image_system(),
			sge::renderer::texture::mipmap::off(),
			sge::renderer::resource_flags_field::null(),
			sge::renderer::texture::emulate_srgb_from_caps(
				sys.renderer_device_ffp().caps()
			)
		)
	);

	sge::font::object_unique_ptr const font_object(
		sys.font_system().create_font(
			sge::font::parameters()
		)
	);

	sge::console::gfx::object gfx(
		object,
		sys.renderer_device_ffp(),
		sge::console::gfx::font_color(
			sge::image::color::any::object{
				sge::image::color::predef::white()
			}
		),
		*font_object,
		sge::font::rect{
			fcppt::math::vector::null<
				sge::font::rect::vector
			>(),
			sge::font::rect::dim{
				400,
				300
			}
		},
		sge::console::gfx::output_line_limit(
			100u
		)
	);

	// TODO: muxing_fcppt_streambuf?
	sge::console::muxing_narrow_streambuf stdout_streambuf(
		std::cout,
		object,
		sge::console::muxing::enabled
	);

	std::cout << "Test for console muxer (cout).\n";

	std::cout << "You should see this message in the console and in the terminal (if available)\n";

	sge::console::muxing_narrow_streambuf stderr_streambuf(
		std::cerr,
		object,
		sge::console::muxing::disabled
	);

	std::cerr << "Test for console muxer (cerr).\n";

	std::cerr << "You should see this message _only_ in the console and _not_ in the terminal (if available)\n";

	auto const draw(
		[
			&gfx,
			&sys
		]{
			sge::renderer::context::scoped_ffp const scoped_block(
				sys.renderer_device_ffp(),
				sys.renderer_device_ffp().onscreen_target()
			);

			scoped_block.get().clear(
				sge::renderer::clear::parameters()
				.back_buffer(
					sge::image::color::any::object{
						sge::image::color::predef::black()
					}
				)
			);

			gfx.render(
				scoped_block.get(),
				sge::console::gfx::input_active{
					true
				}
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
					&gfx
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
							metal::list<
								sge::renderer::event::render const,
								sge::input::focus::event::base const
							>,
							fcppt::cast::dynamic_fun
						>(
							_event
						),
						[
							&draw,
							&gfx
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
									&gfx
								](
									fcppt::reference<
										sge::input::focus::event::base const
									> const _focus_event
								)
								{
									gfx.focus_event(
										_focus_event.get()
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
