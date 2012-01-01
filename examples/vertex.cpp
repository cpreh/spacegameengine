/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/image/colors.hpp>
#include <sge/image/color/bgra8_format.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/renderer/const_vertex_buffer_ref_container.hpp>
#include <sge/renderer/depth_stencil_buffer.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/first_vertex.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/nonindexed_primitive_type.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/scoped_vertex_declaration_and_buffers.hpp>
#include <sge/renderer/scoped_vertex_lock.hpp>
#include <sge/renderer/vertex_buffer_ptr.hpp>
#include <sge/renderer/vertex_count.hpp>
#include <sge/renderer/vertex_declaration_ptr.hpp>
#include <sge/renderer/visual_depth.hpp>
#include <sge/renderer/vsync.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/color.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/vf/color.hpp>
#include <sge/renderer/vf/format.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/part.hpp>
#include <sge/renderer/vf/pos.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/renderer/vf/view.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/renderer/vf/dynamic/make_part_index.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/input_helper.hpp>
#include <sge/systems/input_helper_field.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/running_to_false.hpp>
#include <sge/systems/window.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/parameters.hpp>
#include <sge/window/system.hpp>
#include <sge/window/title.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <ostream>
#include <fcppt/config/external_end.hpp>


int
main()
try
{
	sge::systems::instance const sys(
		sge::systems::list()
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
				sge::renderer::parameters(
					sge::renderer::visual_depth::depth32,
					sge::renderer::depth_stencil_buffer::off,
					sge::renderer::vsync::on,
					sge::renderer::no_multi_sampling
				),
				sge::viewport::fill_on_resize()
			)
		)
		(
			sge::systems::input(
				sge::systems::input_helper_field(
					sge::systems::input_helper::keyboard_collector
				),
				sge::systems::cursor_option_field::null()
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
	sge::renderer::vertex_declaration_ptr const vertex_declaration(
		sys.renderer().create_vertex_declaration(
			sge::renderer::vf::dynamic::make_format<
				format
			>()
		)
	);
//! [vertex_declaration]

//! [vertex_buffer]
	sge::renderer::vertex_buffer_ptr const vertex_buffer(
		sys.renderer().create_vertex_buffer(
			*vertex_declaration,
			sge::renderer::vf::dynamic::make_part_index<
				format,
				format_part
			>(),
			sge::renderer::vertex_count(
				3u
			),
			sge::renderer::resource_flags::none
		)
	);
//! [vertex_buffer]

//! [vblock_declaration]
	{
		sge::renderer::scoped_vertex_lock const vblock(
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
				sge::image::colors::cyan()
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
				sge::image::colors::yellow()
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
				sge::image::colors::magenta()
			)
		);
	}
//! [vertex_write_rest]

	bool running = true;

	fcppt::signal::scoped_connection const scoped_esc_connection(
		sys.keyboard_collector().key_callback(
			sge::input::keyboard::action(
				sge::input::keyboard::key_code::escape,
				sge::systems::running_to_false(
					running
				)
			)
		)
	);

//! [running_block]
	while(
		running
	)
	{
//! [running_block]
		sys.window_system().poll();

		sys.renderer().state(
			sge::renderer::state::list
				(sge::renderer::state::bool_::clear_back_buffer = true)
				(sge::renderer::state::color::back_buffer_clear_color
					= sge::image::colors::black()
			)
		);

//! [scoped_declaration]
		sge::renderer::scoped_vertex_declaration_and_buffers const vb_context(
			sys.renderer(),
			*vertex_declaration,
			fcppt::assign::make_container<
				sge::renderer::const_vertex_buffer_ref_container
			>(
				fcppt::cref(
					*vertex_buffer
				)
			)
		);
//! [scoped_declaration]

//! [scoped_block]
		sge::renderer::scoped_block const block(
			sys.renderer()
		);

		sys.renderer().render_nonindexed(
			sge::renderer::first_vertex(0),
			sge::renderer::vertex_count(3),
			sge::renderer::nonindexed_primitive_type::triangle
		);
	}
//! [scoped_block]
}
catch(
	fcppt::exception const &_error
)
{
	fcppt::io::cerr()
		<< _error.string()
		<< FCPPT_TEXT('\n');

	return EXIT_FAILURE;
}
catch(
	std::exception const &_error
)
{
	std::cerr
		<< _error.what()
		<< '\n';

	return EXIT_FAILURE;
}
