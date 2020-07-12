//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image/color/bgra8_format.hpp>
#include <sge/image/color/convert.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/primitive_type.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/context/core.hpp>
#include <sge/renderer/context/scoped_core.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/display_mode/fullscreen.hpp>
#include <sge/renderer/display_mode/fullscreen_desktop.hpp>
#include <sge/renderer/display_mode/optional_fullscreen.hpp>
#include <sge/renderer/display_mode/parameters.hpp>
#include <sge/renderer/display_mode/vsync.hpp>
#include <sge/renderer/event/render.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/object.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/target/base.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/vertex/buffer.hpp>
#include <sge/renderer/vertex/buffer_parameters.hpp>
#include <sge/renderer/vertex/buffer_unique_ptr.hpp>
#include <sge/renderer/vertex/const_buffer_ref_container.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/declaration.hpp>
#include <sge/renderer/vertex/declaration_parameters.hpp>
#include <sge/renderer/vertex/declaration_unique_ptr.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <sge/renderer/vertex/scoped_declaration_and_buffers.hpp>
#include <sge/renderer/vertex/scoped_lock.hpp>
#include <sge/renderer/vf/color.hpp>
#include <sge/renderer/vf/format.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/part.hpp>
#include <sge/renderer/vf/pos.hpp>
#include <sge/renderer/vf/proxy.hpp>
#include <sge/renderer/vf/set_proxy.hpp>
#include <sge/renderer/vf/vertex_size.hpp>
#include <sge/renderer/vf/view.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/renderer/vf/dynamic/make_part_index.hpp>
#include <sge/renderer/vf/labels/color.hpp>
#include <sge/renderer/vf/labels/pos.hpp>
#include <sge/systems/cursor_option_field.hpp>
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
#include <sge/systems/with_input.hpp>
#include <sge/systems/with_renderer.hpp>
#include <sge/systems/with_window.hpp>
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
#include <fcppt/exception.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/config/external_begin.hpp>
#include <example_main.hpp>
#include <exception>
#include <fcppt/config/external_end.hpp>


