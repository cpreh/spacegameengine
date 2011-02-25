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

#include <sge/camera/activation_state.hpp>
#include <sge/camera/identity_gizmo.hpp>
#include <sge/camera/object.hpp>
#include <sge/camera/parameters.hpp>
#include <sge/camera/projection/object.hpp>
#include <sge/camera/projection/update_perspective_from_viewport.hpp>
#include <sge/config/media_path.hpp>
#include <sge/image/colors.hpp>
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/collector.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/log/global.hpp>
#include <sge/renderer/depth_stencil_buffer.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/first_vertex.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/nonindexed_primitive_type.hpp>
#include <sge/systems/image_loader.hpp>
#include <sge/image/capabilities_field.hpp>
#include <sge/extension_set.hpp>
#include <sge/renderer/texture/planar_ptr.hpp>
#include <sge/renderer/texture/create_planar_from_view.hpp>
#include <sge/renderer/texture/address_mode2.hpp>
#include <sge/renderer/texture/address_mode.hpp>
#include <sge/renderer/texture/filter/linear.hpp>
#include <sge/image2d/multi_loader.hpp>
#include <sge/image2d/file.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/scoped_vertex_buffer.hpp>
#include <sge/renderer/scoped_vertex_declaration.hpp>
#include <sge/renderer/scoped_vertex_lock.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/color.hpp>
#include <sge/renderer/state/cull_mode.hpp>
#include <sge/renderer/state/depth_func.hpp>
#include <sge/renderer/state/draw_mode.hpp>
#include <sge/renderer/state/float.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/stencil_func.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/vertex_buffer_ptr.hpp>
#include <sge/renderer/vertex_buffer_ptr.hpp>
#include <sge/renderer/vertex_count.hpp>
#include <sge/renderer/vertex_declaration_ptr.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/renderer/vf/make_unspecified_tag.hpp>
#include <sge/renderer/vf/unspecified.hpp>
#include <sge/renderer/vf/vector.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <sge/renderer/vf/format.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/part.hpp>
#include <sge/renderer/vf/pos.hpp>
#include <sge/renderer/vf/texpos.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/renderer/vf/view.hpp>
#include <sge/renderer/visual_depth.hpp>
#include <sge/renderer/vsync.hpp>
#include <sge/shader/object.hpp>
#include <sge/shader/sampler_sequence.hpp>
#include <sge/shader/scoped.hpp>
#include <sge/shader/variable.hpp>
#include <sge/shader/variable_sequence.hpp>
#include <sge/shader/variable_type.hpp>
#include <sge/shader/vf_to_string.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/input_helper_field.hpp>
#include <sge/systems/input_helper.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/running_to_false.hpp>
#include <sge/systems/viewport/fill_on_resize.hpp>
#include <sge/systems/window.hpp>
#include <sge/time/second.hpp>
#include <sge/time/timer.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/instance.hpp>
#include <sge/window/simple_parameters.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/log/activate_levels.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/math/deg_to_rad.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/matrix/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/text.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/tr1/functional.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <ostream>

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
position;

typedef 
sge::renderer::vf::texpos
<
	sge::renderer::scalar,
	2
> 
texcoord;

namespace tags
{
SGE_RENDERER_VF_MAKE_UNSPECIFIED_TAG(vertex_normal)
}

typedef 
sge::renderer::vf::unspecified
<
	sge::renderer::vf::vector
	<
		sge::renderer::scalar,
		3
	>,
	tags::vertex_normal
> 
vertex_normal;

typedef 
sge::renderer::vf::part
<
	boost::mpl::vector3
	<
		position,
		texcoord,
		vertex_normal
	>
> 
format_part;

typedef 
sge::renderer::vf::format
<
	boost::mpl::vector1<format_part>
> 
format;

typedef
sge::renderer::vf::view<format_part>
format_part_view;
}

