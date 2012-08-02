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

#include <sge/camera/coordinate_system/identity.hpp>
#include <sge/camera/coordinate_system/object.hpp>
#include <sge/camera/first_person/parameters.hpp>
#include <sge/camera/matrix_conversion/world.hpp>
#include <sge/model/obj/parse_mtllib.hpp>
#include <sge/model/obj/vf/format.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/find_and_convert_member.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/get.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/parse_file_exn.hpp>
#include <sge/renderer/device.hpp>
#include <fcppt/math/rad_to_deg.hpp>
#include <sge/renderer/scoped_transform.hpp>
#include <sge/renderer/scoped_vertex_buffer.hpp>
#include <sge/renderer/scoped_vertex_declaration.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/vertex_declaration.hpp>
#include <sge/renderer/context/object.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/scoped.hpp>
#include <sge/renderer/target/base.hpp>
#include <sge/renderer/target/viewport_size.hpp>
#include <sge/renderer/texture/scoped.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/scenic/scene.hpp>
#include <sge/timer/elapsed_and_reset.hpp>
#include <sge/timer/parameters.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/math/dim/object_impl.hpp>
#include <fcppt/math/matrix/arithmetic.hpp>
#include <fcppt/math/matrix/rotation_x.hpp>
#include <fcppt/math/matrix/rotation_y.hpp>
#include <fcppt/math/matrix/rotation_z.hpp>
#include <fcppt/math/matrix/scaling.hpp>
#include <fcppt/math/matrix/translation.hpp>
#include <fcppt/math/matrix/vector.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/narrow_cast.hpp>
#include <fcppt/math/vector/output.hpp>


namespace
{
sge::renderer::vector3 const
from_blender_vector(
	sge::renderer::vector3 const &_v)
{
	return
		sge::renderer::vector3(
			_v.x(),
			_v.z(),
			_v.y());
}

sge::renderer::matrix4 const
rotation_from_angles_camera(
	sge::renderer::vector3 const &_angles)
{
	return
		fcppt::math::matrix::rotation_z(
			_angles.z()) *
		fcppt::math::matrix::rotation_y(
			-_angles.y()) *
		fcppt::math::matrix::rotation_x(
			-_angles.x());
}

sge::renderer::matrix4 const
rotation_from_angles_mesh(
	sge::renderer::vector3 const &_angles)
{
	return
		fcppt::math::matrix::rotation_y(
			-_angles.y()) *
		fcppt::math::matrix::rotation_z(
			-_angles.z()) *
		fcppt::math::matrix::rotation_x(
			-_angles.x());
}

sge::renderer::vector3 const
multiply_matrix4_vector3(
	sge::renderer::matrix4 const &_matrix,
	sge::renderer::vector3 const &_vector)
{
	return
		fcppt::math::vector::narrow_cast<sge::renderer::vector3>(
			_matrix *
			sge::renderer::vector4(
				_vector.x(),
				_vector.y(),
				_vector.z(),
				1.0f));
}
}

sge::scenic::scene::scene(
	sge::renderer::device &_renderer,
	sge::image2d::system &_image_loader,
	sge::viewport::manager &_viewport_manager,
	sge::input::keyboard::device &_keyboard,
	sge::input::mouse::device &_mouse,
	sge::scenic::scene_description_file const &_scene_description_file,
	sge::scenic::model_base_path const &_model_base_path,
	sge::scenic::material_base_path const &_material_base_path,
	sge::scenic::texture_base_path const &_texture_base_path)
:
	texture_base_path_(
		_texture_base_path),
	model_base_path_(
		_model_base_path),
	material_base_path_(
		_material_base_path),
	model_vertex_declaration_(
		_renderer.create_vertex_declaration(
			sge::renderer::vf::dynamic::make_format<sge::model::obj::vf::format>())),
	texture_manager_(
		_renderer,
		_image_loader),
	materials_(),
	camera_(
		sge::camera::first_person::parameters(
			_keyboard,
			_mouse,
			sge::camera::first_person::is_active(
				true),
			sge::camera::first_person::movement_speed(
				4.0f),
			sge::camera::coordinate_system::identity())),
	camera_viewport_connection_(),
	model_name_to_instance_(),
	meshes_(),
	lights_(),
	camera_timer_(
		sge::timer::parameters<sge::timer::clocks::standard>(
			sge::camera::update_duration(
				1.0f)))
{
	sge::parse::json::object const json_file(
		sge::parse::json::parse_file_exn(
			_scene_description_file.get()));

	this->load_camera(
		sge::parse::json::find_member_exn<sge::parse::json::object const>(
			json_file.members,
			FCPPT_TEXT("camera")),
		_renderer,
		_viewport_manager);

	this->load_meshes(
		_renderer,
		sge::parse::json::find_member_exn<sge::parse::json::array const>(
			json_file.members,
			FCPPT_TEXT("meshes")));
}

