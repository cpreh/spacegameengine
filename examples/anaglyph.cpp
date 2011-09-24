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


#include <sge/camera/object.hpp>
#include <sge/camera/parameters.hpp>
#include <sge/camera/projection/object.hpp>
#include <sge/camera/projection/update_perspective_from_viewport.hpp>
#include <sge/config/media_path.hpp>
#include <sge/image/colors.hpp>
#include <sge/image/color/format.hpp>
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/model/md3/index_sequence.hpp>
#include <sge/model/md3/loader_ptr.hpp>
#include <sge/model/md3/loader.hpp>
#include <sge/model/md3/create.hpp>
#include <sge/model/md3/object.hpp>
#include <sge/model/md3/vertex_sequence.hpp>
#include <sge/model/md3/normal_sequence.hpp>
#include <sge/model/md3/index_sequence.hpp>
#include <sge/renderer/depth_stencil_buffer.hpp>
#include <sge/renderer/scoped_vertex_buffer.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/first_vertex.hpp>
#include <sge/renderer/index_buffer_ptr.hpp>
#include <sge/renderer/index_buffer.hpp>
#include <sge/renderer/index/dynamic/format.hpp>
#include <sge/renderer/matrix_mode.hpp>
#include <sge/renderer/index/dynamic/view.hpp>
#include <sge/renderer/index/i16.hpp>
#include <sge/renderer/index/iterator.hpp>
#include <sge/renderer/clear_flags.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/scoped_vertex_declaration.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/viewport_size.hpp>
#include <sge/renderer/scoped_index_lock.hpp>
#include <sge/renderer/scoped_vertex_lock.hpp>
#include <sge/renderer/size_type.hpp>
// Yeah, I probably shouldn't include this.
#include <sge/renderer/state/state.hpp>
#include <sge/renderer/vertex_buffer_ptr.hpp>
#include <sge/renderer/vertex_count.hpp>
#include <sge/renderer/vertex_declaration_fwd.hpp>
#include <sge/renderer/vertex_declaration_ptr.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <sge/renderer/vf/format.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/part.hpp>
#include <sge/renderer/vf/pos.hpp>
#include <sge/renderer/vf/normal.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/renderer/vf/view.hpp>
#include <sge/renderer/visual_depth.hpp>
#include <sge/renderer/vsync.hpp>
#include <sge/timer/basic.hpp>
#include <sge/timer/clocks/standard.hpp>
#include <sge/timer/elapsed.hpp>
#include <sge/timer/parameters.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/cursor_option.hpp>
#include <sge/systems/input_helper_field.hpp>
#include <sge/systems/input_helper.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/parameterless.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/running_to_false.hpp>
#include <sge/systems/window.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/viewport/manager.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/instance.hpp>
#include <sge/window/simple_parameters.hpp>
#include <sge/log/global.hpp>
#include <fcppt/container/bitfield/bitfield.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/lexical_cast.hpp>
#include <fcppt/log/log.hpp>
#include <fcppt/math/deg_to_rad.hpp>
#include <fcppt/math/dim/dim.hpp>
#include <fcppt/math/matrix/matrix.hpp>
#include <fcppt/math/twopi.hpp>
#include <fcppt/random/uniform.hpp>
#include <fcppt/random/make_inclusive_range.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/math/vector/vector.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/signal/signal.hpp>
#include <fcppt/text.hpp>
#include <fcppt/bad_lexical_cast.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <string>
#include <exception>
#include <iostream>
#include <ostream>
#include <cmath>
#include <cstdlib>
#include <fcppt/config/external_end.hpp>

/**
	Example description:

	This example implements anaglyph 3D, which means you have to buy
	red/cyan 3D glasses to enjoy it. When running it (with default
	parameters), you should be able to look around with the mouse, as
	well as move around with w, a, s and d. You should see "arrow"
	models at various locations and in various orientations around the
	"spawn point".

	Anaglyph 3D is achieved by rendering each object twice: From the
	left eye and from the right eye. The left eye is rendered in red,
	the right eye in cyan.
 */


