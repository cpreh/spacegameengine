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


#include <sge/all_extensions.hpp>
#include <sge/camera/object.hpp>
#include <sge/camera/movement_speed.hpp>
#include <sge/camera/rotation_speed.hpp>
#include <sge/camera/parameters.hpp>
#include <sge/camera/projection/object.hpp>
#include <sge/camera/projection/update_perspective_from_viewport.hpp>
#include <sge/camera/duration.hpp>
#include <sge/exception.hpp>
#include <sge/image/capabilities_field.hpp>
#include <sge/image/colors.hpp>
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/log/global.hpp>
#include <sge/model/obj/loader_ptr.hpp>
#include <sge/model/obj/face_sequence.hpp>
#include <sge/model/obj/instance_ptr.hpp>
#include <sge/model/obj/instance.hpp>
#include <sge/model/obj/loader.hpp>
#include <sge/model/obj/loader.hpp>
#include <sge/model/obj/create.hpp>
#include <sge/model/obj/vb_converter/roles/position.hpp>
#include <sge/model/obj/vb_converter/roles/texcoord.hpp>
#include <sge/model/obj/vb_converter/roles/normal.hpp>
#include <sge/model/obj/vb_converter/convert.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/fov.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/renderer/depth_stencil_buffer.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/first_vertex.hpp>
#include <sge/renderer/light/index.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/nonindexed_primitive_type.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/scoped_vertex_declaration.hpp>
#include <sge/renderer/scoped_vertex_buffer.hpp>
#include <sge/renderer/scoped_vertex_lock.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/color.hpp>
#include <sge/renderer/state/cull_mode.hpp>
#include <sge/renderer/state/depth_func.hpp>
#include <sge/renderer/state/draw_mode.hpp>
#include <sge/renderer/state/float.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/scoped.hpp>
#include <sge/renderer/state/stencil_func.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/texture/address_mode2.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/scoped.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/renderer/texture/address_mode.hpp>
#include <sge/renderer/texture/create_planar_from_path.hpp>
#include <sge/renderer/texture/filter/linear.hpp>
#include <sge/renderer/texture/planar_ptr.hpp>
#include <sge/renderer/vertex_buffer_ptr.hpp>
#include <sge/renderer/vertex_count.hpp>
#include <sge/renderer/vertex_declaration_fwd.hpp>
#include <sge/renderer/vertex_declaration_ptr.hpp>
#include <sge/renderer/vf/format.hpp>
#include <sge/renderer/vf/normal.hpp>
#include <sge/renderer/vf/part.hpp>
#include <sge/renderer/vf/pos.hpp>
#include <sge/renderer/vf/texpos.hpp>
#include <sge/renderer/viewport_size.hpp>
#include <sge/renderer/visual_depth.hpp>
#include <sge/renderer/stage.hpp>
#include <sge/renderer/vsync.hpp>
#include <sge/timer/basic.hpp>
#include <sge/timer/elapsed_and_reset.hpp>
#include <sge/timer/parameters.hpp>
#include <sge/timer/clocks/standard.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/cursor_option.hpp>
#include <sge/systems/image_loader.hpp>
#include <sge/systems/input_helper_field.hpp>
#include <sge/systems/input_helper.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/running_to_false.hpp>
#include <sge/window/simple_parameters.hpp>
#include <sge/systems/window.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/viewport/manager.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/instance.hpp>
#include <fcppt/assert.hpp>
#include <fcppt/container/bitfield/bitfield.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/homogenous_pair.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/lexical_cast.hpp>
#include <fcppt/log/log.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/math/deg_to_rad.hpp>
#include <fcppt/math/dim/dim.hpp>
#include <fcppt/math/vector/vector.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/tr1/unordered_map.hpp>
#include <fcppt/chrono/seconds.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <ostream>
#include <utility>

#include <boost/mpl/map/map10.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/integral_c.hpp>
#include <fcppt/mpl/index_of.hpp>

