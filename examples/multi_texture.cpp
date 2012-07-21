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


#include <sge/config/media_path.hpp>
#include <sge/image/capabilities_field.hpp>
#include <sge/image/colors.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/first_index.hpp>
#include <sge/renderer/first_vertex.hpp>
#include <sge/renderer/index_buffer.hpp>
#include <sge/renderer/index_buffer_scoped_ptr.hpp>
#include <sge/renderer/index_count.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/primitive_type.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/scoped_index_lock.hpp>
#include <sge/renderer/scoped_vertex_buffer.hpp>
#include <sge/renderer/scoped_vertex_declaration.hpp>
#include <sge/renderer/scoped_vertex_lock.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/vertex_buffer_scoped_ptr.hpp>
#include <sge/renderer/vertex_count.hpp>
#include <sge/renderer/vertex_declaration.hpp>
#include <sge/renderer/vertex_declaration_scoped_ptr.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/context/object.hpp>
#include <sge/renderer/context/scoped.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/index/format_16.hpp>
#include <sge/renderer/index/iterator.hpp>
#include <sge/renderer/index/view.hpp>
#include <sge/renderer/index/dynamic/make_format.hpp>
#include <sge/renderer/parameters/object.hpp>
#include <sge/renderer/parameters/vsync.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/texture/create_planar_from_path.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/planar_scoped_ptr.hpp>
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
#include <sge/systems/quit_on_escape.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/window.hpp>
#include <sge/viewport/center_on_resize.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/parameters.hpp>
#include <sge/window/system.hpp>
#include <sge/window/title.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context_fwd.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/math/dim/object_impl.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/signal/auto_connection.hpp>
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
	sge::window::dim const window_dim(
		1024,
		768
	);

	sge::systems::instance const sys(
		sge::systems::list()
		(
			sge::systems::window(
				sge::window::parameters(
					sge::window::title(
						FCPPT_TEXT("sge multi texture sprite example")
					),
					window_dim
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
				sge::viewport::center_on_resize(
					window_dim
				)
			)
		)
		(
			sge::systems::image2d(
				sge::image::capabilities_field::null(),
				sge::media::optional_extension_set(
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

	sge::renderer::texture::planar_scoped_ptr const texture1(
		sge::renderer::texture::create_planar_from_path(
			sge::config::media_path()
			/ FCPPT_TEXT("images")
			/ FCPPT_TEXT("cloudsquare.png"),
			sys.renderer(),
			sys.image_system(),
			sge::renderer::texture::mipmap::off(),
			sge::renderer::resource_flags_field::null()
		)
	);

	sge::renderer::texture::planar_scoped_ptr const texture2(
		sge::renderer::texture::create_planar_from_path(
			sge::config::media_path()
			/ FCPPT_TEXT("images")
			/ FCPPT_TEXT("grass.png"),
			sys.renderer(),
			sys.image_system(),
			sge::renderer::texture::mipmap::off(),
			sge::renderer::resource_flags_field::null()
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

	sge::renderer::vertex_declaration_scoped_ptr const vertex_declaration(
		sys.renderer().create_vertex_declaration(
			sge::renderer::vf::dynamic::make_format<
				vf_format
			>()
		)
	);

	sge::renderer::vertex_buffer_scoped_ptr const vertex_buffer(
		sys.renderer().create_vertex_buffer(
			*vertex_declaration,
			sge::renderer::vf::dynamic::make_part_index<
				vf_format,
				vf_format_part
			>(),
			sge::renderer::vertex_count(
				4u
			),
			sge::renderer::resource_flags_field::null()
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

	sge::renderer::index_buffer_scoped_ptr const index_buffer(
		sys.renderer().create_index_buffer(
			sge::renderer::index::dynamic::make_format<
				index_format
			>(),
			sge::renderer::index_count(
				6u
			),
			sge::renderer::resource_flags_field::null()
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

	fcppt::signal::scoped_connection const escape_connection(
		sge::systems::quit_on_escape(
			sys
		)
	);

	while(
		sys.window_system().poll()
	)
	{
		sge::renderer::context::scoped const scoped_block(
			sys.renderer(),
			sys.renderer().onscreen_target()
		);

		sge::renderer::scoped_vertex_declaration const vb_declaration_context(
			scoped_block.get(),
			*vertex_declaration
		);

		sge::renderer::scoped_vertex_buffer const vb_context(
			scoped_block.get(),
			*vertex_buffer
		);

		sge::renderer::texture::scoped const tex0_context(
			scoped_block.get(),
			*texture1,
			sge::renderer::texture::stage(0u)
		);

		sge::renderer::texture::scoped const tex1_context(
			scoped_block.get(),
			*texture2,
			sge::renderer::texture::stage(1u)
		);

		scoped_block.get().texture_stage_arg(
			sge::renderer::texture::stage(0u),
			sge::renderer::texture::stage_arg::color0,
			sge::renderer::texture::stage_arg_value::texture
		);

		scoped_block.get().texture_stage_op(
			sge::renderer::texture::stage(0u),
			sge::renderer::texture::stage_op::color,
			sge::renderer::texture::stage_op_value::arg0
		);

		scoped_block.get().texture_stage_arg(
			sge::renderer::texture::stage(1u),
			sge::renderer::texture::stage_arg::color0,
			sge::renderer::texture::stage_arg_value::previous
		);

		scoped_block.get().texture_stage_arg(
			sge::renderer::texture::stage(1u),
			sge::renderer::texture::stage_arg::color1,
			sge::renderer::texture::stage_arg_value::texture
		);

		scoped_block.get().texture_stage_op(
			sge::renderer::texture::stage(1u),
			sge::renderer::texture::stage_op::color,
			sge::renderer::texture::stage_op_value::modulate
		);

		scoped_block.get().clear(
			sge::renderer::clear::parameters()
			.back_buffer(
				sge::image::colors::black()
			)
		);

		scoped_block.get().render_indexed(
			*index_buffer,
			sge::renderer::first_vertex(
				0u
			),
			sge::renderer::vertex_count(
				vertex_buffer->size()
			),
			sge::renderer::primitive_type::triangle_list,
			sge::renderer::first_index(
				0u
			),
			sge::renderer::index_count(
				index_buffer->size()
			)
		);
	}

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
