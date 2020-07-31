//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cg/string.hpp>
#include <sge/cg/context/object.hpp>
#include <sge/cg/profile/object.hpp>
#include <sge/cg/profile/shader_type.hpp>
#include <sge/cg/program/from_string_parameters.hpp>
#include <sge/cg/program/main_function.hpp>
#include <sge/cg/program/object.hpp>
#include <sge/cg/program/source.hpp>
#include <sge/cg/program/source_type.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/renderer/primitive_type.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/cg/loaded_program.hpp>
#include <sge/renderer/cg/loaded_program_unique_ptr.hpp>
#include <sge/renderer/cg/scoped_program.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/context/core.hpp>
#include <sge/renderer/context/scoped_core.hpp>
#include <sge/renderer/device/core.hpp>
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
#include <sge/renderer/vf/format.hpp>
#include <sge/renderer/vf/part.hpp>
#include <sge/renderer/vf/pos.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
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
#include <fcppt/container/array/make.hpp>
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
							FCPPT_TEXT("sge cg simple test")
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

	sge::cg::context::object const cg_context{};

	sge::cg::profile::object const vertex_profile(
		sys.renderer_device_core().create_cg_profile(
			sge::cg::profile::shader_type::vertex
		)
	);

	sge::cg::string const vertex_shader_source(
		"// This is C2E1v_green from \"The Cg Tutorial\" (Addison-Wesley, ISBN\n"
		"// 0321194969) by Randima Fernando and Mark J. Kilgard.  See page 38.\n"
		"\n"
		"struct C2E1v_Output {\n"
		"	float4 position : POSITION;\n"
		"};\n"
		"\n"
		"C2E1v_Output C2E1v_green(float2 position : POSITION)\n"
		"{\n"
		"	C2E1v_Output OUT;\n"
		"\n"
		"	OUT.position = float4(position,0,1);\n"
		"\n"
		"	return OUT;\n"
		"}\n"
	);

	sge::cg::program::object vertex_program(
		sge::cg::program::from_string_parameters(
			cg_context,
			sge::cg::program::source_type::text,
			vertex_profile,
			sge::cg::program::source(
				vertex_shader_source
			),
			sge::cg::program::main_function(
				"C2E1v_green"
			),
			sys.renderer_device_core().cg_compile_options(
				cg_context,
				vertex_profile
			)
		)
	);

	sge::renderer::cg::loaded_program_unique_ptr const loaded_vertex_program(
		sys.renderer_device_core().load_cg_program(
			fcppt::make_ref(
				vertex_program
			)
		)
	);

	sge::cg::profile::object const pixel_profile(
		sys.renderer_device_core().create_cg_profile(
			sge::cg::profile::shader_type::pixel
		)
	);

	sge::cg::string const pixel_shader_source(
		"struct C3E3f_Output {\n"
		"	float4 color : COLOR;\n"
		"};\n"
		"C3E3f_Output\n"
		"C3E3f_simple()\n"
		"{\n"
		"	C3E3f_Output OUT;\n"
		"\n"
		"	OUT.color = float4(0,1,0,1);\n"
		"	return OUT;\n"
		"}\n"
	);

	sge::cg::program::object pixel_program(
		sge::cg::program::from_string_parameters(
			cg_context,
			sge::cg::program::source_type::text,
			pixel_profile,
			sge::cg::program::source(
				pixel_shader_source
			),
			sge::cg::program::main_function(
				"C3E3f_simple"
			),
			sys.renderer_device_core().cg_compile_options(
				cg_context,
				pixel_profile
			)
		)
	);

	sge::renderer::cg::loaded_program_unique_ptr const loaded_pixel_program(
		sys.renderer_device_core().load_cg_program(
			fcppt::make_ref(
				pixel_program
			)
		)
	);

	using
	pos3_type
	=
	sge::renderer::vf::pos<
		float,
		3
	>;

	using
	format_part
	=
	sge::renderer::vf::part<
		pos3_type
	>;

	using
	format
	=
	sge::renderer::vf::format<
		format_part
	>;

	sge::renderer::vertex::declaration_unique_ptr const vertex_declaration(
		sys.renderer_device_core().create_vertex_declaration(
			sge::renderer::vertex::declaration_parameters(
				sge::renderer::vf::dynamic::make_format<
					format
				>()
			)
		)
	);

	using
	vec3
	=
	pos3_type::packed_type;

	using
	vertex
	=
	sge::renderer::vf::vertex<
		format_part
	>;

	sge::renderer::vertex::buffer_unique_ptr const vertex_buffer(
		sge::renderer::vertex::create_buffer_from_vertices<
			format
		>(
			fcppt::make_ref(
				sys.renderer_device_core()
			),
			fcppt::make_cref(
				*vertex_declaration
			),
			sge::renderer::resource_flags_field::null(),
			fcppt::container::array::make(
				vertex{
					sge::renderer::vf::labels::pos{} =
						vec3(
							-1.F,
							1.F,
							0.F
						)
				},
				vertex{
					sge::renderer::vf::labels::pos{} =
						vec3(
							-1.F,
							-1.F,
							0.F
						)
				},
				vertex{
					sge::renderer::vf::labels::pos{} =
						vec3(
							1.F,
							1.F,
							0.F
						)
				}
			)
		)
	);

	auto const draw(
		[
			&loaded_pixel_program,
			&loaded_vertex_program,
			&sys,
			&vertex_buffer,
			&vertex_declaration
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

			scoped_block.get().clear(
				sge::renderer::clear::parameters()
				.back_buffer(
					sge::image::color::any::object{
						sge::image::color::predef::black()
					}
				)
			);

			sge::renderer::vertex::scoped_declaration_and_buffers const vb_context(
				fcppt::make_ref(
					scoped_block.get()
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

			sge::renderer::cg::scoped_program const scoped_vertex_program(
				fcppt::make_ref(
					scoped_block.get()
				),
				fcppt::make_cref(
					*loaded_vertex_program
				)
			);

			sge::renderer::cg::scoped_program const scoped_pixel_program(
				fcppt::make_ref(
					scoped_block.get()
				),
				fcppt::make_cref(
					*loaded_pixel_program
				)
			);

			scoped_block.get().render_nonindexed(
				sge::renderer::vertex::first(
					0u
				),
				sge::renderer::vertex::count(
					3u
				),
				sge::renderer::primitive_type::triangle_list
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