namespace
{
// Define the vertex format which consists of a position value and a normal (for the diffuse shading)
namespace vf
{
// As you can see, we're using OpenGL-2 and below
typedef
sge::renderer::vf::pos<sge::renderer::scalar,3>
position;

typedef
sge::renderer::vf::texpos<sge::renderer::scalar, 2>
texcoord;

// As you can see, we're using OpenGL-2 and below
typedef
sge::renderer::vf::normal<sge::renderer::scalar>
normal;

typedef
sge::renderer::vf::part
<
	boost::mpl::vector3<position,texcoord,normal>
>
format_part;

typedef
sge::renderer::vf::format
<
	boost::mpl::vector1<format_part>
>
format;
}

// Just a little helper method.
void
show_usage(
	char const * const app_path)
{
	std::cerr << "usage: " << app_path << " model-file [texture]\n";
}


class compiled_model
{
FCPPT_NONCOPYABLE(
	compiled_model);
public:
	explicit
	compiled_model(
		sge::model::obj::instance const &,
		sge::renderer::device &,
		sge::renderer::vertex_declaration const &,
		sge::renderer::texture::planar_ptr);

	void
	render();

	~compiled_model();
private:
	sge::renderer::vertex_buffer_ptr vb_;
	sge::renderer::texture::planar_ptr texture_;
	sge::renderer::device &renderer_;
};

compiled_model::compiled_model(
	sge::model::obj::instance const &_model,
	sge::renderer::device &_renderer,
	sge::renderer::vertex_declaration const &_vd,
	sge::renderer::texture::planar_ptr const _texture)
:
	vb_(
		sge::model::obj::vb_converter::convert
		<
			vf::format_part,
//			boost::mpl::map3
			boost::mpl::map2
			<
				boost::mpl::pair
				<
					sge::model::obj::vb_converter::roles::position,
					fcppt::mpl::index_of
					<
						vf::format_part::elements,
						vf::position
					>
				>,
				/*
				boost::mpl::pair
				<
					sge::model::obj::vb_converter::roles::texcoord,
					fcppt::mpl::index_of
					<
						vf::format_part::elements,
						vf::texcoord
					>
				>,*/
				boost::mpl::pair
				<
					sge::model::obj::vb_converter::roles::normal,
					fcppt::mpl::index_of
					<
						vf::format_part::elements,
						vf::normal
					>
				>
			>
		>(
			_renderer,
			_vd,
			_model)),
	texture_(
		_texture),
	renderer_(
		_renderer)
{
}

void
compiled_model::render()
{
	fcppt::scoped_ptr<sge::renderer::texture::scoped> scoped_texture;

	if(texture_)
		scoped_texture.take(
			fcppt::make_unique_ptr<sge::renderer::texture::scoped>(
				fcppt::ref(
					renderer_),
				fcppt::cref(
					*texture_),
				sge::renderer::stage(
					0)));

	sge::renderer::scoped_vertex_buffer scoped_vb(
		renderer_,
		*vb_);

	renderer_.render_nonindexed(
		sge::renderer::first_vertex(
			0),
		sge::renderer::vertex_count(
			vb_->size()),
		sge::renderer::nonindexed_primitive_type::triangle);
}

compiled_model::~compiled_model()
{
}
}

int
main(
	int argc,
	char *argv[])
