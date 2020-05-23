//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image/color/bgra8_format.hpp>
#include <sge/image/color/convert.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/primitive_type.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/context/core.hpp>
#include <sge/renderer/context/scoped_core.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/display_mode/parameters.hpp>
#include <sge/renderer/display_mode/vsync.hpp>
#include <sge/renderer/event/render.hpp>
#include <sge/renderer/index/buffer.hpp>
#include <sge/renderer/index/buffer_parameters.hpp>
#include <sge/renderer/index/buffer_unique_ptr.hpp>
#include <sge/renderer/index/count.hpp>
#include <sge/renderer/index/first.hpp>
#include <sge/renderer/index/format_16.hpp>
#include <sge/renderer/index/iterator.hpp>
#include <sge/renderer/index/nonconst_tag.hpp>
#include <sge/renderer/index/scoped_lock.hpp>
#include <sge/renderer/index/view.hpp>
#include <sge/renderer/index/dynamic/make_format.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/target/base.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/vertex/buffer.hpp>
#include <sge/renderer/vertex/buffer_unique_ptr.hpp>
#include <sge/renderer/vertex/const_buffer_ref_container.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/create_buffer_from_vertices.hpp>
#include <sge/renderer/vertex/declaration.hpp>
#include <sge/renderer/vertex/declaration_parameters.hpp>
#include <sge/renderer/vertex/declaration_unique_ptr.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <sge/renderer/vertex/scoped_declaration_and_buffers.hpp>
#include <sge/renderer/vf/color.hpp>
#include <sge/renderer/vf/format.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/part.hpp>
#include <sge/renderer/vf/pos.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
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
#include <fcppt/literal.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/container/array/make.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/config/external_begin.hpp>
#include <example_main.hpp>
#include <exception>
#include <fcppt/config/external_end.hpp>


awl::main::exit_code const
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
					sge::renderer::display_mode::optional_object()
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

	typedef
	sge::renderer::vf::pos<
		float,
		3
	>
	pos3_type;

	typedef
	sge::renderer::vf::color<
		sge::image::color::bgra8_format
	>
	color_type;

	typedef
	sge::renderer::vf::part<
		pos3_type,
		color_type
	>
	format_part;

	typedef
	sge::renderer::vf::format<
		format_part
	>
	format;

	sge::renderer::vertex::declaration_unique_ptr const vertex_declaration(
		sys.renderer_device_core().create_vertex_declaration(
			sge::renderer::vertex::declaration_parameters(
				sge::renderer::vf::dynamic::make_format<
					format
				>()
			)
		)
	);

	typedef
	sge::renderer::vf::vertex<
		format_part
	>
	vertex;

	auto const make_color(
		[](
			sge::image::color::rgba8 const _color
		)
		{
			return
				sge::image::color::convert<
					sge::image::color::bgra8_format
				>(
					_color
				);
		}
	);

	typedef
	pos3_type::packed_type
	vec3;

	sge::renderer::vertex::buffer_unique_ptr const vertex_buffer{
		sge::renderer::vertex::create_buffer_from_vertices<
			format
		>(
			sys.renderer_device_core(),
			*vertex_declaration,
			sge::renderer::resource_flags_field::null(),
			fcppt::container::array::make(
				vertex{
					sge::renderer::vf::labels::pos{} =
						vec3(-1.f, 1.f, 0.f),
					sge::renderer::vf::labels::color{} =
						make_color(
							sge::image::color::predef::cyan()
						)
				},
				vertex{
					sge::renderer::vf::labels::pos{} =
						vec3(-1.f, -1.f, 0.f),
					sge::renderer::vf::labels::color{} =
						make_color(
							sge::image::color::predef::yellow()
						)
				},
				vertex{
					sge::renderer::vf::labels::pos{} =
						vec3(1.f, 1.f, 0.f),
					sge::renderer::vf::labels::color{} =
						make_color(
							sge::image::color::predef::magenta()
						)
				},
				vertex{
					sge::renderer::vf::labels::pos{} =
						vec3(1.f, -1.f, 0.f),
					sge::renderer::vf::labels::color{} =
						make_color(
							sge::image::color::predef::red()
						)
				}
			)
		)
	};

	typedef
	sge::renderer::index::format_16
	index_format;

	sge::renderer::index::buffer_unique_ptr const index_buffer(
		sys.renderer_device_core().create_index_buffer(
			sge::renderer::index::buffer_parameters(
				sge::renderer::index::dynamic::make_format<
					index_format
				>(),
				sge::renderer::index::count(
					6u
				),
				sge::renderer::resource_flags_field::null()
			)
		)
	);

	{
		sge::renderer::index::scoped_lock const iblock(
			*index_buffer,
			sge::renderer::lock_mode::writeonly
		);

		typedef
		sge::renderer::index::view<
			index_format,
			sge::renderer::index::nonconst_tag
		>
		index_view;

		index_view const view(
			iblock.value()
		);

		index_view::iterator it(
			view.begin()
		);

		typedef
		index_view::value_type
		index_value_type;

		(*it++).set(fcppt::literal<index_value_type>(0));
		(*it++).set(fcppt::literal<index_value_type>(1));
		(*it++).set(fcppt::literal<index_value_type>(2));
		(*it++).set(fcppt::literal<index_value_type>(1));
		(*it++).set(fcppt::literal<index_value_type>(3));
		(*it++).set(fcppt::literal<index_value_type>(2));
	}

	auto const draw(
		[
			&index_buffer,
			&vertex_declaration,
			&vertex_buffer,
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

			sge::renderer::vertex::scoped_declaration_and_buffers const vb_context(
				scoped_block.get(),
				*vertex_declaration,
				sge::renderer::vertex::const_buffer_ref_container{
					fcppt::make_cref(
						*vertex_buffer
					)
				}
			);

			scoped_block.get().render_indexed(
				*index_buffer,
				sge::renderer::vertex::first(
					0u
				),
				sge::renderer::vertex::count(
					4u
				),
				sge::renderer::primitive_type::triangle_list,
				sge::renderer::index::first(
					0u
				),
				sge::renderer::index::count(
					6u
				)
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
