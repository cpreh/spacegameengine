/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/renderer/const_vertex_buffer_ref_container.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/scoped_vertex_declaration_and_buffers.hpp>
#include <sge/renderer/scoped_vertex_lock.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/vertex_count.hpp>
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
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/running_to_false.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/window/instance.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <ostream>
#include <fcppt/config/external_end.hpp>


int main()
try
{
	sge::systems::instance const sys(
		sge::systems::list()
		(
			sge::systems::window(
				sge::window::simple_parameters(
					FCPPT_TEXT("sge vertex planar example"),
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

	typedef sge::renderer::vf::pos<
		float,
		3
	> pos3_type;

	typedef sge::image::color::bgra8_format bgra8_format;

	typedef sge::renderer::vf::color<
		bgra8_format
	> color_type;

	typedef sge::renderer::vf::part<
		boost::mpl::vector1<
			pos3_type
		>
	> pos_format_part;

	typedef sge::renderer::vf::part<
		boost::mpl::vector1<
			color_type
		>
	> color_format_part;


	typedef sge::renderer::vf::format<
		boost::mpl::vector2<
			pos_format_part,
			color_format_part
		>
	> format;

	sge::renderer::vertex_declaration_ptr const vertex_declaration(
		sys.renderer().create_vertex_declaration(
			sge::renderer::vf::dynamic::make_format<
				format
			>()
		)
	);

	sge::renderer::vertex_count const num_vertices(
		3u
	);

	sge::renderer::vertex_buffer_ptr const vertex_buffer1(
		sys.renderer().create_vertex_buffer(
			*vertex_declaration,
			sge::renderer::vf::dynamic::make_part_index<
				format,
				pos_format_part
			>(),
			num_vertices,
			sge::renderer::resource_flags::none
		)
	);

	sge::renderer::vertex_buffer_ptr const vertex_buffer2(
		sys.renderer().create_vertex_buffer(
			*vertex_declaration,
			sge::renderer::vf::dynamic::make_part_index<
				format,
				color_format_part
			>(),
			num_vertices,
			sge::renderer::resource_flags::none
		)
	);

	{
		sge::renderer::scoped_vertex_lock const vblock(
			*vertex_buffer1,
			sge::renderer::lock_mode::writeonly
		);

		typedef sge::renderer::vf::view<
			pos_format_part
		> vertex_view;

		vertex_view const vertices(
			vblock.value()
		);

		vertex_view::iterator vb_it(
			vertices.begin()
		);

		typedef pos3_type::packed_type vec3;

		(*vb_it++).set<pos3_type>(
			vec3(-1.f, 1.f, 0.f)
		);

		(*vb_it++).set<pos3_type>(
			vec3(-1.f, -1.f, 0.f)
		);

		(*vb_it++).set<pos3_type>(
			vec3(1.f, 1.f, 0.f)
		);
	}

	{
		sge::renderer::scoped_vertex_lock const vblock(
			*vertex_buffer2,
			sge::renderer::lock_mode::writeonly
		);

		typedef sge::renderer::vf::view<
			color_format_part
		> vertex_view;

		vertex_view const vertices(
			vblock.value()
		);

		vertex_view::iterator vb_it(
			vertices.begin()
		);

		(*vb_it++).set<color_type>(
			sge::image::color::any::convert<
				bgra8_format
			>(
				sge::image::colors::cyan()
			)
		);

		(*vb_it++).set<color_type>(
			sge::image::color::any::convert<
				bgra8_format
			>(
				sge::image::colors::yellow()
			)
		);

		(*vb_it++).set<color_type>(
			sge::image::color::any::convert<
				bgra8_format
			>(
				sge::image::colors::magenta()
			)
		);
	}


	bool running = true;

	fcppt::signal::scoped_connection const cb(
		sys.keyboard_collector().key_callback(
			sge::input::keyboard::action(
				sge::input::keyboard::key_code::escape,
				sge::systems::running_to_false(
					running
				)
			)
		)
	);

	while(
		running
	)
	{
		sys.window().dispatch();

		sys.renderer().state(
			sge::renderer::state::list
				(sge::renderer::state::bool_::clear_back_buffer = true)
				(sge::renderer::state::color::back_buffer_clear_color
					= sge::image::colors::black()
			)
		);

		sge::renderer::scoped_vertex_declaration_and_buffers const vb_context(
			sys.renderer(),
			*vertex_declaration,
			fcppt::assign::make_container<
				sge::renderer::const_vertex_buffer_ref_container
			>(
				fcppt::cref(
					*vertex_buffer1
				)
			)(
				fcppt::cref(
					*vertex_buffer2
				)
			)
		);

		sge::renderer::scoped_block const block(
			sys.renderer()
		);

		sys.renderer().render_nonindexed(
			sge::renderer::first_vertex(
				0
			),
			num_vertices,
			sge::renderer::nonindexed_primitive_type::triangle
		);
	}
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