try
{
	if(argc > 3 || argc <= 1)
	{
		std::cerr << "Error, you provided too many or too few arguments, exiting...\n";
		show_usage(
			argv[0]);
		return EXIT_FAILURE;
	}

	fcppt::log::activate_levels(
		sge::log::global(),
		fcppt::log::level::debug);

	sge::systems::instance sys(
		sge::systems::list()
			(sge::systems::window(
				sge::window::simple_parameters(
					FCPPT_TEXT("sge obj model loader"),
					sge::window::dim(1024,768))))
			(sge::systems::renderer(
				sge::renderer::parameters(
					sge::renderer::visual_depth::depth32,
					sge::renderer::depth_stencil_buffer::d24,
					sge::renderer::vsync::on,
					sge::renderer::no_multi_sampling),
				sge::viewport::fill_on_resize()))
			(sge::systems::image_loader(
				sge::image::capabilities_field::null(),
				sge::all_extensions))
			(sge::systems::input(
				sge::systems::input_helper_field(
					sge::systems::input_helper::keyboard_collector) | sge::systems::input_helper::mouse_collector,
				sge::systems::cursor_option_field(
					sge::systems::cursor_option::exclusive))));

	bool running =
		true;

	fcppt::signal::scoped_connection const cb(
		sys.keyboard_collector().key_callback(
			sge::input::keyboard::action(
				sge::input::keyboard::key_code::escape,
				sge::systems::running_to_false(
					running))));

	sge::camera::object camera(
		sge::camera::parameters(
			sge::camera::movement_speed(
				4.0f),
			sge::camera::rotation_speed(
				200.0f),
			sys.keyboard_collector(),
			sys.mouse_collector()));

	fcppt::signal::scoped_connection const viewport_connection(
		sys.viewport_manager().manage_callback(
			std::tr1::bind(
				sge::camera::projection::update_perspective_from_viewport,
				fcppt::ref(
					sys.renderer()),
				fcppt::ref(
					camera),
				sge::renderer::projection::fov(
					fcppt::math::deg_to_rad(
						90.f)),
				sge::renderer::projection::near(
					0.1f),
				sge::renderer::projection::far(
					1000.f))));

	sge::renderer::vertex_declaration_ptr const vertex_declaration(
		sys.renderer().create_vertex_declaration(
			sge::renderer::vf::dynamic::make_format<vf::format>()));

	sge::model::obj::loader_ptr const model_loader(
		sge::model::obj::create());

	sge::model::obj::instance_ptr model(
		model_loader->load(
			fcppt::from_std_string(
				argv[1])));

	sge::renderer::texture::planar_ptr texture;
	if(argc == 3)
		texture =
			sge::renderer::texture::create_planar_from_path(
				fcppt::from_std_string(
					argv[2]),
				sys.renderer(),
				sys.image_loader(),
				sge::renderer::texture::mipmap::off(),
				sge::renderer::texture::address_mode2(
					sge::renderer::texture::address_mode::clamp),
				sge::renderer::resource_flags::none);

	compiled_model compiled(
		*model,
		sys.renderer(),
		*vertex_declaration,
		texture);

	// Set the important render states
	sys.renderer().state(
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_back_buffer = true)
			(sge::renderer::state::bool_::clear_depth_buffer = true)
			(sge::renderer::state::float_::depth_buffer_clear_val = 1.f)
			(sge::renderer::state::depth_func::less)
			(sge::renderer::state::bool_::enable_alpha_blending = false)
			(sge::renderer::state::cull_mode::front)
			(sge::renderer::state::draw_mode::fill)
			(sge::renderer::state::bool_::enable_lighting = false)
			(sge::renderer::state::stencil_func::off)
			(sge::renderer::state::color::back_buffer_clear_color =
				sge::image::colors::black()));

	sys.renderer().enable_light(
		sge::renderer::light::index(
			0),
		true);

	// We need this timer to update the camera
	sge::timer::basic<sge::timer::clocks::standard>
		frame_timer(
			sge::timer::parameters<sge::timer::clocks::standard>(
				fcppt::chrono::seconds(
					1)));

	// The vertex declaration can be set once in this case
	sge::renderer::scoped_vertex_declaration scoped_vd(
		sys.renderer(),
		*vertex_declaration);

	while(running)
	{
		sys.window().dispatch();

		// If we have no viewport (yet), don't do anything (this is just a
		// precaution, we _might_ divide by zero somewhere below, otherwise)
		if(!sge::renderer::viewport_size(sys.renderer()).content())
			continue;

		// This moves the camera around
		camera.update(
			sge::timer::elapsed_and_reset<sge::camera::duration>(
				frame_timer));

		sge::renderer::scoped_block const block_(
			sys.renderer());

//		compiled.render();
	}
}
catch(fcppt::exception const &e)
{
	fcppt::io::cerr << e.string() << FCPPT_TEXT('\n');
	return EXIT_FAILURE;
}
catch(std::exception const &e)
{
	std::cerr << e.what() << '\n';
	return EXIT_FAILURE;
}