namespace
{
// Define the vertex format which consists of a position value and a normal (for the diffuse shading)
namespace vf
{
// As you can see, we're using OpenGL-2 and below
typedef
sge::renderer::vf::pos
<
	sge::renderer::scalar,
	3
>
position;

// As you can see, we're using OpenGL-2 and below
typedef
sge::renderer::vf::normal
<
	sge::renderer::scalar
>
normal;

typedef
sge::renderer::vf::part
<
	boost::mpl::vector2
	<
		position,
		normal
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

// This class is just a wrapper around a vertex buffer and an index
// buffer. It receives the loaded md3 model and "compiles" both
// buffers from it.
class compiled_model
{
FCPPT_NONCOPYABLE(
	compiled_model);
public:
	explicit
	compiled_model(
		sge::renderer::device &,
		sge::renderer::vertex_declaration const &,
		sge::model::md3::object const &);

	sge::renderer::vertex_buffer &
	vb();

	sge::renderer::vertex_buffer const &
	vb() const;

	void
	render() const;

	~compiled_model();
private:
	sge::renderer::device &renderer_;
	sge::renderer::vertex_buffer_ptr const vb_;
	sge::renderer::index_buffer_ptr const ib_;
};

compiled_model::compiled_model(
	sge::renderer::device &_renderer,
	sge::renderer::vertex_declaration const &_vd,
	sge::model::md3::object const &_model)
:
	renderer_(
		_renderer),
	// Create the vertex buffer
	vb_(
		renderer_.create_vertex_buffer(
			_vd,
			sge::renderer::vf::dynamic::part_index(
				0u),
			static_cast<sge::renderer::size_type>(
				_model.vertices(
					_model.part_names().front()).size()),
			sge::renderer::resource_flags::none)),
	// Create the index buffer. We have to decide which data type to
	// use. Since our models have < 100 vertices, a 16 bit integer is
	// enough, so we're using "format::i16" here. You'll see more of
	// this later on.
	ib_(
		renderer_.create_index_buffer(
			sge::renderer::index::dynamic::format::i16,
			static_cast<sge::renderer::size_type>(
				_model.indices(
					_model.part_names().front()).size()),
		sge::renderer::resource_flags::none))
{
	// Fill the vertex buffer first (arbitrary choice)
	{
		sge::renderer::scoped_vertex_lock const vblock(
			*vb_,
			sge::renderer::lock_mode::writeonly);

		vf::format_part_view const current_vertex_view(
			vblock.value());

		vf::format_part_view::iterator current_vertex(
			current_vertex_view.begin());

		sge::model::md3::vertex_sequence const model_vertices =
			_model.vertices(
				_model.part_names().front());

		// Here, we assume that the model has normals (notice the operator*)
		sge::model::md3::normal_sequence const model_normals =
			*_model.normals(
				_model.part_names().front());

		sge::model::md3::normal_sequence::const_iterator current_model_normal =
			model_normals.begin();

		for(
			sge::model::md3::vertex_sequence::const_iterator current_model_vertex =
				model_vertices.begin();
			current_model_vertex != model_vertices.end();
			++current_model_vertex)
		{
			(*current_vertex).set<vf::position>(
				fcppt::math::vector::structure_cast<vf::position::packed_type>(
					*current_model_vertex));
			(*current_vertex++).set<vf::normal>(
				fcppt::math::vector::structure_cast<vf::normal::packed_type>(
					*current_model_normal++));
		}
	}

	// Then fill the index buffer. The code is somewhat "dual" to the
	// vertex buffer, but has some subtleties. First, we lock the buffer...
	sge::renderer::scoped_index_lock const iblock(
		*ib_,
		sge::renderer::lock_mode::writeonly);

	// then we create a dynamic view to the buffer...
	sge::renderer::index::dynamic::view const indices(
		iblock.value());

	// ...then we declare an iterator for the buffer. Again, you we meet
	// the index format. We could have designed the following code to be
	// agnostic of the integer type, but that would be even more code.
	sge::renderer::index::iterator<sge::renderer::index::format_16> current_index(
		indices.data());

	sge::model::md3::index_sequence const model_indices =
		_model.indices(
			_model.part_names().front());

	// Fill the buffer. _Again_, the format type appears.
	for(
		sge::model::md3::index_sequence::const_iterator current_model_index =
			model_indices.begin();
		current_model_index != model_indices.end();
		++current_model_index)
		(*current_index++).set(
			static_cast<sge::renderer::index::i16>(
				*current_model_index));
}

sge::renderer::vertex_buffer &
compiled_model::vb()
{
	return *vb_;
}

sge::renderer::vertex_buffer const &
compiled_model::vb() const
{
	return *vb_;
}

void
compiled_model::render() const
{
	// This should be pretty self-explanatory. Note that here, we just
	// call render. The vertex buffer isn't activated here, neither is
	// the vertex declaration. This is done at a "higher" level so we
	// don't activate/deactive it too often (which decreases
	// performance).
	renderer_.render_indexed(
		*ib_,
		sge::renderer::first_vertex(0),
		sge::renderer::vertex_count(
			vb_->size()),
		sge::renderer::indexed_primitive_type::triangle,
		sge::renderer::primitive_count(
			ib_->size()/3),
		sge::renderer::first_index(
			0));
}

compiled_model::~compiled_model()
{
}

// This is a specific model instance, meaning it has a position and an
// orientation. It has no logic, however.
class model_instance
{
FCPPT_NONCOPYABLE(
	model_instance);
public:
	explicit
	model_instance(
		compiled_model const &,
		sge::renderer::matrix4 const &);

