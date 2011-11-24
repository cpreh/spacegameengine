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


#include <sge/config/media_path.hpp>
#include <sge/image/capabilities_field.hpp>
#include <sge/image/colors.hpp>
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/renderer/depth_stencil_buffer.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/first_index.hpp>
#include <sge/renderer/first_vertex.hpp>
#include <sge/renderer/index_buffer_ptr.hpp>
#include <sge/renderer/index_count.hpp>
#include <sge/renderer/indexed_primitive_type.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/primitive_count.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/scoped_index_lock.hpp>
#include <sge/renderer/scoped_vertex_buffer.hpp>
#include <sge/renderer/scoped_vertex_declaration.hpp>
#include <sge/renderer/scoped_vertex_lock.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/vertex_buffer_ptr.hpp>
#include <sge/renderer/vertex_count.hpp>
#include <sge/renderer/vertex_declaration_ptr.hpp>
#include <sge/renderer/visual_depth.hpp>
#include <sge/renderer/vsync.hpp>
#include <sge/renderer/index/format_16.hpp>
#include <sge/renderer/index/iterator.hpp>
#include <sge/renderer/index/view.hpp>
#include <sge/renderer/index/dynamic/make_format.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/color.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/scoped.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/texture/address_mode.hpp>
#include <sge/renderer/texture/address_mode2.hpp>
#include <sge/renderer/texture/create_planar_from_path.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/planar_ptr.hpp>
#include <sge/renderer/texture/scoped.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <sge/renderer/texture/stage_arg.hpp>
#include <sge/renderer/texture/stage_arg_value.hpp>
#include <sge/renderer/texture/stage_op.hpp>
#include <sge/renderer/texture/stage_op_value.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
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
#include <sge/systems/input_helper.hpp>
#include <sge/systems/input_helper_field.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/running_to_false.hpp>
#include <sge/systems/window.hpp>
#include <sge/viewport/center_on_resize.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/instance.hpp>
#include <sge/window/simple_parameters.hpp>
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
	sge::window::dim const window_dim(
		1024,
		768
	);

	sge::systems::instance const sys(
		sge::systems::list()
		(
			sge::systems::window(
				sge::window::simple_parameters(
					FCPPT_TEXT("sge multi texture sprite example"),
					window_dim
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
				sge::viewport::center_on_resize(
					window_dim
				)
			)
		)
		(
			sge::systems::image2d(
				sge::image::capabilities_field::null(),
				fcppt::assign::make_container<
					sge::media::extension_set
				>
				(
					sge::media::extension(
						FCPPT_TEXT("png")
					)
				)
			)
		)
		(
			sge::systems::input(
				sge::systems::input_helper_field(
					sge::systems::input_helper::keyboard_collector
				),
				sge::systems::cursor_option_field()
			)
		)
	);

	sge::renderer::texture::planar_ptr const texture1(
		sge::renderer::texture::create_planar_from_path(
			sge::config::media_path()
			/ FCPPT_TEXT("images")
			/ FCPPT_TEXT("cloudsquare.png"),
			sys.renderer(),
			sys.image_system(),
			sge::renderer::texture::mipmap::off(),
			sge::renderer::texture::address_mode2(
				sge::renderer::texture::address_mode::clamp
			),
			sge::renderer::resource_flags::none
		)
	);

	sge::renderer::texture::planar_ptr const texture2(
		sge::renderer::texture::create_planar_from_path(
			sge::config::media_path()
			/ FCPPT_TEXT("images")
			/ FCPPT_TEXT("grass.png"),
			sys.renderer(),
			sys.image_system(),
			sge::renderer::texture::mipmap::off(),
			sge::renderer::texture::address_mode2(
				sge::renderer::texture::address_mode::clamp
			),
			sge::renderer::resource_flags::none
		)
	);

	typedef sge::renderer::vf::pos<
		float,
		3
	> vf_pos;

	typedef sge::renderer::vf::texpos<
		float,
		2,
		sge::renderer::vf::index<
			0
		>
	> vf_texpos0;

	typedef sge::renderer::vf::texpos<
		float,
		2,
		sge::renderer::vf::index<
			1
		>
	> vf_texpos1;

	typedef sge::renderer::vf::part<
		boost::mpl::vector3<
			vf_pos,
			vf_texpos0,
			vf_texpos1
		>
	> vf_format_part;

	typedef sge::renderer::vf::format<
		boost::mpl::vector1<
			vf_format_part
		>
	> vf_format;

	sge::renderer::vertex_declaration_ptr const vertex_declaration(
		sys.renderer().create_vertex_declaration(
			sge::renderer::vf::dynamic::make_format<
				vf_format
			>()
		)
	);

	sge::renderer::vertex_buffer_ptr const vertex_buffer(
		sys.renderer().create_vertex_buffer(
			*vertex_declaration,
			sge::renderer::vf::dynamic::make_part_index<
				vf_format,
				vf_format_part
			>(),
			sge::renderer::vertex_count(
				4u
			),
			sge::renderer::resource_flags::none
		)
	);

	{
		sge::renderer::scoped_vertex_lock const vblock(
			*vertex_buffer,
			sge::renderer::lock_mode::writeonly
		);

		typedef sge::renderer::vf::view<
			vf_format_part
		> vertex_view;

		vertex_view const vertices(
			vblock.value()
		);

		vertex_view::iterator vb_it(
			vertices.begin()
		);

		typedef vf_pos::packed_type pos;

		typedef vf_texpos0::packed_type texpos0;

		typedef vf_texpos1::packed_type texpos1;

		// top left
		(*vb_it).set<
			vf_pos
		>(
			pos(-1.f, 1.f, 0.f)
		);

		(*vb_it).set<
			vf_texpos0
		>(
			texpos0(0.f, 0.f)
		);

		(*vb_it++).set<
			vf_texpos1
		>(
			texpos1(0.f, 0.f)
		);

		// bottom left
		(*vb_it).set<
			vf_pos
		>(
			pos(-1.f, -1.f, 0.f)
		);

		(*vb_it).set<
			vf_texpos0
		>(
			texpos0(0.f, 1.f)
		);

		(*vb_it++).set<
			vf_texpos1
		>(
			texpos1(0.f, 1.f)
		);

		// top right
		(*vb_it).set<
			vf_pos
		>(
			pos(1.f, 1.f, 0.f)
		);

		(*vb_it).set<
			vf_texpos0
		>(
			texpos0(1.f, 0.f)
		);

		(*vb_it++).set<
			vf_texpos1
		>(
			texpos1(1.f, 0.f)
		);

		// bottom right
		(*vb_it).set<
			vf_pos
		>(
			pos(1.f, -1.f, 0.f)
		);

		(*vb_it).set<
			vf_texpos0
		>(
			texpos0(1.f, 1.f)
		);

		(*vb_it++).set<
			vf_texpos1
		>(
			texpos1(1.f, 1.f)
		);
	}

	typedef sge::renderer::index::format_16 index_format;

	sge::renderer::index_buffer_ptr const index_buffer(
		sys.renderer().create_index_buffer(
			sge::renderer::index::dynamic::make_format<
				index_format
			>(),
			sge::renderer::index_count(
				6u
			),
			sge::renderer::resource_flags::none
		)
	);

	{
		sge::renderer::scoped_index_lock const iblock(
			*index_buffer,
			sge::renderer::lock_mode::writeonly
		);

		typedef sge::renderer::index::view<
			index_format
		> index_view;

		index_view const indices(
			iblock.value()
		);

		typedef index_view::iterator index_iterator;

		index_iterator ib_it(
			indices.begin()
		);

		(*ib_it++).set(0);
		(*ib_it++).set(1);
		(*ib_it++).set(2);
		(*ib_it++).set(2);
		(*ib_it++).set(3);
		(*ib_it++).set(1);
	}

	bool running = true;

	fcppt::signal::scoped_connection const escape_connection(
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

		sge::renderer::scoped_vertex_declaration const vb_declaration_context(
			sys.renderer(),
			*vertex_declaration
		);

		sge::renderer::scoped_vertex_buffer const vb_context(
			sys.renderer(),
			*vertex_buffer
		);

		sge::renderer::texture::scoped const tex0_context(
			sys.renderer(),
			*texture1,
			sge::renderer::texture::stage(0u)
		);

		sge::renderer::texture::scoped const tex1_context(
			sys.renderer(),
			*texture2,
			sge::renderer::texture::stage(1u)
		);

		sge::renderer::state::scoped const scoped_state(
			sys.renderer(),
			sge::renderer::state::list(
				sge::renderer::state::bool_::clear_back_buffer = true
			)(
				sge::renderer::state::color::back_buffer_clear_color =
					sge::image::colors::black()
			)
		);

		sys.renderer().texture_stage_arg(
			sge::renderer::texture::stage(0u),
			sge::renderer::texture::stage_arg::color0,
			sge::renderer::texture::stage_arg_value::texture
		);

		sys.renderer().texture_stage_op(
			sge::renderer::texture::stage(0u),
			sge::renderer::texture::stage_op::color,
			sge::renderer::texture::stage_op_value::arg0
		);

		sys.renderer().texture_stage_arg(
			sge::renderer::texture::stage(1u),
			sge::renderer::texture::stage_arg::color0,
			sge::renderer::texture::stage_arg_value::previous
		);

		sys.renderer().texture_stage_arg(
			sge::renderer::texture::stage(1u),
			sge::renderer::texture::stage_arg::color1,
			sge::renderer::texture::stage_arg_value::texture
		);

		sys.renderer().texture_stage_op(
			sge::renderer::texture::stage(1u),
			sge::renderer::texture::stage_op::color,
			sge::renderer::texture::stage_op_value::modulate
		);

		sge::renderer::scoped_block const block(
			sys.renderer()
		);

		sys.renderer().render_indexed(
			*index_buffer,
			sge::renderer::first_vertex(
				0u
			),
			sge::renderer::vertex_count(
				vertex_buffer->size()
			),
			sge::renderer::indexed_primitive_type::triangle,
			sge::renderer::primitive_count(
				2u
			),
			sge::renderer::first_index(
				0u
			)
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
