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
#include <sge/camera/coordinate_system/scoped.hpp>
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
#include <sge/renderer/state/cull_mode.hpp>
#include <sge/renderer/state/depth_func.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/scoped.hpp>
#include <sge/renderer/target/base.hpp>
#include <sge/renderer/target/offscreen.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/texture/cube.hpp>
#include <sge/renderer/texture/cube_parameters.hpp>
#include <sge/renderer/texture/cube_scoped_ptr.hpp>
#include <sge/renderer/texture/scoped.hpp>
#include <sge/renderer/texture/filter/mipmap.hpp>
#include <sge/renderer/texture/filter/scoped.hpp>
#include <sge/renderer/texture/mipmap/all_levels.hpp>
#include <sge/systems/charconv.hpp>
#include <sge/scenic/scene/prototype.hpp>
#include <sge/scenic/scene/from_blender_file.hpp>
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
#include <sge/scenic/scene/manager.hpp>
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
#include <fcppt/move.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/assign/make_array.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/array.hpp>
#include <fcppt/container/bitfield/object_impl.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/math/deg_to_rad.hpp>
#include <fcppt/math/box/object_impl.hpp>
#include <fcppt/math/dim/object_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/matrix/object_impl.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/signal/connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/chrono.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <example_main.hpp>
#include <exception>
#include <ostream>
#include <fcppt/config/external_end.hpp>


namespace
{
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

class cube_map
{
FCPPT_NONCOPYABLE(
	cube_map);
public:
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

	cube_map(
		sge::renderer::device &,
		sge::image2d::system &);

	void
	render(
		sge::renderer::context::object &,
		sge::camera::base &);

	sge::renderer::target::base &
	target_for_side(
		sge::renderer::texture::cube_side::type);
private:
	typedef
	boost::ptr_map
	<
		sge::renderer::texture::cube_side::type,
		sge::renderer::target::base
	>
	target_map;

	sge::renderer::vertex_declaration_scoped_ptr vertex_declaration_;
	sge::renderer::vertex_buffer_scoped_ptr vertex_buffer_;
	sge::renderer::texture::cube_scoped_ptr texture_;
	target_map targets_;

	void
	fill_geometry();

	void
	fill_textures(
		sge::image2d::system &);