	void
	render();

	sge::renderer::matrix4 const &
	modelview() const;

	~model_instance();
private:
	compiled_model const &backend_;
	sge::renderer::matrix4 const modelview_;
};

model_instance::model_instance(
	compiled_model const &_backend,
	sge::renderer::matrix4 const &_modelview)
:
	backend_(
		_backend),
	modelview_(
		_modelview)
{
}

void
model_instance::render()
{
	backend_.render();
}

sge::renderer::matrix4 const &
model_instance::modelview() const
{
	return modelview_;
}

model_instance::~model_instance()
{
}

// This class represents a collection of randomly placed and oriented
// "model_instance" objects (see above).
class random_model_collection
{
FCPPT_NONCOPYABLE(
	random_model_collection);
public:
	explicit
	random_model_collection(
		sge::renderer::device &,
		compiled_model const &);

	void
	render(
		sge::renderer::matrix4 const &);

	~random_model_collection();
private:
	typedef
	boost::ptr_vector<model_instance>
	model_sequence;

	sge::renderer::device &renderer_;
	compiled_model const &backend_;
	model_sequence models_;
};

random_model_collection::random_model_collection(
	sge::renderer::device &_renderer,
	compiled_model const &_backend)
:
	renderer_(
		_renderer),
	backend_(
		_backend),
	models_()
{
	// Create objects in the cube with side length 10
	sge::renderer::scalar const position_range =
		static_cast<sge::renderer::scalar>(
			10);

	// See the fcppt documentation on how this really works. It's not
	// that difficult, however.
	fcppt::random::uniform<sge::renderer::scalar> position_rng(
		fcppt::random::make_inclusive_range<sge::renderer::scalar>(
			-position_range,
			position_range));

	// Ditto
	fcppt::random::uniform<sge::renderer::scalar> angle_rng(
		fcppt::random::make_inclusive_range<sge::renderer::scalar>(
			0,
			fcppt::math::twopi<sge::renderer::scalar>()));

	model_sequence::size_type const number_of_models =
		100;

	for(model_sequence::size_type i = 0; i < number_of_models; ++i)
		// Again, we refer to the fcppt documentation on what the hell
		// we're doing here. tl;dr: This is for exception safety and
		// against memory leaks.
		fcppt::container::ptr::push_back_unique_ptr(
			models_,
			fcppt::make_unique_ptr<model_instance>(
				fcppt::cref(
					backend_),
				// Concatenate translation and rotation. Slightly expensive,
				// but we only need to do it once, so...
				fcppt::math::matrix::rotation_x(
					angle_rng()) *
				fcppt::math::matrix::rotation_y(
					angle_rng()) *
				fcppt::math::matrix::rotation_z(
					angle_rng()) *
				fcppt::math::matrix::translation(
					sge::renderer::vector3(
						position_rng(),
						position_rng(),
						position_rng()))));
}

void
random_model_collection::render(
	sge::renderer::matrix4 const &mv)
{
	// Finally, we activate the vertex buffer so we can render stuff
	// with it. We only activate it once, however, not for every model.
	sge::renderer::scoped_vertex_buffer scoped_vb(
		renderer_,
		backend_.vb());

	for(
		model_sequence::iterator current_model =
			models_.begin();
		current_model != models_.end();
		++current_model)
	{
		// Set the world transformation and render
		renderer_.transform(
			sge::renderer::matrix_mode::world,
			mv * current_model->modelview());

		current_model->render();
	}
}

random_model_collection::~random_model_collection()
{
}

// Just a little helper method.
void
show_usage(
	char const * const app_path)
{
	std::cerr << "usage: " << app_path << " [<eye-distance] [<focal-length>]\n";
	std::cerr << "The default eye distance is 0.01, the default focal length is 5\n";
}

// Rendering works as follows:
// The camera gives us a coordinate system consisting of three vectors: right, up, and forward:
//
// .oO(The following ascii art is probably screwed up if you're using a non-monospace font)
//     ^
//     |
//     | forward
//     |
// up  +-----> right
//
// We want to emulate a person looking straight ahead (along the
// forward vector) with two eyes, focusing an object at distance
// 'f'. The distance between the eyes is 'd'. So we have:
//          x
//   |     / \     |
//   |    /   \    |
//   |   /  ^  \   |  f
//   |  /   |   \ a|
//   | /    |    \ |
//   |/     |     \|
//   y      +----->z
//    <---->
//      d/2
//
// Here, 'y' and 'z' are the two eyes, focusing the object at location 'x'.
// Now, rendering is just:
//
// - Translate d/2 along the "right" vector
// - Rotate the coordinate system around the "up" vector with angle 'a'
//
// Using simple trigonometry, we get "atan(f/(d/2))" for 'a'
// The following function implements just this.

void
move_eye_position(
	sge::camera::object &camera,
	sge::renderer::scalar const eye_distance,
	sge::renderer::scalar const focal_length)
{
	camera.gizmo().position(
		camera.gizmo().position() + eye_distance * camera.gizmo().right());

	sge::renderer::scalar const
		angle =
			std::atan(
				eye_distance/focal_length),
		sinx = std::sin(angle),
		cosx = std::cos(angle),
		cosxc = 1 - cosx,
		x = camera.gizmo().up().x(),
		y = camera.gizmo().up().y(),
		z = camera.gizmo().up().z();

	fcppt::math::matrix::static_<sge::renderer::scalar,3,3>::type rotation_matrix(
		cosx + x*x*cosxc,   x*y*cosxc - z*sinx, x*z*cosxc + y*sinx,
		x*y*cosxc + z*sinx, cosx + y*y*cosxc,   y*z*cosxc - x*sinx,
		x*z*cosxc - y*sinx, y*z*cosxc + x*sinx, cosx + z*z*cosxc);

	camera.gizmo().right(
		rotation_matrix * camera.gizmo().right());

	camera.gizmo().forward(
		rotation_matrix * camera.gizmo().forward());

}

// This adapts the perspective matrix to the now changed camera.
void
adapt_perspective(
	sge::renderer::device &renderer,
	sge::camera::object const &camera)
{
	renderer.transform(
		sge::renderer::matrix_mode::projection,
		camera.projection());
}
}

int
main(
	int argc,
	char *argv[])
try
{
	if(argc > 3)
	{
		std::cerr << "Error, you provided too many arguments, exiting...\n";
		show_usage(
			argv[0]);
		return EXIT_FAILURE;
	}

	sge::renderer::scalar
		eye_distance =
			static_cast<sge::renderer::scalar>(
				0.01),
		focal_length =
			static_cast<sge::renderer::scalar>(
				1);

	if(argc >= 2)
	{
		if(std::string(argv[1]) == "--help")
		{
			show_usage(
				argv[0]);
			return EXIT_SUCCESS;
		}

		try
		{
			eye_distance =
				fcppt::lexical_cast<sge::renderer::scalar>(
					std::string(
						argv[1]));
		}
		catch(fcppt::bad_lexical_cast const &)
		{
			std::cerr << "The eye distance argument has to be floating point! Exiting...\n";
			show_usage(
				argv[0]);
			return EXIT_FAILURE;
		}

		if(argc == 3)
		{
			try
			{
				focal_length =
					fcppt::lexical_cast<sge::renderer::scalar>(
						std::string(
							argv[2]));
			}
			catch(fcppt::bad_lexical_cast const &)
			{
				std::cerr << "The focal length argument has to be floating point! Exiting...\n";
				show_usage(
					argv[0]);
				return EXIT_FAILURE;
			}
		}
	}

	fcppt::log::activate_levels(
		sge::log::global(),
		fcppt::log::level::debug);

	sge::systems::instance sys(
		sge::systems::list()
			(sge::systems::window(
				sge::window::simple_parameters(
					FCPPT_TEXT("sge test for anaglyph 3D"),
					sge::window::dim(1024,768))))
			(sge::systems::renderer(
				sge::renderer::parameters(
					sge::renderer::visual_depth::depth32,
					sge::renderer::depth_stencil_buffer::d24,
					sge::renderer::vsync::on,
					sge::renderer::no_multi_sampling),
				sge::viewport::fill_on_resize()))
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
				4.f),
			sge::camera::rotation_speed(
				200.f),
			sys.keyboard_collector(),
			sys.mouse_collector()));

	// Adapt the camera to the viewport
	fcppt::signal::scoped_connection const
		viewport_connection(
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
						1000.f)))),
		adapt_perspective_connection(
			sys.viewport_manager().manage_callback(
				std::tr1::bind(
					&adapt_perspective,
					fcppt::ref(
						sys.renderer()),
					fcppt::cref(
						camera))));

	sge::renderer::vertex_declaration_ptr const vertex_declaration(
		sys.renderer().create_vertex_declaration(
			sge::renderer::vf::dynamic::make_format<vf::format>()));

	// Create an md3 loader using the "create" function.
	sge::model::md3::loader_ptr md3_loader(
		sge::model::md3::create());

	// Create a model and a model collection
	compiled_model main_model(
		sys.renderer(),
		*vertex_declaration,
		*md3_loader->load(
			sge::config::media_path()
				/ FCPPT_TEXT("models")
				/ FCPPT_TEXT("arrow.md3")));

	random_model_collection model_collection(
		sys.renderer(),
		main_model);

	// Set the important render states
	sys.renderer().state(
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_back_buffer = true)
			(sge::renderer::state::bool_::clear_depth_buffer = true)
			(sge::renderer::state::float_::depth_buffer_clear_val = 1.f)
			(sge::renderer::state::depth_func::less)
			(sge::renderer::state::bool_::enable_alpha_blending = false)
			(sge::renderer::state::cull_mode::counter_clockwise)
			(sge::renderer::state::draw_mode::fill)
			(sge::renderer::state::bool_::enable_lighting = true)
			(sge::renderer::state::stencil_func::off)
			(sge::renderer::state::color::back_buffer_clear_color =
				sge::image::colors::black()));

	sys.renderer().enable_light(
		sge::renderer::light::index(
			0),
		true);

	sge::timer::basic<sge::timer::clocks::standard> camera_timer(
		sge::timer::parameters<sge::timer::clocks::standard>(
			sge::camera::duration(
				1.0f)));

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
			sge::timer::elapsed<sge::camera::duration>(
				camera_timer));

		camera_timer.reset();

		// Since the "write_*" attributes also apply to the "clear
		// backbuffer" stuff, we set everything to "true" here.
		sys.renderer().state(
			sge::renderer::state::list
				(sge::renderer::state::bool_::write_red = true)
				(sge::renderer::state::bool_::write_blue = true)
				(sge::renderer::state::bool_::write_green = true));

		sge::renderer::scoped_block const block_(
			sys.renderer());

		sge::camera::gizmo_type const original_gizmo =
			camera.gizmo();

		// Set the color mask to "red"
		sys.renderer().state(
			sge::renderer::state::list
				(sge::renderer::state::bool_::write_red = true)
				(sge::renderer::state::bool_::write_blue = false)
				(sge::renderer::state::bool_::write_green = false));

		move_eye_position(
			camera,
			eye_distance,
			focal_length);

		model_collection.render(
			camera.world());

		camera.gizmo() =
			original_gizmo;

		// Clear depth buffer
		sys.renderer().clear(
			sge::renderer::clear_flags::depth_buffer);

		// Set the color mask to cyan
		sys.renderer().state(
			sge::renderer::state::list
				(sge::renderer::state::bool_::write_red = false)
				(sge::renderer::state::bool_::write_blue = true)
				(sge::renderer::state::bool_::write_green = true));

		move_eye_position(
			camera,
			-eye_distance,
			focal_length);

		model_collection.render(
			camera.world());

		camera.gizmo() =
			original_gizmo;
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
