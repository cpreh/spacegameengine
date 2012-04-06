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
#include <sge/camera/first_person/object.hpp>
#include <sge/camera/first_person/parameters.hpp>
#include <sge/camera/matrix_conversion/world.hpp>
#include <sge/config/media_path.hpp>
#include <sge/image/colors.hpp>
#include <sge/image/color/format.hpp>
#include <sge/log/global.hpp>
#include <sge/model/md3/create.hpp>
#include <sge/model/md3/index_sequence.hpp>
#include <sge/model/md3/loader.hpp>
#include <sge/model/md3/loader_scoped_ptr.hpp>
#include <sge/model/md3/normal_sequence.hpp>
#include <sge/model/md3/object.hpp>
#include <sge/model/md3/vertex_sequence.hpp>
#include <sge/renderer/clear_flags.hpp>
#include <sge/renderer/clear_flags_field.hpp>
#include <sge/renderer/depth_stencil_buffer.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/first_vertex.hpp>
#include <sge/renderer/index_buffer.hpp>
#include <sge/renderer/index_buffer_scoped_ptr.hpp>
#include <sge/renderer/index_count.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/matrix_mode.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/scoped_index_lock.hpp>
#include <sge/renderer/scoped_vertex_buffer.hpp>
#include <sge/renderer/scoped_vertex_declaration.hpp>
#include <sge/renderer/scoped_vertex_lock.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/vertex_buffer_scoped_ptr.hpp>
#include <sge/renderer/vertex_count.hpp>
#include <sge/renderer/vertex_declaration.hpp>
#include <sge/renderer/vertex_declaration_scoped_ptr.hpp>
#include <sge/renderer/viewport_size.hpp>
#include <sge/renderer/visual_depth.hpp>
#include <sge/renderer/vsync.hpp>
#include <sge/renderer/index/i16.hpp>
#include <sge/renderer/index/iterator.hpp>
#include <sge/renderer/index/dynamic/format.hpp>
#include <sge/renderer/index/dynamic/view.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/color.hpp>
#include <sge/renderer/state/cull_mode.hpp>
#include <sge/renderer/state/depth_func.hpp>
#include <sge/renderer/state/draw_mode.hpp>
#include <sge/renderer/state/float.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/stencil_func.hpp>
#include <sge/renderer/vf/format.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/normal.hpp>
#include <sge/renderer/vf/part.hpp>
#include <sge/renderer/vf/pos.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/renderer/vf/view.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/renderer/vf/dynamic/make_part_index.hpp>
#include <sge/systems/cursor_option.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/input_helper.hpp>
#include <sge/systems/input_helper_field.hpp>
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
#include <sge/viewport/manager.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/parameters.hpp>
#include <sge/window/system.hpp>
#include <sge/window/title.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/exit_success.hpp>
#include <awl/main/function_context.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/extract_from_string.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/log/activate_levels.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/math/deg_to_rad.hpp>
#include <fcppt/math/twopi.hpp>
#include <fcppt/math/dim/object_impl.hpp>
#include <fcppt/math/matrix/arithmetic.hpp>
#include <fcppt/math/matrix/object_impl.hpp>
#include <fcppt/math/matrix/rotation_x.hpp>
#include <fcppt/math/matrix/rotation_y.hpp>
#include <fcppt/math/matrix/rotation_z.hpp>
#include <fcppt/math/matrix/static.hpp>
#include <fcppt/math/matrix/translation.hpp>
#include <fcppt/math/matrix/vector.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/random/variate.hpp>
#include <fcppt/random/distribution/uniform_real.hpp>
#include <fcppt/random/generator/minstd_rand.hpp>
#include <fcppt/random/generator/seed_from_chrono.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <cmath>
#include <example_main.hpp>
#include <exception>
#include <iostream>
#include <ostream>
#include <string>
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
	sge::renderer::vertex_buffer_scoped_ptr const vb_;
	sge::renderer::index_buffer_scoped_ptr const ib_;
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
			sge::renderer::vf::dynamic::make_part_index<
				vf::format,
				vf::format_part
			>(),
			sge::renderer::vertex_count(
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
			sge::renderer::index_count(
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
		sge::renderer::first_vertex(0u),
		vb_->size(),
		sge::renderer::indexed_primitive_type::triangle,
		sge::renderer::primitive_count(
			ib_->size().get()/3u),
		sge::renderer::first_index(
			0u));
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
	typedef fcppt::random::generator::minstd_rand generator_type;

	generator_type generator(
		fcppt::random::generator::seed_from_chrono<
			generator_type::seed
		>());

	typedef fcppt::random::distribution::uniform_real<
		sge::renderer::scalar
	> distribution;

	typedef fcppt::random::variate<
		generator_type,
		distribution
	> variate;

	variate position_rng(
		generator,
		distribution(
			distribution::min(
				-position_range
			),
			distribution::sup(
				position_range)));

	variate angle_rng(
		generator,
		distribution(
			distribution::min(
				0.f),
				distribution::sup(
					fcppt::math::twopi<
						sge::renderer::scalar
					>())));

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

sge::camera::coordinate_system::object const
move_eye_position(
	sge::camera::coordinate_system::object result,
	sge::renderer::scalar const eye_distance,
	sge::renderer::scalar const focal_length)
{
	result.position(
		sge::camera::coordinate_system::position(
			result.position().get() + eye_distance * result.right().get()));

	sge::renderer::scalar const
		angle =
			std::atan(
				eye_distance/focal_length),
		sinx = std::sin(angle),
		cosx = std::cos(angle),
		cosxc = 1 - cosx,
		x = result.up().get().x(),
		y = result.up().get().y(),
		z = result.up().get().z();

	typedef
	fcppt::math::matrix::static_<sge::renderer::scalar,3,3>::type
	matrix3;

	matrix3 const rotation_matrix(
		cosx + x*x*cosxc,   x*y*cosxc - z*sinx, x*z*cosxc + y*sinx,
		x*y*cosxc + z*sinx, cosx + y*y*cosxc,   y*z*cosxc - x*sinx,
		x*z*cosxc - y*sinx, y*z*cosxc + x*sinx, cosx + z*z*cosxc);

	result.right(
		sge::camera::coordinate_system::right(
			rotation_matrix * result.right().get()));

	result.forward(
		sge::camera::coordinate_system::forward(
			rotation_matrix * result.forward().get()));

	return
		result;

}

// This adapts the perspective matrix to the now changed camera.
void
adapt_perspective(
	sge::renderer::device &renderer,
	sge::camera::base const &camera)
{
	renderer.transform(
		sge::renderer::matrix_mode::projection,
		camera.projection_matrix().get());
}
}