void
fill_vb_with_cube(
	sge::shader::object &shader,
	sge::renderer::vertex_buffer_ptr const vb)
{
	sge::shader::scoped scoped_shader(
		shader);

	sge::renderer::scoped_vertex_lock const vblock(
		vb,
		sge::renderer::lock_mode::writeonly);

	vf::format_part_view const vertices(
		vblock.value());

	vf::format_part_view::iterator vb_it(
		vertices.begin());

	typedef 
	vf::position::packed_type 
	position_vector;

	typedef 
	vf::vertex_normal::packed_type 
	vertex_normal_vector;

	typedef 
	vf::texcoord::packed_type 
	texcoord_vector;

	// bottom 1
	(*vb_it).set<vf::position>(
		position_vector(
			-1,-1,-1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			0,-1,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			0,0));
	(*vb_it).set<vf::position>(
		position_vector(
			-1,-1,1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			0,-1,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			0,1));
	(*vb_it).set<vf::position>(
		position_vector(
			1,-1,1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			0,-1,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			1,1));
	// bottom 2
	(*vb_it).set<vf::position>(
		position_vector(
			1,-1,1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			0,-1,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			1,1));
	(*vb_it).set<vf::position>(
		position_vector(
			1,-1,-1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			0,-1,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			1,0));
	(*vb_it).set<vf::position>(
		position_vector(
			-1,-1,-1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			0,-1,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			0,0));
	// top 1
	(*vb_it).set<vf::position>(
		position_vector(
			-1,1,-1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			0,1,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			0,0));
	(*vb_it).set<vf::position>(
		position_vector(
			1,1,-1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			0,1,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			0,1));
	(*vb_it).set<vf::position>(
		position_vector(
			1,1,1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			0,1,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			1,1));
	// top 2
	(*vb_it).set<vf::position>(
		position_vector(
			1,1,1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			0,1,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			1,1));
	(*vb_it).set<vf::position>(
		position_vector(
			-1,1,1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			0,1,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			1,0));
	(*vb_it).set<vf::position>(
		position_vector(
			-1,1,-1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			0,1,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			0,0));
	// left 1
	(*vb_it).set<vf::position>(
		position_vector(
			-1,-1,-1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			-1,0,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			0,0));
	(*vb_it).set<vf::position>(
		position_vector(
			-1,1,-1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			-1,0,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			0,1));
	(*vb_it).set<vf::position>(
		position_vector(
			-1,1,1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			-1,0,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			1,1));
	// left 2
	(*vb_it).set<vf::position>(
		position_vector(
			-1,1,1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			-1,0,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			1,1));
	(*vb_it).set<vf::position>(
		position_vector(
			-1,-1,1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			-1,0,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			1,0));
	(*vb_it).set<vf::position>(
		position_vector(
			-1,-1,-1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			-1,0,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			0,0));
	// right 1
	(*vb_it).set<vf::position>(
		position_vector(
			1,-1,-1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			1,0,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			0,0));
	(*vb_it).set<vf::position>(
		position_vector(
			1,-1,1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			1,0,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			0,1));
	(*vb_it).set<vf::position>(
		position_vector(
			1,1,1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			1,0,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			1,1));
	// right 2
	(*vb_it).set<vf::position>(
		position_vector(
			1,1,1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			1,0,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			1,1));
	(*vb_it).set<vf::position>(
		position_vector(
			1,1,-1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			1,0,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			1,0));
	(*vb_it).set<vf::position>(
		position_vector(
			1,-1,-1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			1,0,0));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			0,0));
	// front 1
	(*vb_it).set<vf::position>(
		position_vector(
			-1,-1,1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			0,0,1));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			0,0));
	(*vb_it).set<vf::position>(
		position_vector(
			-1,1,1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			0,0,1));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			0,1));
	(*vb_it).set<vf::position>(
		position_vector(
			1,1,1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			0,0,1));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			1,1));
	// front 2
	(*vb_it).set<vf::position>(
		position_vector(
			1,1,1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			0,0,1));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			1,1));
	(*vb_it).set<vf::position>(
		position_vector(
			1,-1,1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			0,0,1));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			1,0));
	(*vb_it).set<vf::position>(
		position_vector(
			-1,-1,1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			0,0,1));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			0,0));
	// back 1
	(*vb_it).set<vf::position>(
		position_vector(
			-1,-1,-1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			0,0,-1));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			0,0));
	(*vb_it).set<vf::position>(
		position_vector(
			1,-1,-1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			0,0,-1));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			0,1));
	(*vb_it).set<vf::position>(
		position_vector(
			1,1,-1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			0,0,-1));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			1,1));
	// back 1
	(*vb_it).set<vf::position>(
		position_vector(
			1,1,-1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			0,0,-1));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			1,1));
	(*vb_it).set<vf::position>(
		position_vector(
			-1,1,-1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			0,0,-1));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			1,0));
	(*vb_it).set<vf::position>(
		position_vector(
			-1,-1,-1));
	(*vb_it).set<vf::vertex_normal>(
		vertex_normal_vector(
			0,0,-1));
	(*vb_it++).set<vf::texcoord>(
		texcoord_vector(
			0,0));
}
}

