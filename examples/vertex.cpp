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


#include <sge/exception.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/running_to_false.hpp>
#include <sge/systems/viewport/fill_on_resize.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/renderer/vf/format.hpp>
#include <sge/renderer/vf/pos.hpp>
#include <sge/renderer/vf/color.hpp>
#include <sge/renderer/vf/view.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/scoped_vertex_buffer.hpp>
#include <sge/renderer/scoped_vertex_lock.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/image/color/rgba8_format.hpp>
#include <sge/image/colors.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/window/instance.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/text.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <ostream>
#include <exception>
#include <cstdlib>

int main()
try
{
	sge::systems::instance const sys(
		sge::systems::list()
		(
			sge::systems::window(
				sge::window::simple_parameters(
					FCPPT_TEXT("sge vertextest"),
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
					sge::renderer::depth_buffer::off,
					sge::renderer::stencil_buffer::off,
					sge::renderer::vsync::on,
					sge::renderer::no_multi_sampling
				),
				sge::systems::viewport::fill_on_resize()
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

	typedef sge::image::color::rgba8_format rgba8_format;

	typedef sge::renderer::vf::color<
		rgba8_format
	> color_type;

	typedef sge::renderer::vf::format<
		boost::mpl::vector2<
			pos3_type,
			color_type
		>
	> format;

	sge::renderer::device_ptr const rend(
		sys.renderer()
	);

	sge::renderer::vertex_buffer_ptr const vb(
		rend->create_vertex_buffer(
			sge::renderer::vf::dynamic::make_format<format>(),
			3,
			sge::renderer::resource_flags::none
		)
	);

	{
		sge::renderer::scoped_vertex_lock const vblock(
			vb,
			sge::renderer::lock_mode::writeonly
		);

		typedef sge::renderer::vf::view<
			format
		> vertex_view;

		vertex_view const vertices(
			vblock.value()
		);

		vertex_view::iterator vb_it(
			vertices.begin()
		);

		typedef pos3_type::packed_type vec3;

		(*vb_it).set<pos3_type>(
			vec3(-1.f, 1.f, 0.f)
		);

		(*vb_it++).set<color_type>(
			sge::image::color::any::convert<
				rgba8_format
			>(
				sge::image::colors::cyan()
			)
		);

		(*vb_it).set<pos3_type>(
			vec3(-1.f, -1.f, 0.f)
		);

		(*vb_it++).set<color_type>(
			sge::image::color::any::convert<
				rgba8_format
			>(
				sge::image::colors::yellow()
			)
		);

		(*vb_it).set<pos3_type>(
			vec3(1.f, 1.f, 0.f)
		);

		(*vb_it++).set<color_type>(
			sge::image::color::any::convert<
				rgba8_format
			>(
				sge::image::colors::magenta()
			)
		);
	}

	bool running = true;

	fcppt::signal::scoped_connection const cb(
		sys.keyboard_collector()->key_callback(
			sge::input::keyboard::action(
				sge::input::keyboard::key_code::escape,
				sge::systems::running_to_false(
					running
				)
			)
		)
	);

	rend->state(
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_backbuffer = true)
			(sge::renderer::state::color::clear_color
				= sge::image::colors::black()
		)
	);

	sge::renderer::scoped_vertex_buffer const vb_context(
		rend,
		vb
	);

	while(running)
	{
		sys.window()->dispatch();

		sge::renderer::scoped_block const block_(rend);

		rend->render(
			sge::renderer::first_vertex(0),
			sge::renderer::vertex_count(3),
			sge::renderer::nonindexed_primitive_type::triangle
		);
	}
}
catch(sge::exception const &e)
{
	fcppt::io::cerr << e.string() << FCPPT_TEXT('\n');
	return EXIT_FAILURE;
}
catch(std::exception const &e)
{
	fcppt::io::cerr << e.what() << FCPPT_TEXT('\n');
	return EXIT_FAILURE;
}
