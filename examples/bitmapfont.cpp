//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/config/media_path.hpp>
#include <sge/font/from_fcppt_string.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/object.hpp>
#include <sge/font/object_unique_ptr.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/vector.hpp>
#include <sge/font/align_h/center.hpp>
#include <sge/font/align_h/left.hpp>
#include <sge/font/align_h/max_width.hpp>
#include <sge/font/align_h/right.hpp>
#include <sge/font/align_h/variant.hpp>
#include <sge/font/bitmap/create.hpp>
#include <sge/font/draw/static_text.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>
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
#include <sge/renderer/target/viewport_size.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/image2d.hpp>
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
#include <sge/viewport/center_on_resize.hpp>
#include <sge/viewport/optional_resize_callback.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/loop.hpp>
#include <sge/window/loop_function.hpp>
#include <sge/window/title.hpp>
#include <awl/show_error.hpp>
#include <awl/show_error_narrow.hpp>
#include <awl/event/base.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context.hpp>
#include <fcppt/args_from_second.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/output_to_fcppt_string.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/either/match.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/options/argument.hpp>
#include <fcppt/options/error.hpp>
#include <fcppt/options/error_output.hpp>
#include <fcppt/options/long_name.hpp>
#include <fcppt/options/make_optional.hpp>
#include <fcppt/options/optional_help_text.hpp>
#include <fcppt/options/parse.hpp>
#include <fcppt/options/result_of.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/record/make_label.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal/list/list.hpp>
#include <example_main.hpp>
#include <exception>
#include <fcppt/config/external_end.hpp>


namespace
{

awl::main::exit_code
main_program(
	sge::font::string const &_text
)
{
	sge::systems::instance<
		metal::list<
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
							FCPPT_TEXT("bitmapfont")
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

	sge::font::object_unique_ptr const font_object(
		sge::font::bitmap::create(
			sys.log_context(),
			sge::config::media_path()
			/ FCPPT_TEXT("fonts")
			/ FCPPT_TEXT("bitmap")
			/ FCPPT_TEXT("font.json"),
			sys.image_system()
		)
	);

	sge::font::draw::static_text const static_text_left(
		sys.renderer_device_ffp(),
		*font_object,
		_text,
		sge::font::text_parameters(
			sge::font::align_h::variant(
				sge::font::align_h::left(
					sge::font::align_h::max_width(
						300
					)
				)
			)
		),
		sge::font::vector(
			100,
			100
		),
		sge::image::color::any::object{
			sge::image::color::predef::white()
		},
		sge::renderer::texture::emulate_srgb::yes
	);

	sge::font::draw::static_text const static_text_center(
		sys.renderer_device_ffp(),
		*font_object,
		_text,
		sge::font::text_parameters(
			sge::font::align_h::variant(
				sge::font::align_h::center(
					sge::font::align_h::max_width(
						300
					)
				)
			)
		),
		sge::font::vector(
			400,
			100
		),
		sge::image::color::any::object{
			sge::image::color::predef::white()
		},
		sge::renderer::texture::emulate_srgb::yes
	);

	sge::font::draw::static_text const static_text_right(
		sys.renderer_device_ffp(),
		*font_object,
		_text,
		sge::font::text_parameters(
			sge::font::align_h::variant(
				sge::font::align_h::right(
					sge::font::align_h::max_width(
						300
					)
				)
			)
		),
		sge::font::vector(
			700,
			100
		),
		sge::image::color::any::object{
			sge::image::color::predef::white()
		},
		sge::renderer::texture::emulate_srgb::yes
	);

	auto const draw(
		[
			&static_text_center,
			&static_text_left,
			&static_text_right,
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

			static_text_left.draw(
				scoped_block.get()
			);

			static_text_center.draw(
				scoped_block.get()
			);

			static_text_right.draw(
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
				}
			}
		);
}

}

awl::main::exit_code const
example_main(
	awl::main::function_context const &_main_function_context
)
try
{
	FCPPT_RECORD_MAKE_LABEL(
		text_label
	);

	auto const parser(
		fcppt::options::make_optional(
			fcppt::options::argument<
				text_label,
				fcppt::string
			>{
				fcppt::options::long_name{
					FCPPT_TEXT("text")
				},
				fcppt::options::optional_help_text{}
			}
		)
	);

	typedef
	fcppt::options::result_of<
		decltype(
			parser
		)
	>
	result_type;

	return
		fcppt::either::match(
			fcppt::options::parse(
				parser,
				fcppt::args_from_second(
					_main_function_context.argc(),
					_main_function_context.argv()
				)
			),
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
				result_type const &_result
			)
			{
				return
					main_program(
						fcppt::optional::from(
							fcppt::optional::map(
								fcppt::record::get<
									text_label
								>(
									_result
								),
								[](
									fcppt::string const &_text
								)
								{
									return
										sge::font::from_fcppt_string(
											_text
										);
								}
							),
							[]{
								return
									sge::font::string{
										SGE_FONT_LIT("test abcd e 123456789 10 11")
									};
							}
						)
					);
			}
		);
}
catch(
	fcppt::exception const &_exception
)
{
	awl::show_error(
		_exception.string()
	);

	return
		awl::main::exit_failure();
}
catch(
	std::exception const &_exception
)
{
	awl::show_error_narrow(
		_exception.what()
	);

	return
		awl::main::exit_failure();
}
