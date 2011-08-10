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
#include <sge/camera/activation_state.hpp>
#include <sge/camera/identity_gizmo.hpp>
#include <sge/camera/object.hpp>
#include <sge/camera/parameters.hpp>
#include <sge/camera/projection/object.hpp>
#include <sge/camera/projection/update_perspective_from_viewport.hpp>
#include <sge/exception.hpp>
#include <sge/image/capabilities_field.hpp>
#include <sge/image/colors.hpp>
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/log/global.hpp>
#include <sge/model/obj/face.hpp>
#include <sge/model/obj/face_sequence.hpp>
#include <sge/model/obj/group_name.hpp>
#include <sge/model/obj/instance.hpp>
#include <sge/model/obj/object_name.hpp>
#include <sge/renderer/depth_stencil_buffer.hpp>
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
#include <sge/renderer/scoped_vertex_lock.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/stage_type.hpp>
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
#include <sge/renderer/texture/address_mode.hpp>
#include <sge/renderer/texture/create_planar_from_file.hpp>
#include <sge/renderer/texture/filter/linear.hpp>
#include <sge/renderer/texture/planar_ptr.hpp>
#include <sge/renderer/vertex_buffer_ptr.hpp>
#include <sge/renderer/vertex_count.hpp>
#include <sge/renderer/vertex_declaration_fwd.hpp>
#include <sge/renderer/vertex_declaration_ptr.hpp>
#include <sge/renderer/vetex_buffer.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <sge/renderer/vf/format.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/normal.hpp>
#include <sge/renderer/vf/part.hpp>
#include <sge/renderer/vf/pos.hpp>
#include <sge/renderer/vf/texpos.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/renderer/vf/view.hpp>
#include <sge/renderer/viewport_size.hpp>
#include <sge/renderer/visual_depth.hpp>
#include <sge/renderer/vsync.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/cursor_option.hpp>
#include <sge/systems/image_loader.hpp>
#include <sge/systems/input_helper_field.hpp>
#include <sge/systems/input_helper.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/running_to_false.hpp>
#include <sge/systems/simple_parameters.hpp>
#include <sge/systems/window.hpp>
#include <sge/time/second.hpp>
#include <sge/time/timer.hpp>
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
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/tr1/unordered_map.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <ostream>
#include <utility>

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

typedef
sge::renderer::vf::view<format_part>
format_part_view;
}

// Just a little helper method.
void
show_usage(
	char const * const app_path)
{
	std::cerr << "usage: " << app_path << " model-file [texture]\n";
}

class group_representation
{
public:
	explicit
	group_representation(
		sge::renderer::size_type const start,
		sge::renderer::size_type const end,
		bool const _has_normals)
	:
		first_vertex_(
			start),
		vertex_count_(
			static_cast<sge::renderer::vertex_count::size_type>(
				end - start)),
		has_normals_(
			_has_normal)
	{

	}

	sge::renderer::first_vertex
	first_vertex() const
	{
		return
			sge::renderer::first_vertex(
				first_vertex_);
	}

	sge::renderer::vertex_count
	vertex_count() const
	{
		return
			sge::renderer::vertex_count(
				vertex_count_);
	}

	bool
	has_normals() const
	{
		return has_normals_;
	}
private:
	sge::renderer::first_vertex::value_type first_vertex_;
	sge::renderer::vertex_count::value_type vertex_count_;
	bool has_normals_;
};

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

	typedef
	std::tr1::unordered_map
	<
		sge::model::obj::group_name,
		group_representation
	>
	group_to_representation;

	typedef
	std::tr1::unordered_map
	<
		sge::model::obj::object_name,
		group_representation
	>
	object_to_representation;

	group_to_representation group_to_representation_;
	object_to_representation object_to_representation_;

	void
	render_group(
		group_representation const &);
};

namespace
{
fcppt::homogenous_pair<sge::renderer::size_type> const
insert_faces(
	vf::format_part_view::iterator &current_vertex,
	sge::renderer::size_type const start_index,
	sge::model::obj::face_sequence const &faces)
{
	sge::renderer::size_type current_index =
		start_index;

	for(
		sge::model::obj::face_sequence::const_iterator current_face =
			faces.begin();
		current_face != faces.end();
		++current_face)
	{
		if(current_face->vertices().size() != 3)
			throw
				sge::exception(
					FCPPT_TEXT("Encountered a face with ")+
					fcppt::lexical_cast<fcppt::string>(
						current_face->vertices().size())+
					FCPPT_TEXT(" vertices. Only triangles are allowed, however."));

		for(
			sge::model::obj::face::vertex_indices::size_type current_face_vertex =
				0;
			current_face_vertex < 3;
			++current_face_vertex)
		{
			current_vertex->set<vf::position>(
				fcppt::math::vector::narrow_cast<vf::position::packed_type>(
					current_face->vertices()[current_face_vertex]));
			current_vertex->set<vf::texcoord>(
				current_face->texcoords()
				?
					fcppt::math::vector::narrow_cast<vf::texcoord::packed_type>(
						(*(current_face->texcoords())[current_face_vertex]))
				:
					vf::texcoord::packed_type::null());
			current_vertex->set<vf::normal>(
				current_face->normals()
				?
					fcppt::math::vector::narrow_cast<vf::texcoord::packed_type>(
						(*(current_face->normals())[current_face_vertex]))
				:
					vf::texcoord::packed_type::null());

			++current_vertex;
			++current_index;
		}
	}

	return
		fcppt::homogenous_pair<sge::renderer::size_type>(
			start_index,
			current_index);
}

sge::renderer::size_type
count_vertices(
	sge::model::obj::instance const &_model)
{
	sge::renderer::size_type result = 0;
	for(
		sge::model::obj::group_sequence::const_iterator it =
			groups.begin();
		it != groups.end();
		++it)
	{
		sge::model::obj::face_sequence const faces =
			_model.group_faces(
				_group);

		result =
			static_cast<sge::renderer::size_type>(
				result +
				3u * faces.size());
	}

	for(
		sge::model::obj::group_sequence::const_iterator it =
			objects.begin();
		it != objects.end();
		++it)
	{
		sge::model::obj::face_sequence const faces =
			_model.object_faces(
				_group);

		result =
			static_cast<sge::renderer::size_type>(
				result +
				3u * faces.size());
	}
	return result;
}
}