void
sge::scenic::scene::render(
	sge::renderer::context::object &_context)
{
	if(
		!sge::renderer::target::viewport_size(
			_context.target()).content())
		return;

	camera_.update(
		sge::timer::elapsed_and_reset<sge::camera::update_duration>(
			camera_timer_));

	sge::renderer::scoped_vertex_declaration scoped_vertex_declaration(
		_context,
		*model_vertex_declaration_);

	sge::renderer::scoped_transform scoped_projection(
		_context,
		sge::renderer::matrix_mode::projection,
		camera_.projection_matrix().get());

	sge::renderer::state::scoped scoped_global_state(
		_context,
		sge::renderer::state::list
		//			(sge::renderer::state::bool_::enable_lighting = true)
			(sge::renderer::state::bool_::enable_lighting = false)
			(sge::renderer::state::depth_func::less)
			(sge::renderer::state::cull_mode::off));

	this->enable_lights(
		_context);

	for(
		mesh_sequence::const_iterator it =
			meshes_.begin();
		it != meshes_.end();
		++it)
		this->render_mesh(
			*it,
			_context);
}

sge::scenic::scene::~scene()
{
}

void
sge::scenic::scene::enable_lights(
	sge::renderer::context::object &_context)
{
	sge::renderer::light::index current_light_index(
		0u);

	for(
		light_sequence::const_iterator it =
			lights_.begin();
		it != lights_.end();
		++it)
	{
		sge::renderer::scoped_transform scoped_world(
			_context,
			sge::renderer::matrix_mode::world,
			sge::camera::matrix_conversion::world(
				camera_.coordinate_system()));

		_context.enable_light(
			current_light_index,
			true);

		_context.light(
			current_light_index,
			*it);

		current_light_index++;
	}
}

void
sge::scenic::scene::render_mesh(
	sge::scenic::mesh const &_mesh,
	sge::renderer::context::object &_context)
{
	sge::renderer::scoped_transform scoped_world(
		_context,
		sge::renderer::matrix_mode::world,
		sge::camera::matrix_conversion::world(
			camera_.coordinate_system()) *
		fcppt::math::matrix::translation(
			_mesh.position().get()) *
		rotation_from_angles_mesh(
			_mesh.rotation().get()) *
		fcppt::math::matrix::scaling(
			_mesh.scale().get()));

	sge::model::obj::instance &model(
		_mesh.model());

	sge::renderer::scoped_vertex_buffer scoped_vertex_buffer(
		_context,
		model.vertex_buffer());

	for(
		sge::model::obj::material_to_index_buffer_range::const_iterator material_name_and_index_buffer_range =
			model.parts().begin();
		material_name_and_index_buffer_range != model.parts().end();
		++material_name_and_index_buffer_range)
	{
		sge::model::obj::material_map::const_iterator const material_name_and_material =
			materials_.find(
				material_name_and_index_buffer_range->first);

		FCPPT_ASSERT_PRE(
			material_name_and_material != materials_.end());

		sge::model::obj::material const &material(
			material_name_and_material->second);

		_context.material(
			material.renderer_material());

		fcppt::scoped_ptr<sge::renderer::texture::scoped> scoped_texture;
		if(!material.texture().get().empty())
		{
			scoped_texture.take(
				fcppt::make_unique_ptr<sge::renderer::texture::scoped>(
					fcppt::ref(
						_context),
					fcppt::cref(
						texture_manager_.texture_for_path(
							texture_base_path_.get() / material.texture().get())),
					sge::renderer::texture::stage(
						0u)));
		}

		_context.render_indexed(
			model.index_buffer(),
			sge::renderer::first_vertex(
				0u),
			sge::renderer::vertex_count(
				model.vertex_buffer().size()),
			sge::renderer::primitive_type::triangle_list,
			material_name_and_index_buffer_range->second.first_index(),
			material_name_and_index_buffer_range->second.index_count());
	}
}

