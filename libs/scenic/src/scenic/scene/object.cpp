//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/camera/base.hpp>
#include <sge/camera/has_mutable_projection.hpp>
#include <sge/camera/projection_matrix.hpp>
#include <sge/camera/coordinate_system/object.hpp>
#include <sge/camera/matrix_conversion/world.hpp>
#include <sge/model/obj/parse_mtllib.hpp>
#include <sge/model/obj/prototype.hpp>
#include <sge/renderer/target/base.hpp>
#include <sge/renderer/target/viewport_size.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/scenic/exception.hpp>
#include <sge/scenic/render_context/base.hpp>
#include <sge/scenic/render_context/transform_matrix_type.hpp>
#include <sge/scenic/render_context/fog/properties.hpp>
#include <sge/scenic/render_queue/object.hpp>
#include <sge/scenic/scene/manager.hpp>
#include <sge/scenic/scene/object.hpp>
#include <sge/scenic/scene/prototype.hpp>
#include <sge/scenic/scene/material/from_obj_material.hpp>
#include <sge/scenic/scene/mesh/object.hpp>
#include <sge/scenic/vf/format.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/math/dim/contents.hpp>
#include <fcppt/math/matrix/arithmetic.hpp>
#include <fcppt/math/matrix/scaling.hpp>
#include <fcppt/math/matrix/translation.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::scenic::scene::object::object(
	fcppt::log::context &_log_context,
	sge::scenic::scene::manager &_scene_manager,
	sge::viewport::manager &_viewport_manager,
	sge::camera::base &_camera,
	sge::scenic::scene::prototype_unique_ptr _prototype)
:
	log_context_{
		_log_context
	},
	scene_manager_(
		_scene_manager),
	camera_(
		_camera),
	prototype_(
		std::move(
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
	state_changes_{
		0u
	}
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
		fcppt::math::dim::contents(
			sge::renderer::target::viewport_size(
				_context.target()
			)
		)
		==
		0u
	)
		return;

	fcppt::optional::maybe_void(
		camera_.projection_matrix(),
		[
			&_context,
			this
		](
			sge::camera::projection_matrix const &_projection
		)
		{
			state_changes_ =
				0u;

			_context.transform(
				sge::scenic::render_context::transform_matrix_type::projection,
				_projection.get()
			);

			this->activate_lights(
				_context);

			_context.fog(
				prototype_->fog());

			sge::scenic::render_queue::object current_render_queue(
				scene_manager_.texture_manager());

			for(
				// TODO: range-based loop
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
		}
	);
}

sge::scenic::scene::object::~object()
{
}

void
sge::scenic::scene::object::load_entities()
{
	for(
		sge::scenic::scene::entity const &current_entity
		:
		prototype_->entities()
	)
	{
		// TODO: find_opt
		mesh_map::iterator const mesh_name_and_instance(
			mesh_name_to_instance_.find(
				current_entity.mesh_path()));

		if(mesh_name_and_instance != mesh_name_to_instance_.end())
			continue;

		sge::model::obj::prototype const new_prototype(
			log_context_,
			current_entity.mesh_path().get()
		);

		for(
			std::filesystem::path const &current_material_file
			:
			new_prototype.material_files()
		)
		{
			sge::model::obj::material_map const new_materials(
				sge::model::obj::parse_mtllib(
					log_context_,
					current_material_file
				)
			);

			for(
				auto const &current_obj_material
				:
				new_materials
			)
			{
				materials_.insert(
					std::make_pair(
						sge::scenic::scene::identifier(
							current_obj_material.first.get()
						),
						sge::scenic::scene::material::from_obj_material(
							current_obj_material.second
						)
					)
				);
			}
		}

		mesh_name_to_instance_.insert(
			std::make_pair(
				current_entity.mesh_path(),
				sge::scenic::scene::mesh::object(
					scene_manager_.renderer(),
					scene_manager_.vertex_declaration(),
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
		mesh_name_to_instance_.find(
			_entity.mesh_path())->second);

	_context.current_vertex_buffer(
		mesh.vertex_buffer());

	for(
		auto const &material_name_and_index_buffer_range
		:
		mesh.parts()
	)
	{
		material_map::const_iterator const material_name_and_material =
			materials_.find(
				material_name_and_index_buffer_range.first);

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
			material_name_and_index_buffer_range.second);
	}
}
