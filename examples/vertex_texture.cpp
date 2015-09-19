/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/primitive_type.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/context/core.hpp>
#include <sge/renderer/context/scoped_core.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/display_mode/parameters.hpp>
#include <sge/renderer/display_mode/vsync.hpp>
#include <sge/renderer/index/buffer.hpp>
#include <sge/renderer/index/buffer_parameters.hpp>
#include <sge/renderer/index/buffer_unique_ptr.hpp>
#include <sge/renderer/index/count.hpp>
#include <sge/renderer/index/first.hpp>
#include <sge/renderer/index/format_16.hpp>
#include <sge/renderer/index/iterator.hpp>
#include <sge/renderer/index/scoped_lock.hpp>
#include <sge/renderer/index/view.hpp>
#include <sge/renderer/index/dynamic/make_format.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/texture/create_planar_from_path.hpp>
#include <sge/renderer/texture/emulate_srgb_from_caps.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/planar_unique_ptr.hpp>
#include <sge/renderer/texture/scoped.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
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
#include <sge/renderer/vf/format.hpp>
#include <sge/renderer/vf/index.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/part.hpp>
#include <sge/renderer/vf/pos.hpp>
#include <sge/renderer/vf/texpos.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/renderer/vf/view.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/renderer/vf/dynamic/make_part_index.hpp>
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
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/viewport/optional_resize_callback.hpp>
#include <sge/window/system.hpp>
#include <sge/window/title.hpp>
#include <awl/show_error.hpp>
#include <awl/show_error_narrow.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context_fwd.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
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
		boost::mpl::vector4<
			sge::systems::with_window,
			sge::systems::with_renderer<
				sge::systems::renderer_caps::core
			>,
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

//! [texture_vf_declaration]
	typedef sge::renderer::vf::pos<
		float,
		3
	> pos3_type;

	typedef sge::renderer::vf::texpos<
		float,
		2,
		sge::renderer::vf::index<
			0u
		>
	> texpos2_type;

	typedef sge::renderer::vf::part<
		boost::mpl::vector2<
			pos3_type,
			texpos2_type
		>
	> format_part;

	typedef sge::renderer::vf::format<
		boost::mpl::vector1<
			format_part
		>
	> format;
//! [texture_vf_declaration]

	sge::renderer::vertex::declaration_unique_ptr const vertex_declaration(
		sys.renderer_device_core().create_vertex_declaration(
			sge::renderer::vertex::declaration_parameters(
				sge::renderer::vf::dynamic::make_format<
					format
				>()
			)
		)
	);

	sge::renderer::vertex::buffer_unique_ptr const vertex_buffer(
		sys.renderer_device_core().create_vertex_buffer(
			sge::renderer::vertex::buffer_parameters(
				*vertex_declaration,
				sge::renderer::vf::dynamic::make_part_index<
					format,
					format_part
				>(),
				sge::renderer::vertex::count(
					4u
				),
				sge::renderer::resource_flags_field::null()
			)
		)
	);

	{
		sge::renderer::vertex::scoped_lock const vblock(
			*vertex_buffer,
			sge::renderer::lock_mode::writeonly
		);

		typedef sge::renderer::vf::view<
			format_part
		> vertex_view;

		vertex_view const vertices(
			vblock.value()
		);

// ![write_vertices]
		vertex_view::iterator vb_it(
			vertices.begin()
		);

		typedef pos3_type::packed_type vec3;

		typedef texpos2_type::packed_type vec2;

		(*vb_it).set<
			pos3_type
		>(
			vec3(-1.f, 1.f, 0.f)
		);

		(*vb_it).set<
			texpos2_type
		>(
			vec2(0.f, 0.f)
		);

		++vb_it;

		(*vb_it).set<
			pos3_type
		>(
			vec3(-1.f, -1.f, 0.f)
		);

		(*vb_it).set<
			texpos2_type
		>(
			vec2(0.f, 1.f)
		);

		++vb_it;

		(*vb_it).set<
			pos3_type
		>(
			vec3(1.f, 1.f, 0.f)
		);

		(*vb_it).set<
			texpos2_type
		>(
			vec2(1.f, 0.f)
		);

		++vb_it;

		(*vb_it).set<
			pos3_type
		>(
			vec3(1.f, -1.f, 0.f)
		);

		(*vb_it).set<
			texpos2_type
		>(
			vec2(1.f, 1.f)
		);
// ![write_vertices]
	}

	typedef sge::renderer::index::format_16 index_format;

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

		typedef sge::renderer::index::view<
			index_format
		> index_view;

		index_view const view(
			iblock.value()
		);

		index_view::iterator it(
			view.begin()
		);

		typedef index_view::value_type index_value_type;

		(*it++).set(static_cast<index_value_type>(0));
		(*it++).set(static_cast<index_value_type>(1));
		(*it++).set(static_cast<index_value_type>(2));
		(*it++).set(static_cast<index_value_type>(1));
		(*it++).set(static_cast<index_value_type>(3));
		(*it++).set(static_cast<index_value_type>(2));
	}

// ![load_texture]
	sge::renderer::texture::planar_unique_ptr const texture(
		sge::renderer::texture::create_planar_from_path(
			sge::config::media_path()
			/ FCPPT_TEXT("images")
			/ FCPPT_TEXT("grass.png"),
			sys.renderer_device_core(),
			sys.image_system(),
			sge::renderer::texture::mipmap::off(),
			sge::renderer::resource_flags_field::null(),
			sge::renderer::texture::emulate_srgb_from_caps(
				sys.renderer_device_core().caps()
			)
		)
	);
// ![load_texture]

	fcppt::signal::auto_connection const scoped_esc_connection(
		sge::systems::quit_on_escape(
			sys
		)
	);

	while(
		sys.window_system().poll()
	)
	{
		sge::renderer::context::scoped_core const scoped_block(
			sys.renderer_device_core(),
			sys.renderer_device_core().onscreen_target()
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
//! [render_block]
		sge::renderer::texture::scoped const tex_context(
			scoped_block.get(),
			*texture,
			sge::renderer::texture::stage(
				0u
			)
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
//! [render_block]
	}

	return
		sys.window_system().exit_code();
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
