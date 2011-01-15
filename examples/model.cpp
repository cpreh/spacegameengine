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


#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/running_to_false.hpp>
#include <sge/systems/viewport/manage_resize.hpp>
#include <sge/model/loader.hpp>
#include <sge/model/loader_ptr.hpp>
#include <sge/model/object.hpp>
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/renderer/vf/dynamic/format.hpp>
#include <sge/renderer/filter/linear.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/index_buffer.hpp>
#include <sge/renderer/aspect.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/texture.hpp>
#include <sge/renderer/scoped_vertex_buffer.hpp>
#include <sge/renderer/scoped_vertex_lock.hpp>
#include <sge/renderer/scoped_index_lock.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/refresh_rate_dont_care.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/image/create_texture.hpp>
#include <sge/config/media_path.hpp>
#include <sge/window/instance.hpp>
#include <sge/extension_set.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/math/matrix/perspective.hpp>
#include <fcppt/math/pi.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/text.hpp>
#include <exception>
#include <ios>
#include <iostream>
#include <ostream>
#include <cstdlib>

int main()
try
{
	sge::systems::instance sys(
		sge::systems::list()
		(
			sge::systems::window(
				sge::renderer::window_parameters(
					FCPPT_TEXT("sge modeltest")
				)
			)
		)
		(
			sge::systems::renderer(
				sge::renderer::parameters(
					sge::renderer::display_mode(
						sge::renderer::screen_size(
							1024,
							768
						),
						sge::renderer::bit_depth::depth32,
						sge::renderer::refresh_rate_dont_care
					),
					sge::renderer::depth_buffer::off,
					sge::renderer::stencil_buffer::off,
					sge::renderer::window_mode::windowed,
					sge::renderer::vsync::on,
					sge::renderer::no_multi_sampling
				),
				sge::systems::viewport::manage_resize()
			)
		)
		(
			sge::systems::input(
				sge::systems::input_helper_field(
					sge::systems::input_helper::keyboard_collector
				),
				sge::systems::cursor_grab::off
			)
		)
		(
			sge::systems::image_loader(
				sge::image::capabilities_field::null(),
				fcppt::assign::make_container<
					sge::extension_set
				>(
					FCPPT_TEXT("png")
				)
			)
		)
		(
			sge::systems::parameterless::md3_loader
		)
	);

	sge::model::loader_ptr const loader(
		sys.md3_loader()
	);

	sge::model::object_ptr const object(
		loader->load(
			sge::config::media_path()
			/ FCPPT_TEXT("european_fnt_v2.md3")
		)
	);

	sge::renderer::vertex_buffer_ptr const vb(
		sys.renderer()->create_vertex_buffer(
			object->format(),
			object->vertices(),
			sge::renderer::resource_flags::none
		)
	);

	sge::renderer::index_buffer_ptr const ib(
		sys.renderer()->create_index_buffer(
			sge::renderer::index::dynamic::format::i16,
			object->indices(),
			sge::renderer::resource_flags::none
		)
	);

	object->copy_vertices(
		sge::renderer::scoped_vertex_lock(
			vb,
			sge::renderer::lock_mode::writeonly
		).value()
	);

	object->copy_indices(
		sge::renderer::scoped_index_lock(
			ib,
			sge::renderer::lock_mode::writeonly
		).value() 
	); 

	sge::renderer::texture_ptr const tex(
		sge::image::create_texture(
			sge::config::media_path() / FCPPT_TEXT("european_fnt.png"),
			sys.renderer(),
			sys.image_loader(),
			sge::renderer::filter::linear,
			sge::renderer::resource_flags::none
		)
	);

	sys.renderer()->texture(
		tex
	);

	sys.renderer()->state(
		sge::renderer::state::list
			(sge::renderer::state::cull_mode::off)

	);

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

	typedef float unit;

	sys.renderer()->transform(
		sge::renderer::matrix_mode::projection,
		fcppt::math::matrix::perspective<unit>(
			sge::renderer::aspect<unit>(
				sys.renderer()->screen_size()
			),
			fcppt::math::pi<unit>() / static_cast<unit>(4),
			-100.f,
			100.f
		)
	);

	sge::renderer::scoped_vertex_buffer const vb_context(
		sys.renderer(),
		vb
	);

	while(running)
	{
		sys.window()->dispatch();

		sge::renderer::scoped_block const block_(
			sys.renderer()
		);

		sys.renderer()->render(
			ib,
			sge::renderer::first_vertex(0),
			sge::renderer::vertex_count(vb->size()),
			sge::renderer::indexed_primitive_type::triangle,
			sge::renderer::primitive_count(ib->size() / 3),
			sge::renderer::first_index(0)
		);
	}
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