	void
	create_targets(
		sge::renderer::device &);
};

cube_map::cube_map(
	sge::renderer::device &_renderer,
	sge::image2d::system &_image_loader)
:
	vertex_declaration_(
		_renderer.create_vertex_declaration(
			sge::renderer::vf::dynamic::make_format<vf::format>())),
	vertex_buffer_(
		_renderer.create_vertex_buffer(
			*vertex_declaration_,
			sge::renderer::vf::dynamic::make_part_index
			<
				vf::format,
				vf::part
			>(),
			sge::renderer::vertex_count(
				pos_array::dim_wrapper::value),
			sge::renderer::resource_flags_field::null())),
	texture_(
		_renderer.create_cube_texture(
			sge::renderer::texture::cube_parameters(
				// Warning: hard-coded value
				128u,
				sge::image::color::format::srgba8,
				sge::renderer::texture::mipmap::all_levels(
					sge::renderer::texture::mipmap::auto_generate::yes),
				sge::renderer::resource_flags_field::null(),
				sge::renderer::texture::capabilities_field(
					sge::renderer::texture::capabilities::render_target)))),
	targets_()
{
	this->fill_geometry();
	this->fill_textures(
		_image_loader);
	this->create_targets(
		_renderer);
}

void
cube_map::create_targets(
	sge::renderer::device &_renderer)
{
	FCPPT_FOREACH_ENUMERATOR(
		current_side,
		sge::renderer::texture::cube_side)
	{
		sge::renderer::target::offscreen_unique_ptr new_target(
			_renderer.create_target());

		sge::renderer::texture::cube::color_buffer &cbuffer(
			texture_->level(
				current_side,
				sge::renderer::texture::mipmap::level(
					0u)));

		new_target->color_surface(
			sge::renderer::color_buffer::optional_surface_ref(
				cbuffer),
			sge::renderer::target::surface_index(
				0u));

		new_target->viewport(
			sge::renderer::target::viewport(
				sge::renderer::pixel_rect(
					sge::renderer::pixel_rect::vector::null(),
					fcppt::math::dim::structure_cast<sge::renderer::pixel_rect::dim>(
						cbuffer.size()))));

		fcppt::container::ptr::insert_unique_ptr_map(
			targets_,
			current_side,
			fcppt::move(
				new_target));
	}
}

void
cube_map::fill_textures(
	sge::image2d::system &_image_loader)
{
	FCPPT_FOREACH_ENUMERATOR(
		current_side,
		sge::renderer::texture::cube_side)
	{
		sge::renderer::color_buffer::scoped_surface_lock const lock(
			texture_->level(
				current_side,
				sge::renderer::texture::mipmap::level(
					0u)),
			sge::renderer::lock_mode::writeonly);

		sge::image2d::algorithm::copy_and_convert(
			_image_loader.load(
				sge::config::media_path() /
					FCPPT_TEXT("images") /
					FCPPT_TEXT("cube_faces") /
					(cube_side_to_string(
						current_side)+FCPPT_TEXT(".png")))->view(),
			lock.value(),
			sge::image::algorithm::may_overlap::no);
	}
}

void
cube_map::render(
	sge::renderer::context::object &_context,
	sge::camera::base &_camera)
{
	sge::renderer::scoped_vertex_declaration const scoped_vd(
		_context,
		*vertex_declaration_);

	sge::renderer::scoped_vertex_buffer const scoped_vb(
		_context,
		*vertex_buffer_);

	sge::renderer::texture::scoped const scoped_texture(
		_context,
		*texture_,
		sge::renderer::texture::stage(
			0u));

	sge::renderer::texture::filter::scoped const scoped_filter(
		_context,
		sge::renderer::texture::stage(
			0u),
		sge::renderer::texture::filter::mipmap());

	sge::renderer::state::scoped const scoped_state(
		_context,
		sge::renderer::state::list
			(sge::renderer::state::depth_func::less)
			(sge::renderer::state::cull_mode::clockwise));

	_context.transform(
		sge::renderer::matrix_mode::world,
		sge::camera::matrix_conversion::world(
			_camera.coordinate_system()));

	_context.transform(
		sge::renderer::matrix_mode::projection,
		_camera.projection_matrix().get());

	_context.render_nonindexed(
		sge::renderer::first_vertex(
			0u),
		sge::renderer::vertex_count(
			vertex_buffer_->size()),
		sge::renderer::primitive_type::triangle_list);
}

sge::renderer::target::base &
cube_map::target_for_side(
	sge::renderer::texture::cube_side::type const _side)
{
	return
		*(targets_.find(
			_side)->second);
}

void
cube_map::fill_geometry()
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
		*vertex_buffer_,
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
			sge::renderer::vector3(
				pos_it->x(),
				pos_it->y(),
				-pos_it->z()));

		(*vb_it).set<vf::normal>(
			*normal_it);

		(*vb_it++).set<vf::texpos>(
			texpos);
	}
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
		(sge::systems::charconv())
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

	cube_map cube(
		sys.renderer(),
		sys.image_system());

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

	fcppt::string const scene_name(
		FCPPT_TEXT("cube_map_example"));

	sge::scenic::scene::manager test_scene(
		sys.renderer(),
		sys.image_system(),
		sys.viewport_manager(),
		sys.charconv_system(),
		camera,
		sge::scenic::scene::from_blender_file(
			sge::config::media_path() / FCPPT_TEXT("scenes") / scene_name / FCPPT_TEXT("description.json"),
			sys.charconv_system()),
		sge::scenic::scene::manager::model_base_path(
			sge::config::media_path() / FCPPT_TEXT("scenes") / scene_name),
		sge::scenic::scene::manager::material_base_path(
			sge::config::media_path() / FCPPT_TEXT("scenes") / scene_name),
		sge::scenic::scene::manager::texture_base_path(
			sge::config::media_path() / FCPPT_TEXT("scenes") / scene_name));

	typedef
	sge::timer::basic<sge::timer::clocks::standard>
	timer;

	timer frame_timer(
		timer::parameters(
			boost::chrono::seconds(
				1)));

	typedef
	std::map
	<
		sge::renderer::texture::cube_side::type,
		sge::camera::coordinate_system::object
	>
	side_to_coordinate_system_map;

	side_to_coordinate_system_map side_to_coordinate_system;
	side_to_coordinate_system.insert(
		std::make_pair(
			sge::renderer::texture::cube_side::back,
			sge::camera::coordinate_system::object(
				sge::camera::coordinate_system::right(
					sge::renderer::vector3(1.0f,0.0f,0.0f)),
				sge::camera::coordinate_system::up(
					sge::renderer::vector3(0.0f,1.0f,0.0f)),
				sge::camera::coordinate_system::forward(
					sge::renderer::vector3(0.0f,0.0f,1.0f)),
				sge::camera::coordinate_system::position(
					sge::renderer::vector3::null()))));
	side_to_coordinate_system.insert(
		std::make_pair(
			sge::renderer::texture::cube_side::front,
			sge::camera::coordinate_system::object(
				sge::camera::coordinate_system::right(
					sge::renderer::vector3(1.0f,0.0f,0.0f)),
				sge::camera::coordinate_system::up(
					sge::renderer::vector3(0.0f,1.0f,0.0f)),
				sge::camera::coordinate_system::forward(
					sge::renderer::vector3(0.0f,0.0f,-1.0f)),
				sge::camera::coordinate_system::position(
					sge::renderer::vector3::null()))));
	side_to_coordinate_system.insert(
		std::make_pair(
			sge::renderer::texture::cube_side::left,
			sge::camera::coordinate_system::object(
				sge::camera::coordinate_system::right(
					sge::renderer::vector3(0.0f,0.0f,1.0f)),
				sge::camera::coordinate_system::up(
					sge::renderer::vector3(0.0f,1.0f,0.0f)),
				sge::camera::coordinate_system::forward(
					sge::renderer::vector3(-1.0f,0.0f,0.0f)),
				sge::camera::coordinate_system::position(
					sge::renderer::vector3::null()))));
	side_to_coordinate_system.insert(
		std::make_pair(
			sge::renderer::texture::cube_side::right,
			sge::camera::coordinate_system::object(
				sge::camera::coordinate_system::right(
					sge::renderer::vector3(0.0f,0.0f,-1.0f)),
				sge::camera::coordinate_system::up(
					sge::renderer::vector3(0.0f,1.0f,0.0f)),
				sge::camera::coordinate_system::forward(
					sge::renderer::vector3(1.0f,0.0f,0.0f)),
				sge::camera::coordinate_system::position(
					sge::renderer::vector3::null()))));

	while(
		sys.window_system().poll())
	{
		camera.update(
			sge::timer::elapsed_and_reset<sge::camera::update_duration>(
				frame_timer));

		for(
			side_to_coordinate_system_map::const_iterator to_coordinate =
				side_to_coordinate_system.begin();
			to_coordinate != side_to_coordinate_system.end();
			++to_coordinate)
		{
			sge::camera::coordinate_system::scoped scoped_coordinates(
				camera,
				to_coordinate->second);

			sge::renderer::context::scoped const scoped_block(
				sys.renderer(),
				cube.target_for_side(
					to_coordinate->first));

			scoped_block.get().clear(
				sge::renderer::clear::parameters()
					.back_buffer(
						sge::image::colors::black())
					.depth_buffer(
						1.f));

			test_scene.render(
				scoped_block.get());
		}


		sge::renderer::context::scoped const scoped_block(
			sys.renderer(),
			sys.renderer().onscreen_target());

		scoped_block.get().clear(
			sge::renderer::clear::parameters()
				.back_buffer(
					sge::image::colors::black())
				.depth_buffer(
					1.f));

		test_scene.render(
			scoped_block.get());


		cube.render(
			scoped_block.get(),
			camera);
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
