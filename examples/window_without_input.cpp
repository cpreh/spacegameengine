/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/image/color/bgra8_format.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/primitive_type.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/context/core.hpp>
#include <sge/renderer/context/scoped_core.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/parameters/object.hpp>
#include <sge/renderer/parameters/vsync.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/vertex/buffer.hpp>
#include <sge/renderer/vertex/buffer_parameters.hpp>
#include <sge/renderer/vertex/buffer_scoped_ptr.hpp>
#include <sge/renderer/vertex/const_buffer_ref_container.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/declaration.hpp>
#include <sge/renderer/vertex/declaration_parameters.hpp>
#include <sge/renderer/vertex/declaration_scoped_ptr.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <sge/renderer/vertex/scoped_declaration_and_buffers.hpp>
#include <sge/renderer/vertex/scoped_lock.hpp>
#include <sge/renderer/vf/color.hpp>
#include <sge/renderer/vf/format.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/part.hpp>
#include <sge/renderer/vf/pos.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/renderer/vf/view.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/renderer/vf/dynamic/make_part_index.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/window.hpp>
#include <sge/systems/with_renderer.hpp>
#include <sge/systems/with_window.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/parameters.hpp>
#include <sge/window/system.hpp>
#include <sge/window/title.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context_fwd.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/math/dim/object_impl.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/signal/scoped_connection.hpp>
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
		boost::mpl::vector2<
			sge::systems::with_window,
			sge::systems::with_renderer<
				sge::systems::renderer_caps::core
			>
		>
	> const sys(
		sge::systems::make_list
		(
			sge::systems::window(
				sge::window::parameters(
					sge::window::title(
						FCPPT_TEXT("sge vertex example")
					),
					sge::window::dim(
						1024,
						768
					)
				)
			)
		)
		(
			sge::systems::renderer(
				sge::renderer::parameters::object(
					sge::renderer::pixel_format::object(
						sge::renderer::pixel_format::color::depth32,
						sge::renderer::pixel_format::depth_stencil::off,
						sge::renderer::pixel_format::optional_multi_samples(),
						sge::renderer::pixel_format::srgb::no
					),
					sge::renderer::parameters::vsync::on,
					sge::renderer::display_mode::optional_object()
				),
				sge::viewport::fill_on_resize()
			)
		)
	);

//! [position_declaration]
	typedef sge::renderer::vf::pos<
		float,
		3
	> pos3_type;
//! [position_declaration]

//! [color_declaration]
	typedef sge::renderer::vf::color<
		sge::image::color::bgra8_format
	> color_type;
//! [color_declaration]

//! [format_part_declaration]
	typedef sge::renderer::vf::part<
		boost::mpl::vector2<
			pos3_type,
			color_type
		>
	> format_part;
//! [format_part_declaration]

//! [format_declaration]
	typedef sge::renderer::vf::format<
		boost::mpl::vector1<
			format_part
		>
	> format;
//! [format_declaration]

//! [vertex_declaration]
	sge::renderer::vertex::declaration_scoped_ptr const vertex_declaration(
		sys.renderer_core().create_vertex_declaration(
			sge::renderer::vertex::declaration_parameters(
				sge::renderer::vf::dynamic::make_format<
					format
				>()
			)
		)
	);
//! [vertex_declaration]

//! [vertex_buffer]
	sge::renderer::vertex::buffer_scoped_ptr const vertex_buffer(
		sys.renderer_core().create_vertex_buffer(
			sge::renderer::vertex::buffer_parameters(
				*vertex_declaration,
				sge::renderer::vf::dynamic::make_part_index<
					format,
					format_part
				>(),
				sge::renderer::vertex::count(
					3u
				),
				sge::renderer::resource_flags_field::null()
			)
		)
	);
//! [vertex_buffer]

//! [vblock_declaration]
	{
		sge::renderer::vertex::scoped_lock const vblock(
			*vertex_buffer,
			sge::renderer::lock_mode::writeonly
		);
//! [vblock_declaration]

//! [vertex_view_declaration]
		typedef sge::renderer::vf::view<
			format_part
		> vertex_view;

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
		typedef pos3_type::packed_type vec3;

		(*vb_it).set<
			pos3_type
		>(
			vec3(-1.f, 1.f, 0.f)
		);
//! [vertex_write_pos_1]

//! [vertex_write_color_1]
		(*vb_it).set<
			color_type
		>(
			sge::image::color::any::convert<
				sge::image::color::bgra8_format
			>(
				sge::image::color::predef::cyan()
			)
		);
//! [vertex_write_color_1]

//! [vertex_write_rest]
		++vb_it;

		(*vb_it).set<
			pos3_type
		>(
			vec3(-1.f, -1.f, 0.f)
		);

		(*vb_it).set<
			color_type
		>(
			sge::image::color::any::convert<
				sge::image::color::bgra8_format
			>(
				sge::image::color::predef::yellow()
			)
		);

		++vb_it;

		(*vb_it).set<
			pos3_type
		>(
			vec3(1.f, 1.f, 0.f)
		);

		(*vb_it).set<
			color_type
		>(
			sge::image::color::any::convert<
				sge::image::color::bgra8_format
			>(
				sge::image::color::predef::magenta()
			)
		);
	}
//! [vertex_write_rest]

//! [running_block]
	while(
		sys.window_system().poll()
	)
	{
//! [running_block]
		sge::renderer::context::scoped_core const scoped_block(
			sys.renderer_core(),
			sys.renderer_core().onscreen_target()
		);

		scoped_block.get().clear(
			sge::renderer::clear::parameters()
			.back_buffer(
				sge::image::color::predef::black()
			)
		);

//! [scoped_declaration]
		sge::renderer::vertex::scoped_declaration_and_buffers const vb_context(
			scoped_block.get(),
			*vertex_declaration,
			sge::renderer::vertex::const_buffer_ref_container{
				fcppt::make_cref(
					*vertex_buffer
				)
			}
		);
//! [scoped_declaration]

//! [scoped_block]
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
//! [scoped_block]

	return
		sys.window_system().exit_code();
}
catch(
	fcppt::exception const &_error
)
{
	fcppt::io::cerr()
		<< _error.string()
		<< FCPPT_TEXT('\n');

	return awl::main::exit_failure();
}
catch(
	std::exception const &_error
)
{
	std::cerr
		<< _error.what()
		<< '\n';

	return awl::main::exit_failure();
}
