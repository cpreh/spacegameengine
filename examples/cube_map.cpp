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

#include <sge/camera/perspective_projection_from_viewport.hpp>
#include <sge/camera/coordinate_system/identity.hpp>
#include <sge/camera/coordinate_system/object.hpp>
#include <sge/camera/first_person/object.hpp>
#include <sge/camera/first_person/parameters.hpp>
#include <sge/camera/matrix_conversion/world.hpp>
#include <sge/config/media_path.hpp>
#include <sge/image/colors.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/system.hpp>
#include <sge/image2d/algorithm/copy_and_convert.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/scoped_vertex_buffer.hpp>
#include <sge/renderer/scoped_vertex_declaration.hpp>
#include <sge/renderer/scoped_vertex_lock.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/vertex_buffer_scoped_ptr.hpp>
#include <sge/renderer/vertex_declaration.hpp>
#include <sge/renderer/vertex_declaration_scoped_ptr.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/color_buffer/scoped_surface_lock.hpp>
#include <sge/renderer/context/object.hpp>
#include <sge/renderer/context/scoped.hpp>
#include <sge/renderer/parameters/object.hpp>
#include <sge/renderer/pixel_format/object.hpp>
#include <sge/renderer/state/depth_func.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/scoped.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/texture/cube.hpp>
#include <sge/renderer/texture/cube_parameters.hpp>
#include <sge/renderer/texture/cube_scoped_ptr.hpp>
#include <sge/renderer/texture/scoped.hpp>
#include <sge/renderer/texture/mipmap/all_levels.hpp>
#include <sge/renderer/vf/format.hpp>
#include <sge/renderer/vf/index.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/normal.hpp>
#include <sge/renderer/vf/part.hpp>
#include <sge/renderer/vf/pos.hpp>
#include <sge/renderer/vf/texpos.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/renderer/vf/view.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/renderer/vf/dynamic/make_part_index.hpp>
#include <sge/systems/image2d.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/quit_on_escape.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/window.hpp>
#include <sge/timer/basic.hpp>
#include <sge/timer/elapsed_and_reset.hpp>
#include <sge/timer/parameters.hpp>
#include <sge/timer/clocks/standard.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/parameters.hpp>
#include <sge/window/system.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/foreach_enumerator.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/array_map.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/assign/make_array.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/array.hpp>
#include <fcppt/container/bitfield/object_impl.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/math/deg_to_rad.hpp>
#include <fcppt/math/dim/object_impl.hpp>
#include <fcppt/math/matrix/object_impl.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/signal/connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/chrono.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <example_main.hpp>
#include <exception>
#include <ostream>
#include <fcppt/config/external_end.hpp>