awl::main::exit_code const
example_main(
	awl::main::function_context const &_main_function_context)
try
{
	if(_main_function_context.argc() > 3)
	{
		std::cerr << "Error, you provided too many arguments, exiting...\n";
		show_usage(
			_main_function_context.argv()[0]);

		return awl::main::exit_failure();
	}

	sge::renderer::scalar
		eye_distance =
			static_cast<sge::renderer::scalar>(
				0.01),
		focal_length =
			static_cast<sge::renderer::scalar>(
				1);

	if(_main_function_context.argc() >= 2)
	{
		if(std::string(_main_function_context.argv()[1]) == "--help")
		{
			show_usage(
				_main_function_context.argv()[0]);
			return awl::main::exit_success();
		}

		typedef fcppt::optional<
			sge::renderer::scalar
		> optional_scalar;

		{
			optional_scalar const opt_eye_distance(
				fcppt::extract_from_string<
					sge::renderer::scalar
				>(
					std::string(
						_main_function_context.argv()[1])));

			if(
				!opt_eye_distance
			)
			{
				std::cerr << "The eye distance argument has to be floating point! Exiting...\n";
				show_usage(
					_main_function_context.argv()[0]);
				return awl::main::exit_failure();
			}

			eye_distance = *opt_eye_distance;
		}

		if(_main_function_context.argc() == 3)
		{
			optional_scalar const opt_focal_length(
				fcppt::extract_from_string<
					sge::renderer::scalar
				>(
					std::string(
						_main_function_context.argv()[2])));

			if(
				!opt_focal_length
			)
			{
				std::cerr << "The focal length argument has to be floating point! Exiting...\n";
				show_usage(
					_main_function_context.argv()[0]);
				return awl::main::exit_failure();
			}

			focal_length = *opt_focal_length;
		}
	}

	fcppt::log::activate_levels(
		sge::log::global(),
		fcppt::log::level::debug);

	sge::systems::instance const sys(
		sge::systems::list()
			(sge::systems::window(
				sge::window::parameters(
					sge::window::title(
						FCPPT_TEXT("sge test for anaglyph 3D")),
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
					sge::systems::input_helper::keyboard_collector)
					| sge::systems::input_helper::mouse_collector,
				sge::systems::cursor_option_field(
					sge::systems::cursor_option::exclusive))));

	fcppt::signal::scoped_connection const escape_callback(
		sge::systems::quit_on_escape(
			sys));

	sge::camera::first_person::object camera(
		sge::camera::first_person::parameters(
			sys.keyboard_collector(),
			sys.mouse_collector(),
			sge::camera::first_person::is_active(
				true
			),
			sge::camera::first_person::movement_speed(
				4.0f
			),
			sge::camera::coordinate_system::identity()
		)
	);

	sge::camera::perspective_projection_from_viewport camera_viewport_connection(
		camera,
		sys.renderer(),
		sys.viewport_manager(),
		sge::renderer::projection::near(
			0.1f
		),
		sge::renderer::projection::far(
			1000.f
		),
		sge::renderer::projection::fov(
			fcppt::math::deg_to_rad(
				90.f
			)
		)
	);
	// Adapt the camera to the viewport
	fcppt::signal::scoped_connection const
		adapt_perspective_connection(
			sys.viewport_manager().manage_callback(
				std::tr1::bind(
					&adapt_perspective,
					fcppt::ref(
						sys.renderer()),
					fcppt::cref(
						camera))));

	sge::renderer::vertex_declaration_scoped_ptr const vertex_declaration(
		sys.renderer().create_vertex_declaration(
			sge::renderer::vf::dynamic::make_format<vf::format>()));

	// Create an md3 loader using the "create" function.
	sge::model::md3::loader_scoped_ptr const md3_loader(
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
			0u),
		true);

	sge::timer::basic<sge::timer::clocks::standard> camera_timer(
		sge::timer::parameters<sge::timer::clocks::standard>(
			sge::camera::update_duration(
				1.0f)));

	// The vertex declaration can be set once in this case
	sge::renderer::scoped_vertex_declaration scoped_vd(
		sys.renderer(),
		*vertex_declaration);

	while(
		sys.window_system().poll()
	)
	{
		// If we have no viewport (yet), don't do anything (this is just a
		// precaution, we _might_ divide by zero somewhere below, otherwise)
		if(!sge::renderer::viewport_size(sys.renderer()).content())
			continue;

		// This moves the camera around
		camera.update(
			sge::timer::elapsed_and_reset<sge::camera::update_duration>(
				camera_timer));

		// Since the "write_*" attributes also apply to the "clear
		// backbuffer" stuff, we set everything to "true" here.
		sys.renderer().state(
			sge::renderer::state::list
				(sge::renderer::state::bool_::write_red = true)
				(sge::renderer::state::bool_::write_blue = true)
				(sge::renderer::state::bool_::write_green = true));

		sge::renderer::scoped_block const block_(
			sys.renderer());

		// Set the color mask to "red"
		sys.renderer().state(
			sge::renderer::state::list
				(sge::renderer::state::bool_::write_red = true)
				(sge::renderer::state::bool_::write_blue = false)
				(sge::renderer::state::bool_::write_green = false));

		model_collection.render(
			sge::camera::matrix_conversion::world(
				move_eye_position(
					camera.coordinate_system(),
					eye_distance,
					focal_length)));

		// Clear depth buffer
		sys.renderer().clear(
			sge::renderer::clear_flags_field(
				sge::renderer::clear_flags::depth_buffer));

		// Set the color mask to cyan
		sys.renderer().state(
			sge::renderer::state::list
				(sge::renderer::state::bool_::write_red = false)
				(sge::renderer::state::bool_::write_blue = true)
				(sge::renderer::state::bool_::write_green = true));

		model_collection.render(
			sge::camera::matrix_conversion::world(
				move_eye_position(
					camera.coordinate_system(),
					-eye_distance,
					focal_length)));
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
