/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/plugin/manager.hpp>
#include <sge/plugin/plugin.hpp>
#include <sge/plugin/context.hpp>
#include <sge/model/plugin.hpp>
#include <sge/model/loader.hpp>
#include <sge/model/loader_ptr.hpp>
#include <sge/model/object.hpp>
#include <sge/input/system.hpp>
#include <sge/input/action.hpp>
#include <sge/renderer/vf/dynamic_format.hpp>
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
#include <sge/mainloop/catch_block.hpp>
#include <sge/config/media_path.hpp>
#include <sge/mainloop/dispatch.hpp>
#include <fcppt/io/cifstream.hpp>
#include <fcppt/math/matrix/perspective.hpp>
#include <fcppt/math/pi.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/text.hpp>
#include <boost/spirit/home/phoenix/core/reference.hpp>
#include <boost/spirit/home/phoenix/operator/self.hpp>
#include <fstream>

int main()
try
{
	sge::systems::instance sys(
		sge::systems::list()
		(sge::window::parameters(
			FCPPT_TEXT("sge animtest")
		))
		(sge::renderer::parameters(
			sge::renderer::display_mode(
				sge::renderer::screen_size( 1024,
					768),
				sge::renderer::bit_depth::depth32,
				sge::renderer::refresh_rate_dont_care),
			sge::renderer::depth_buffer::off,
			sge::renderer::stencil_buffer::off,
			sge::renderer::window_mode::windowed,
			sge::renderer::vsync::on,
			sge::renderer::no_multi_sampling
		))
		(sge::systems::parameterless::input)
		(sge::systems::parameterless::image)
	);

	sge::plugin::plugin<
		sge::model::loader
	>::ptr_type const  model_plugin(
		sys.plugin_manager().plugin<sge::model::loader>()
		.load()
	);

	sge::model::loader_ptr const loader(
		model_plugin->get()()
	);

	fcppt::io::cifstream ifs(
		sge::config::media_path() / FCPPT_TEXT("european_fnt_v2.md3"),
		std::ios_base::binary
	);

	sge::model::object_ptr const object(
		loader->load(
			ifs
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
			sge::renderer::index::format::i16,
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
			sge::config::media_path() / FCPPT_TEXT("european_fnt.tga"),
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
		sys.input_system()->register_callback(
			sge::input::action(
				sge::input::kc::key_escape,
				boost::phoenix::ref(running) = false
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
		sge::mainloop::dispatch();

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
SGE_MAINLOOP_CATCH_BLOCK