int main()
try
{
	fcppt::log::activate_levels(
		sge::log::global(),
		fcppt::log::level::debug);

	sge::systems::instance sys(
		sge::systems::list()
			(sge::systems::window(
				sge::window::simple_parameters(
					FCPPT_TEXT("sge test for sge::shader::object"),
					sge::window::dim(1024,768))))
			(sge::systems::renderer(
				sge::renderer::parameters(
					sge::renderer::visual_depth::depth32,
					sge::renderer::depth_stencil_buffer::d24,
					sge::renderer::vsync::on,
					sge::renderer::no_multi_sampling),
				sge::systems::viewport::fill_on_resize()))
			(sge::systems::image_loader(
				sge::image::capabilities_field::null(),
				fcppt::assign::make_container<sge::extension_set>(
					FCPPT_TEXT("png"))))
			(sge::systems::input(
				sge::systems::input_helper_field(
					sge::systems::input_helper::keyboard_collector) | sge::systems::input_helper::mouse_collector,
				sge::systems::cursor_option_field(
					sge::systems::cursor_option::hide) | sge::systems::cursor_option::confine)));

	sge::renderer::texture::planar_ptr const normal_texture =
		sge::renderer::texture::create_planar_from_view(
			sys.renderer(),
			sys.image_loader().load(
				sge::config::media_path()/FCPPT_TEXT("normal_map.png"))->view(),
			sge::renderer::texture::filter::linear,
			sge::renderer::texture::address_mode2(
				sge::renderer::texture::address_mode::clamp),
			sge::renderer::resource_flags::none);

	bool running = 
		true;

	fcppt::signal::scoped_connection const cb(
		sys.keyboard_collector()->key_callback(
			sge::input::keyboard::action(
				sge::input::keyboard::key_code::escape,
				sge::systems::running_to_false(
					running))));

	sge::camera::object camera(
		sge::camera::parameters(
			sge::camera::projection::object(),
			// movementspeed
			static_cast<sge::renderer::scalar>(4.),
			// mousespeed
			static_cast<sge::renderer::scalar>(200.),
			// position
			sge::camera::identity_gizmo(),
			*sys.keyboard_collector(),
			*sys.mouse_collector(),
			sge::camera::activation_state::active));

	fcppt::signal::scoped_connection const viewport_connection(
		sys.manage_viewport_callback(
			std::tr1::bind(
				sge::camera::projection::update_perspective_from_viewport,
				std::tr1::placeholders::_1,
				std::tr1::ref(
					camera),
				// fov
				static_cast<sge::renderer::scalar>(
					fcppt::math::deg_to_rad(
						90.)),
				// near
				static_cast<sge::renderer::scalar>(
					0.1),
				// far
				static_cast<sge::renderer::scalar>(
					1000.))));

	sge::shader::object shader(
		sys.renderer(),
		sge::config::media_path()/FCPPT_TEXT("shaders")/FCPPT_TEXT("cube_vertex.glsl"),
		sge::config::media_path()/FCPPT_TEXT("shaders")/FCPPT_TEXT("cube_fragment.glsl"),
		sge::shader::vf_to_string<vf::format>(),
		fcppt::assign::make_container<sge::shader::variable_sequence>
			(sge::shader::variable(
				"mvp",
				sge::shader::variable_type::uniform,
				sge::renderer::matrix4()))
			/*
			(sge::shader::variable(
				"mv",
				sge::shader::variable_type::uniform,
				sge::renderer::matrix4()))*/
			(sge::shader::variable(
				"light_position",
				sge::shader::variable_type::const_,
				sge::renderer::vector3(
					3,
					4,
					5))),
		fcppt::assign::make_container<sge::shader::sampler_sequence>
			(sge::shader::sampler(
				"normal_texture",
				normal_texture)));

	sge::renderer::vertex_declaration_ptr const vertex_declaration(
		sys.renderer()->create_vertex_declaration(
			sge::renderer::vf::dynamic::make_format<vf::format>()));

	sge::renderer::vertex_buffer_ptr const vb(
		sys.renderer()->create_vertex_buffer(
			vertex_declaration,
			sge::renderer::vf::dynamic::part_index(0u),
			// 6 sides, 2 triangles per side, 3 vertices (we don't use an
			// index buffer - overkill)
			6 * 2 * 3,
			sge::renderer::resource_flags::none));

	fill_vb_with_cube(
		shader,
		vb);

	sys.renderer()->state(
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_backbuffer = true)
			(sge::renderer::state::bool_::clear_zbuffer = true)
			(sge::renderer::state::bool_::enable_alpha_blending = false)
			(sge::renderer::state::cull_mode::off)
			(sge::renderer::state::depth_func::less)
			(sge::renderer::state::draw_mode::fill)
			(sge::renderer::state::float_::zbuffer_clear_val = 1.f)
			(sge::renderer::state::stencil_func::off)
			(sge::renderer::state::color::clear_color = sge::image::colors::black()));

	sge::time::timer frame_timer(
		sge::time::second(1));

	sge::shader::scoped scoped_shader(
		shader);

	sge::renderer::scoped_vertex_declaration const vb_declaration_context(
		sys.renderer(),
		vertex_declaration);

	sge::renderer::scoped_vertex_buffer const vb_context(
		sys.renderer(),
		vb);

	while(running)
	{
		sys.window()->dispatch();

		camera.update(
			frame_timer.reset());

		sge::renderer::scoped_block const block_(
			sys.renderer());

		shader.update_uniform(
			"mvp",
			camera.mvp());

		/*
		shader.update_uniform(
			"mv",
			camera.world());
		*/

		sys.renderer()->render(
			sge::renderer::first_vertex(0),
			sge::renderer::vertex_count(
				vb->size()),
			sge::renderer::nonindexed_primitive_type::triangle);
	}
}
catch(fcppt::exception const &e)
{
	fcppt::io::cerr << e.string() << FCPPT_TEXT('\n');
	return EXIT_FAILURE;
}
catch(std::exception const &e)
{
	std::cerr << e.what() << FCPPT_TEXT('\n');
	return EXIT_FAILURE;
}