compiled_model::compiled_model(
	sge::model::obj::instance const &_model,
	sge::renderer::device &_renderer,
	sge::renderer::vertex_declaration const &_vd,
	sge::renderer::texture::planar_ptr const _texture)
:
	vb_(
		renderer_.create_vertex_buffer(
			_vd,
			sge::renderer::vf::dynamic::part_index(
				0u),
			count_vertices(
				_model),
			sge::renderer::resource_flags::none)),
	texture_(
		_texture)
{
	sge::model::obj::group_sequence const groups =
		_model.groups();
	sge::model::obj::object_sequence const objects =
		_model.objects();

	sge::renderer::scoped_vertex_lock const vblock(
		*vb_,
		sge::renderer::lock_mode::writeonly);

	vf::format_part_view const current_vertex_view(
		vblock.value());

	vf::format_part_view::iterator current_vertex(
		current_vertex_view.begin());

	sge::renderer::size_type current_index = 0;

	for(
		sge::model::obj::group_sequence::const_iterator it =
			groups.begin();
		it != groups.end();
		++it)
	{
		sge::model::obj::face_sequence const faces =
			_model.group_faces(
				*it);

		FCPPT_ASSERT(
			!faces.empty());

		fcppt::homogenous_pair<sge::renderer::size_type> const sub_result(
			insert_faces(
				current_vertex,
				current_index,
				faces));

		group_to_representation.insert(
			std::make_pair(
				*it,
				group_representation(
					sub_result.first,
					sub_result.second,
					faces.begin()->normals())));
	}

	for(
		sge::model::obj::object_sequence::const_iterator it =
			objects.begin();
		it != objects.end();
		++it)
	{
		sge::model::obj::face_sequence const faces =
			_model.object_faces(
				*it);

		object_to_representation_.insert(
			std::make_pair(
				*it,
				insert_faces(
					current_vertex,
					current_index,
					faces)));
	}
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
				*texture_,
				static_cast<sge::renderer::stage_type>(
					0)));

	sge::renderer::scoped_vertex_buffer scoped_vb(
		renderer_,
		*vb_);

	for(
		group_to_representation::const_iterator it =
			group_to_representation_.begin();
		it != group_to_representation_.end();
		++it)
		this->render_group(
			it->second);

	for(
		object_to_representation::const_iterator it =
			object_to_representation_.begin();
		it != object_to_representation_.end();
		++it)
		this->render_group(
			it->second);

}

compiled_model::~compiled_model()
{
}

void
compiled_model::render_group(
	group_representation const &r)
{
	sge::renderer::state::scoped scoped_state(
		sge::renderer::state::list
			(sge::renderer::state::bool_::enable_lighting = r.has_normals()));

	renderer_.render(
		r.first_vertex(),
		r.vertex_count(),
		sge::renderer::nonindexed_primitive_type::triangle);
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
					FCPPT_TEXT("sge model loader"),
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
			sge::camera::projection::object(),
			static_cast<sge::renderer::scalar>(4.),
			static_cast<sge::renderer::scalar>(200.),
			sge::camera::identity_gizmo(),
			sys.keyboard_collector(),
			sys.mouse_collector(),
			sge::camera::activation_state::active));

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
					// Field of view
					static_cast<sge::renderer::scalar>(
						fcppt::math::deg_to_rad(
							90.)),
					// Near plane
					static_cast<sge::renderer::scalar>(
						0.1),
					// Far plane
					static_cast<sge::renderer::scalar>(
						1000.)))),
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

	sge::model::obj::instance model(
		fcppt::from_std_string(
			argv[1]));

	sge::renderer::texture::planar_ptr texture;
	if(argc == 3)
		texture =
			sge::renderer::texture::create_planar_from_file(
				sys.renderer(),
				sys.image_loader(),
				sge::renderer::texture::filter::linear,
				sge::renderer::texture::address_mode2(
					sge::renderer::texture::address_mode::clamp),
				sge::renderer::resource_flags::none);

	compiled_model compiled(
		model,
		sys.renderer(),
		vertex_declaration,
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
	sge::time::timer
		frame_timer(
			sge::time::second(
				1));

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
			frame_timer.reset());

		sge::renderer::scoped_block const block_(
			sys.renderer());

		compiled.render();
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