awl::main::exit_code
example_main(
	awl::main::function_context const &
)
try
{
	sge::systems::instance<
		sge::systems::with_window,
		sge::systems::with_renderer<
			sge::systems::renderer_caps::core
		>,
		sge::systems::with_input
	> const sys(
		sge::systems::make_list
		(
			sge::systems::window(
				sge::systems::window_source(
					sge::systems::original_window(
						sge::window::title(
							FCPPT_TEXT("sge vertex example")
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
					sge::renderer::display_mode::optional_fullscreen{
						sge::renderer::display_mode::fullscreen{
							sge::renderer::display_mode::fullscreen_desktop{}
						}
					}
				),
				sge::viewport::optional_resize_callback{
					sge::viewport::fill_on_resize()
				}
			)
		)
		(
			sge::systems::input(
				sge::systems::cursor_option_field::null()
			)
		)
	);

//! [position_declaration]
	using
	pos3_type
	=
	sge::renderer::vf::pos<
		float,
		3
	>;
//! [position_declaration]

//! [color_declaration]
	using
	color_format
	=
	sge::image::color::bgra8_format;

	using
	color_type
	=
	sge::renderer::vf::color<
		color_format
	>;
//! [color_declaration]

//! [format_part_declaration]
	using
	format_part
	=
	sge::renderer::vf::part<
		pos3_type,
		color_type
	>;
//! [format_part_declaration]

//! [format_declaration]
	using
	format
	=
	sge::renderer::vf::format<
		format_part
	>;
//! [format_declaration]

//! [vertex_declaration]
	sge::renderer::vertex::declaration_unique_ptr const vertex_declaration(
		sys.renderer_device_core().create_vertex_declaration(
			sge::renderer::vertex::declaration_parameters(
				sge::renderer::vf::dynamic::make_format<
					format
				>()
			)
		)
	);
//! [vertex_declaration]

//! [vertex_buffer]
	sge::renderer::vertex::buffer_unique_ptr const vertex_buffer(
		sys.renderer_device_core().create_vertex_buffer(
			sge::renderer::vertex::buffer_parameters(
				fcppt::make_cref(
					*vertex_declaration
				),
				sge::renderer::vf::dynamic::make_part_index<
					format,
					format_part
				>(),
				sge::renderer::vertex::count(
					3U
				),
				sge::renderer::resource_flags_field::null()
			)
		)
	);
//! [vertex_buffer]

//! [vblock_declaration]
	{
		sge::renderer::vertex::scoped_lock const vblock(
			fcppt::make_ref(
				*vertex_buffer
			),
			sge::renderer::lock_mode::writeonly
		);
//! [vblock_declaration]

//! [vertex_view_declaration]
		using
		vertex_view
		=
		sge::renderer::vf::view<
			format_part
		>;

		vertex_view const vertices(
			vblock.value()
		);
//! [vertex_view_declaration]

//! [vertex_iterator_declaration]
		vertex_view::iterator vb_it(
			vertices.begin()
		);
//! [vertex_iterator_declaration]

//! [vertex_write_pos_1]
		using
		vec3
		=
		pos3_type::packed_type;

		sge::renderer::vf::set_proxy(
			*vb_it,
			sge::renderer::vf::labels::pos{},
			vec3(-1.F, 1.F, 0.F)
		);
//! [vertex_write_pos_1]

//! [vertex_write_color_1]
		sge::renderer::vf::set_proxy(
			*vb_it,
			sge::renderer::vf::labels::color{},
			sge::image::color::convert<
				color_format
			>(
				sge::image::color::predef::cyan()
			)
		);
//! [vertex_write_color_1]

//! [vertex_write_rest]
		++vb_it;

		sge::renderer::vf::set_proxy(
			*vb_it,
			sge::renderer::vf::labels::pos{},
			vec3(-1.F, -1.F, 0.F)
		);

		sge::renderer::vf::set_proxy(
			*vb_it,
			sge::renderer::vf::labels::color{},
			sge::image::color::convert<
				color_format
			>(
				sge::image::color::predef::yellow()
			)
		);

		++vb_it;

		sge::renderer::vf::set_proxy(
			*vb_it,
			sge::renderer::vf::labels::pos{},
			vec3(1.F, 1.F, 0.F)
		);

		sge::renderer::vf::set_proxy(
			*vb_it,
			sge::renderer::vf::labels::color{},
			sge::image::color::convert<
				color_format
			>(
				sge::image::color::predef::magenta()
			)
		);
	}
//! [vertex_write_rest]

	auto const draw(
		[
			&vertex_buffer,
			&vertex_declaration,
			&sys
		]{
			sge::renderer::context::scoped_core const scoped_block(
				fcppt::make_ref(
					sys.renderer_device_core()
				),
				fcppt::reference_to_base<
					sge::renderer::target::base
				>(
					fcppt::make_ref(
						sys.renderer_device_core().onscreen_target()
					)
				)
			);

			sge::renderer::context::core &context(
				scoped_block.get()
			);

			context.clear(
				sge::renderer::clear::parameters()
				.back_buffer(
					sge::image::color::any::object{
						sge::image::color::predef::black()
					}
				)
			);

//! [scoped_declaration]
			sge::renderer::vertex::scoped_declaration_and_buffers const vb_context(
				fcppt::make_ref(
					context
				),
				fcppt::make_cref(
					*vertex_declaration
				),
				sge::renderer::vertex::const_buffer_ref_container{
					fcppt::make_cref(
						*vertex_buffer
					)
				}
			);
//! [scoped_declaration]

//! [scoped_block]
			context.render_nonindexed(
				sge::renderer::vertex::first(
					0U
				),
				sge::renderer::vertex::count(
					3U
				),
				sge::renderer::primitive_type::triangle_list
			);
//! [scoped_block]
		}
	);

//! [running_block]
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
//! [running_block]
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