namespace
{
namespace vf
{
typedef
sge::renderer::vf::pos
<
	sge::renderer::scalar,
	3
>
pos;

typedef
sge::renderer::vf::texpos
<
	sge::renderer::scalar,
	3,
	sge::renderer::vf::index<0>
>
texpos;

typedef
sge::renderer::vf::normal
<
	sge::renderer::scalar
>
normal;

typedef
sge::renderer::vf::part
<
	boost::mpl::vector3
	<
		vf::pos,
		vf::normal,
		vf::texpos
	>
>
part;

typedef
sge::renderer::vf::format
<
	boost::mpl::vector1<vf::part>
>
format;
}

typedef
vf::pos::packed_type
pos_vector;

typedef
fcppt::container::array
<
	pos_vector,
	2u * 3u * 6u
>
pos_array;

sge::renderer::scalar
coord_to_texcoord(
	sge::renderer::scalar const _value)
{
	return
		static_cast<sge::renderer::scalar>(
			(_value + 1.f) / 2.f);
}

void
fill_geometry(
	sge::renderer::vertex_buffer &_vertex_buffer)
{
	pos_array const positions(
		fcppt::assign::make_array<pos_vector>
			// bottom 1
			(pos_vector(
				-1,-1,-1))
			(pos_vector(
				-1,-1,1))
			(pos_vector(
				1,-1,1))
			// bottom 2
			(pos_vector(
				1,-1,1))
			(pos_vector(
				1,-1,-1))
			(pos_vector(
				-1,-1,-1))
			// top 1
			(pos_vector(
				-1,1,-1))
			(pos_vector(
				1,1,-1))
			(pos_vector(
				1,1,1))
			// top 2
			(pos_vector(
				1,1,1))
			(pos_vector(
				-1,1,1))
			(pos_vector(
				-1,1,-1))
			// left 1
			(pos_vector(
				-1,-1,-1))
			(pos_vector(
				-1,1,-1))
			(pos_vector(
				-1,1,1))
			// left 2
			(pos_vector(
				-1,1,1))
			(pos_vector(
				-1,-1,1))
			(pos_vector(
				-1,-1,-1))
			// right 1
			(pos_vector(
				1,-1,-1))
			(pos_vector(
				1,-1,1))
			(pos_vector(
				1,1,1))
			// right 2
			(pos_vector(
				1,1,1))
			(pos_vector(
				1,1,-1))
			(pos_vector(
				1,-1,-1))
			// front 1
			(pos_vector(
				-1,-1,1))
			(pos_vector(
				-1,1,1))
			(pos_vector(
				1,1,1))
			// front 2
			(pos_vector(
				1,1,1))
			(pos_vector(
				1,-1,1))
			(pos_vector(
				-1,-1,1))
			// back 1
			(pos_vector(
				-1,-1,-1))
			(pos_vector(
				1,-1,-1))
			(pos_vector(
				1,1,-1))
			// back 2
			(pos_vector(
				1,1,-1))
			(pos_vector(
				-1,1,-1))
			(pos_vector(
				-1,-1,-1)));

	pos_array const normals(
		fcppt::assign::make_array<pos_vector>
			// bottom 1
			(pos_vector(
				0,-1,0))
			(pos_vector(
				0,-1,0))
			(pos_vector(
				0,-1,0))
			// bottom 2
			(pos_vector(
				0,-1,0))
			(pos_vector(
				0,-1,0))
			(pos_vector(
				0,-1,0))
			// top 1
			(pos_vector(
				0,1,0))
			(pos_vector(
				0,1,0))
			(pos_vector(
				0,1,0))
			// top 2
			(pos_vector(
				0,1,0))
			(pos_vector(
				0,1,0))
			(pos_vector(
				0,1,0))
			// left 1
			(pos_vector(
				-1,0,0))
			(pos_vector(
				-1,0,0))
			(pos_vector(
				-1,0,0))
			// left 2
			(pos_vector(
				-1,0,0))
			(pos_vector(
				-1,0,0))
			(pos_vector(
				-1,0,0))
			// right 1
			(pos_vector(
				1,0,0))
			(pos_vector(
				1,0,0))
			(pos_vector(
				1,0,0))
			// right 2
			(pos_vector(
				1,0,0))
			(pos_vector(
				1,0,0))
			(pos_vector(
				1,0,0))
			// front 1
			(pos_vector(
				0,0,-1))
			(pos_vector(
				0,0,-1))
			(pos_vector(
				0,0,-1))
			// front 2
			(pos_vector(
				0,0,-1))
			(pos_vector(
				0,0,-1))
			(pos_vector(
				0,0,-1))
			// back 1
			(pos_vector(
				0,0,1))
			(pos_vector(
				0,0,1))
			(pos_vector(
				0,0,1))
			// back 2
			(pos_vector(
				0,0,1))
			(pos_vector(
				0,0,1))
			(pos_vector(
				0,0,1)));

	sge::renderer::scoped_vertex_lock const vb_lock(
		_vertex_buffer,
		sge::renderer::lock_mode::writeonly);

	typedef
	sge::renderer::vf::view
	<
		vf::part
	>
	vf_view;

	vf_view const view(
		vb_lock.value());

	typedef
	vf_view::iterator
	vf_iterator;

	vf_iterator vb_it(
		view.begin());

	for(
		pos_array::const_iterator
			pos_it(
				positions.begin()),
			normal_it(
				normals.begin());
		pos_it != positions.end();
		++pos_it,++normal_it)
	{
		(*vb_it).set<vf::pos>(
			*pos_it);

		pos_vector const texpos(
			fcppt::algorithm::array_map<pos_vector>(
				*pos_it,
				coord_to_texcoord));

		(*vb_it).set<vf::normal>(
			*normal_it);

		(*vb_it++).set<vf::texpos>(
			texpos);
	}
}

fcppt::string const
cube_side_to_string(
	sge::renderer::texture::cube_side::type const _enum)
{
	switch(_enum)
	{
	case sge::renderer::texture::cube_side::front:
		return FCPPT_TEXT("front");
	case sge::renderer::texture::cube_side::back:
		return FCPPT_TEXT("back");
	case sge::renderer::texture::cube_side::left:
		return FCPPT_TEXT("left");
	case sge::renderer::texture::cube_side::right:
		return FCPPT_TEXT("right");
	case sge::renderer::texture::cube_side::top:
		return FCPPT_TEXT("top");
	case sge::renderer::texture::cube_side::bottom:
		return FCPPT_TEXT("bottom");
	case sge::renderer::texture::cube_side::size:
		break;
	}

	FCPPT_ASSERT_UNREACHABLE;
}

}

awl::main::exit_code const
example_main(
	awl::main::function_context const &)