void
sge::scenic::scene::load_camera(
	sge::parse::json::object const &_json_camera,
	sge::renderer::device &_renderer,
	sge::viewport::manager &_viewport_manager)
{
	camera_viewport_connection_.take(
		fcppt::make_unique_ptr<sge::camera::perspective_projection_from_viewport>(
			fcppt::ref(
				camera_),
			fcppt::ref(
				_renderer),
			fcppt::ref(
				_viewport_manager),
			sge::renderer::projection::near(
				sge::parse::json::find_and_convert_member<sge::renderer::scalar>(
					_json_camera,
					sge::parse::json::path(
					FCPPT_TEXT("near")))),
			sge::renderer::projection::far(
				sge::parse::json::find_and_convert_member<sge::renderer::scalar>(
					_json_camera,
					sge::parse::json::path(
					FCPPT_TEXT("far")))),
			sge::renderer::projection::fov(
				0.6f
				/*
				sge::parse::json::find_and_convert_member<sge::renderer::scalar>(
					_json_camera,
					sge::parse::json::path(
					FCPPT_TEXT("fov")))*/)));

	sge::renderer::vector3 const camera_rotation_vector(
		from_blender_vector(
			sge::parse::json::find_and_convert_member<sge::renderer::vector3>(
				_json_camera,
				sge::parse::json::path(
					FCPPT_TEXT("rotation")))));

	sge::renderer::matrix4 const camera_rotation(
		rotation_from_angles_camera(
			camera_rotation_vector));

	sge::renderer::vector3 const
		right(
			multiply_matrix4_vector3(
				camera_rotation,
				sge::renderer::vector3(1.0f,0.0f,0.0f))),
		up(
			multiply_matrix4_vector3(
				camera_rotation,
				sge::renderer::vector3(0.0f,0.0f,1.0f))),
		forward(
			multiply_matrix4_vector3(
				camera_rotation,
				sge::renderer::vector3(0.0f,-1.0f,0.0f)));

	camera_.coordinate_system(
		sge::camera::coordinate_system::object(
			sge::camera::coordinate_system::right(
				right),
			sge::camera::coordinate_system::up(
				up),
			sge::camera::coordinate_system::forward(
				forward),
			sge::camera::coordinate_system::position(
				-from_blender_vector(
					sge::parse::json::find_and_convert_member<sge::renderer::vector3>(
						_json_camera,
						sge::parse::json::path(
						FCPPT_TEXT("position")))))));
}

void
sge::scenic::scene::load_meshes(
	sge::renderer::device &_renderer,
	sge::parse::json::array const &_json_meshes)
{
	for(
		sge::parse::json::element_vector::const_iterator current_mesh =
			_json_meshes.elements.begin();
		current_mesh != _json_meshes.elements.end();
		++current_mesh)
		this->load_mesh(
			_renderer,
			sge::parse::json::get<sge::parse::json::object const>(
				*current_mesh));
}

void
sge::scenic::scene::load_mesh(
	sge::renderer::device &_renderer,
	sge::parse::json::object const &_json_mesh)
{
	fcppt::string const mesh_name(
		sge::parse::json::find_and_convert_member<fcppt::string>(
			_json_mesh,
			sge::parse::json::path(
				FCPPT_TEXT("name"))));

	sge::model::obj::instance &model_instance =
		this->insert_model_if_necessary(
			_renderer,
			mesh_name);

	fcppt::container::ptr::push_back_unique_ptr(
		meshes_,
		fcppt::make_unique_ptr<sge::scenic::mesh>(
			fcppt::ref(
				model_instance),
			sge::scenic::position(
				from_blender_vector(
					sge::parse::json::find_and_convert_member<sge::renderer::vector3>(
						_json_mesh,
						sge::parse::json::path(
							FCPPT_TEXT("position"))))),
			sge::scenic::rotation(
				from_blender_vector(
					sge::parse::json::find_and_convert_member<sge::renderer::vector3>(
						_json_mesh,
						sge::parse::json::path(
							FCPPT_TEXT("rotation"))))),
			sge::scenic::scale(
				from_blender_vector(
					sge::parse::json::find_and_convert_member<sge::renderer::vector3>(
						_json_mesh,
						sge::parse::json::path(
							FCPPT_TEXT("scale")))))));
}

sge::model::obj::instance &
sge::scenic::scene::insert_model_if_necessary(
	sge::renderer::device &_renderer,
	fcppt::string const &_model_name)
{
	model_name_to_instance_map::iterator model_name_and_instance(
		model_name_to_instance_.find(
			_model_name));

	if(model_name_and_instance != model_name_to_instance_.end())
		return
			*(model_name_and_instance->second);

	sge::model::obj::prototype const new_prototype(
		model_base_path_.get() / (_model_name+FCPPT_TEXT(".obj")));

	for(
		sge::model::obj::material_file_sequence::const_iterator current_material_file =
			new_prototype.material_files().begin();
		current_material_file != new_prototype.material_files().end();
		++current_material_file)
	{
		sge::model::obj::material_map const new_materials(
			sge::model::obj::parse_mtllib(
				material_base_path_.get() / (*current_material_file)));

		materials_.insert(
			new_materials.begin(),
			new_materials.end());
	}

	return
		*fcppt::container::ptr::insert_unique_ptr_map(
			model_name_to_instance_,
			_model_name,
			fcppt::make_unique_ptr<sge::model::obj::instance>(
				fcppt::ref(
					_renderer),
				fcppt::ref(
					*model_vertex_declaration_),
				fcppt::cref(
					new_prototype))).first->second;
}
