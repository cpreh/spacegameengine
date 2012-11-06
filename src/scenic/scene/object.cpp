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


#include <sge/camera/base.hpp>
#include <sge/camera/has_mutable_projection.hpp>
#include <sge/camera/coordinate_system/object.hpp>
#include <sge/camera/matrix_conversion/world.hpp>
#include <sge/image/colors.hpp>
#include <sge/model/obj/parse_mtllib.hpp>
#include <sge/model/obj/prototype.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/vertex_declaration.hpp>
#include <sge/renderer/target/base.hpp>
#include <sge/renderer/target/viewport_size.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/scenic/exception.hpp>
#include <sge/scenic/render_context/base.hpp>
#include <sge/scenic/render_context/fog/properties.hpp>
#include <sge/scenic/render_queue/object.hpp>
#include <sge/scenic/scene/manager.hpp>
#include <sge/scenic/scene/object.hpp>
#include <sge/scenic/scene/prototype.hpp>
#include <sge/scenic/scene/material/from_obj_material.hpp>
#include <sge/scenic/scene/mesh/object.hpp>
#include <sge/scenic/vf/format.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/move.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/string.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/math/dim/object_impl.hpp>
#include <fcppt/math/matrix/arithmetic.hpp>
#include <fcppt/math/matrix/scaling.hpp>
#include <fcppt/math/matrix/translation.hpp>
#include <fcppt/math/vector/output.hpp>


sge::scenic::scene::object::object(
	sge::scenic::scene::manager &_scene_manager,
	sge::viewport::manager &_viewport_manager,
	sge::charconv::system &_charconv_system,
	sge::camera::base &_camera,
	sge::scenic::scene::prototype_unique_ptr _prototype)
:
	scene_manager_(
		_scene_manager),
	camera_(
		_camera),
	charconv_system_(
		_charconv_system),
	prototype_(
		fcppt::move(
			_prototype)),
	camera_viewport_connection_(
		dynamic_cast<sge::camera::has_mutable_projection &>(
			camera_),
		_viewport_manager,
		prototype_->camera().near(),
		prototype_->camera().far(),
		prototype_->camera().fov()),
	mesh_name_to_instance_(),
	materials_(),
	state_changes_()
{
	this->load_entities();

	/*
	camera_.update_coordinate_system(
		prototype_->camera().coordinate_system());
	*/
}

void
sge::scenic::scene::object::render(
	sge::scenic::render_context::base &_context)
{
	if(
		!sge::renderer::target::viewport_size(
			_context.target()).content())
		return;

	state_changes_ =
		0u;

	_context.transform(
		sge::scenic::render_context::transform_matrix_type::projection,
		camera_.projection_matrix().get());

	this->activate_lights(
		_context);

	_context.fog(
		prototype_->fog());

	sge::scenic::render_queue::object current_render_queue(
		scene_manager_.texture_manager());

	for(
		sge::scenic::scene::entity_sequence::const_iterator it =
			prototype_->entities().begin();
		it != prototype_->entities().end();
		++it)
		this->render_entity(
			*it,
			current_render_queue);

	/*sge::scenic::render_queue::state_change_count const state_changes(
	 */
	current_render_queue.render(_context)/*)*/;

	/*
	std::cout
		<< "\r"
		<< prototype_->entities().size()
		<< " entities, "
		<< state_changes.get()
		<< " state changes";

	std::cout.flush();
	*/
}

sge::scenic::scene::object::~object()
{
	//std::cout << "\n";
}

void
sge::scenic::scene::object::load_entities()
{
	for(
		sge::scenic::scene::entity_sequence::const_iterator current_entity =
			prototype_->entities().begin();
		current_entity != prototype_->entities().end();
		++current_entity)
	{
		mesh_map::iterator mesh_name_and_instance(
			mesh_name_to_instance_.find(
				current_entity->mesh_path()));

		if(mesh_name_and_instance != mesh_name_to_instance_.end())
			continue;

		sge::model::obj::prototype const new_prototype(
			current_entity->mesh_path().get(),
			charconv_system_);

		for(
			sge::model::obj::material::file_sequence::const_iterator current_material_file =
				new_prototype.material_files().begin();
			current_material_file != new_prototype.material_files().end();
			++current_material_file)
		{
			sge::model::obj::material_map const new_materials(
				sge::model::obj::parse_mtllib(
					*current_material_file,
					charconv_system_));

			for(
				sge::model::obj::material_map::const_iterator current_obj_material =
					new_materials.begin();
				current_obj_material != new_materials.end();
				++current_obj_material)
			{
				materials_.insert(
					std::make_pair(
						sge::scenic::scene::identifier(
							current_obj_material->first.get()),
						sge::scenic::scene::material::from_obj_material(
							current_obj_material->second)));
			}
		}

		fcppt::container::ptr::insert_unique_ptr_map(
			mesh_name_to_instance_,
			current_entity->mesh_path(),
			fcppt::make_unique_ptr<sge::scenic::scene::mesh::object>(
				fcppt::ref(
					scene_manager_.renderer()),
				fcppt::ref(
					scene_manager_.vertex_declaration()),
				fcppt::cref(
					new_prototype)));
	}
}

void
sge::scenic::scene::object::activate_lights(
	sge::scenic::render_context::base &_context)
{
	_context.transform(
		sge::scenic::render_context::transform_matrix_type::world,
		sge::camera::matrix_conversion::world(
			camera_.coordinate_system()));

	_context.lights(
		prototype_->lights());
}

void
sge::scenic::scene::object::render_entity(
	sge::scenic::scene::entity const &_entity,
	sge::scenic::render_queue::object &_context)
{
	sge::scenic::scene::mesh::object &mesh(
		*(mesh_name_to_instance_.find(
			_entity.mesh_path())->second));

	_context.current_vertex_buffer(
		mesh.vertex_buffer());

	for(
		sge::scenic::scene::mesh::material_to_index_buffer_range::const_iterator material_name_and_index_buffer_range =
			mesh.parts().begin();
		material_name_and_index_buffer_range != mesh.parts().end();
		++material_name_and_index_buffer_range)
	{
		material_map::const_iterator const material_name_and_material =
			materials_.find(
				material_name_and_index_buffer_range->first);

		FCPPT_ASSERT_PRE(
			material_name_and_material != materials_.end());

		sge::scenic::scene::material::object const &material(
			material_name_and_material->second);

		_context.current_material(
			material);

		_context.add_mesh(
			sge::camera::matrix_conversion::world(
				camera_.coordinate_system()) *
			fcppt::math::matrix::translation(
				_entity.position().get()) *
			_entity.rotation().get() *
			fcppt::math::matrix::scaling(
				_entity.scale().get()),
			mesh.index_buffer(),
			material_name_and_index_buffer_range->second);
	}
}