try
{
	sge::systems::instance const sys(
		sge::systems::list()
		(sge::systems::window(
			sge::window::parameters(
				sge::window::title(
					FCPPT_TEXT("sge cube map example")),
				sge::window::dim(
					1024,
					768))))
		(sge::systems::renderer(
			sge::renderer::parameters::object(
				sge::renderer::pixel_format::object(
					sge::renderer::pixel_format::color::depth32,
					sge::renderer::pixel_format::depth_stencil::d16,
					sge::renderer::pixel_format::optional_multi_samples(),
					sge::renderer::pixel_format::srgb::no),
				sge::renderer::parameters::vsync::on,
				sge::renderer::display_mode::optional_object()),
			sge::viewport::fill_on_resize()))
		(sge::systems::image2d(
			sge::image::capabilities_field::null(),
			sge::media::optional_extension_set(
				fcppt::assign::make_container<sge::media::extension_set>(
					sge::media::extension(
						FCPPT_TEXT("png"))))))
		(sge::systems::input(
			sge::systems::input_helper_field(
				sge::systems::input_helper::keyboard_collector)
			| sge::systems::input_helper::mouse_collector,
			sge::systems::cursor_option_field(
				sge::systems::cursor_option::exclusive))));

	sge::renderer::texture::cube_scoped_ptr cube_map(
		sys.renderer().create_cube_texture(
			sge::renderer::texture::cube_parameters(
				128u,
				sge::image::color::format::rgba8,
				sge::renderer::texture::mipmap::all_levels(
					sge::renderer::texture::mipmap::auto_generate::yes),
				sge::renderer::resource_flags_field::null(),
				sge::renderer::texture::capabilities_field(
					sge::renderer::texture::capabilities::render_target))));

	FCPPT_FOREACH_ENUMERATOR(
		current_side,
		sge::renderer::texture::cube_side)
	{
		sge::renderer::color_buffer::scoped_surface_lock const lock(
			cube_map->level(
				current_side,
				sge::renderer::texture::mipmap::level(
					0u)),
			sge::renderer::lock_mode::writeonly);

		sge::image2d::algorithm::copy_and_convert(
			sys.image_system().load(
				sge::config::media_path() /
					FCPPT_TEXT("images") /
					FCPPT_TEXT("cube_faces") /
					(cube_side_to_string(
						current_side)+FCPPT_TEXT(".png")))->view(),
			lock.value(),
			sge::image::algorithm::may_overlap::no);
	}

	sge::renderer::vertex_declaration_scoped_ptr const vertex_declaration(
		sys.renderer().create_vertex_declaration(
			sge::renderer::vf::dynamic::make_format<vf::format>()));

	sge::renderer::vertex_buffer_scoped_ptr const vertex_buffer(
		sys.renderer().create_vertex_buffer(
			*vertex_declaration,
			sge::renderer::vf::dynamic::make_part_index
			<
				vf::format,
				vf::part
			>(),
			sge::renderer::vertex_count(
				pos_array::dim_wrapper::value),
			sge::renderer::resource_flags_field::null()));

	fill_geometry(
		*vertex_buffer);

	fcppt::signal::scoped_connection const input_connection(
		sge::systems::quit_on_escape(
			sys));

	sge::camera::first_person::object camera(
		sge::camera::first_person::parameters(
			sys.keyboard_collector(),
			sys.mouse_collector(),
			sge::camera::first_person::is_active(
				true),
			sge::camera::first_person::movement_speed(
				4.0f),
			sge::camera::coordinate_system::identity()));

	sge::camera::perspective_projection_from_viewport camera_viewport_connection(
		camera,
		sys.renderer(),
		sys.viewport_manager(),
		sge::renderer::projection::near(
			0.1f),
		sge::renderer::projection::far(
			1000.f),
		sge::renderer::projection::fov(
			fcppt::math::deg_to_rad(
				60.f)));

	typedef
	sge::timer::basic<sge::timer::clocks::standard>
	timer;

	timer frame_timer(
		timer::parameters(
			boost::chrono::seconds(
				1)));

	while(
		sys.window_system().poll())
	{
		camera.update(
			sge::timer::elapsed_and_reset<sge::camera::update_duration>(
				frame_timer));

		sge::renderer::context::scoped const scoped_block(
			sys.renderer(),
			sys.renderer().onscreen_target());

		sge::renderer::scoped_vertex_declaration const scoped_vd(
			scoped_block.get(),
			*vertex_declaration);

		sge::renderer::scoped_vertex_buffer const scoped_vb(
			scoped_block.get(),
			*vertex_buffer);

		sge::renderer::texture::scoped const scoped_texture(
			scoped_block.get(),
			*cube_map,
			sge::renderer::texture::stage(
				0u));


		sge::renderer::state::scoped const scoped_state(
			scoped_block.get(),
			sge::renderer::state::list
				(sge::renderer::state::depth_func::less));

		scoped_block.get().clear(
			sge::renderer::clear::parameters()
				.back_buffer(
					sge::image::colors::black())
				.depth_buffer(
					1.f));

		scoped_block.get().transform(
			sge::renderer::matrix_mode::world,
			sge::camera::matrix_conversion::world(
				camera.coordinate_system()));

		scoped_block.get().transform(
			sge::renderer::matrix_mode::projection,
			camera.projection_matrix().get());

		scoped_block.get().render_nonindexed(
			sge::renderer::first_vertex(
				0u),
			sge::renderer::vertex_count(
				vertex_buffer->size()),
			sge::renderer::primitive_type::triangle_list);
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
