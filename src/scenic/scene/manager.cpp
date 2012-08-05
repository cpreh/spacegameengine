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
#include <sge/camera/coordinate_system/object.hpp>
#include <sge/camera/first_person/object.hpp>
#include <sge/camera/matrix_conversion/world.hpp>
#include <sge/image/colors.hpp>
#include <sge/model/obj/instance.hpp>
#include <sge/model/obj/parse_mtllib.hpp>
#include <sge/scenic/render_context/object.hpp>
#include <sge/model/obj/prototype.hpp>
#include <sge/model/obj/vf/format.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/scoped_transform.hpp>
#include <sge/renderer/texture/filter/scoped.hpp>
#include <sge/renderer/texture/filter/mipmap.hpp>
#include <sge/renderer/texture/filter/object.hpp>
#include <sge/renderer/scoped_vertex_buffer.hpp>
#include <sge/renderer/scoped_vertex_declaration.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/vertex_declaration.hpp>
#include <sge/renderer/context/object.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/color.hpp>
#include <sge/renderer/state/cull_mode.hpp>
#include <sge/renderer/state/depth_func.hpp>
#include <sge/renderer/state/float.hpp>
#include <sge/renderer/state/fog_mode.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/scoped.hpp>
#include <sge/renderer/target/base.hpp>
#include <sge/renderer/target/viewport_size.hpp>
#include <sge/renderer/texture/scoped.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/scenic/exception.hpp>
#include <sge/scenic/scene/from_blender_file.hpp>
#include <sge/scenic/scene/manager.hpp>
#include <sge/scenic/scene/prototype.hpp>
#include <fcppt/cref.hpp>
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


sge::scenic::scene::manager::manager(
	sge::renderer::device &_renderer,
	sge::image2d::system &_image_loader,
	sge::viewport::manager &_viewport_manager,
	sge::camera::first_person::object &_camera,
	boost::filesystem::path const &_prototype_file,
	sge::scenic::model_base_path const &_model_base_path,
	sge::scenic::material_base_path const &_material_base_path,
	sge::scenic::texture_base_path const &_texture_base_path)
:
	camera_(
		_camera),
	model_base_path_(
		_model_base_path),
	material_base_path_(
		_material_base_path),
	texture_base_path_(
		_texture_base_path),
	prototype_(
		sge::scenic::scene::from_blender_file(
			_prototype_file)),
	camera_viewport_connection_(
		camera_,
		_renderer,
		_viewport_manager,
		prototype_->camera().near(),
		prototype_->camera().far(),
		prototype_->camera().fov()),
	model_vertex_declaration_(
		_renderer.create_vertex_declaration(
			sge::renderer::vf::dynamic::make_format<sge::model::obj::vf::format>())),
	model_name_to_instance_(),
	texture_manager_(
		_renderer,
		_image_loader),
	materials_(),
	state_changes_()
{
	this->load_meshes(
		_renderer);

	camera_.update_coordinate_system(
		prototype_->camera().coordinate_system());
}

void
sge::scenic::scene::manager::render(
	sge::renderer::context::object &_context)
{
	if(
		!sge::renderer::target::viewport_size(
			_context.target()).content())
		return;

	state_changes_ =
		0u;

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
			(sge::renderer::state::bool_::enable_lighting = true)
			(sge::renderer::state::depth_func::less)
			(sge::renderer::state::color::ambient_light_color = prototype_->ambient_color().get())
			(prototype_->fog() ? sge::renderer::state::fog_mode::linear : sge::renderer::state::fog_mode::off)
			(sge::renderer::state::cull_mode::counter_clockwise));

	sge::renderer::texture::filter::scoped scoped_filter(
		_context,
		sge::renderer::texture::stage(
			0u),
		sge::renderer::texture::filter::mipmap());

	fcppt::scoped_ptr<sge::renderer::state::scoped> scoped_fog_state;

	if(prototype_->fog())
	{
		scoped_fog_state.take(
			fcppt::make_unique_ptr<sge::renderer::state::scoped>(
				fcppt::ref(
					_context),
				fcppt::cref(
					sge::renderer::state::list
						(sge::renderer::state::float_::fog_start = prototype_->fog()->start().get())
						(sge::renderer::state::float_::fog_end = prototype_->fog()->end().get())
						(sge::renderer::state::color::fog_color = prototype_->fog()->color().get()))));
	}

	this->activate_lights(
		_context);

	sge::scenic::render_context::object current_render_context;
	for(
		sge::scenic::mesh_sequence::const_iterator it =
			prototype_->meshes().begin();
		it != prototype_->meshes().end();
		++it)
		/*
		this->render_mesh(
			*it,
			_context);
		*/
		this->render_mesh_better(
			*it,
			current_render_context);

	std::cout << prototype_->meshes().size() << " meshes, " << current_render_context.render(_context).get() << " state changes\n";
}

sge::scenic::scene::manager::~manager()
{
}

void
sge::scenic::scene::manager::load_meshes(
	sge::renderer::device &_renderer)
{
	for(
		sge::scenic::mesh_sequence::const_iterator current_mesh =
			prototype_->meshes().begin();
		current_mesh != prototype_->meshes().end();
		++current_mesh)
	{
		fcppt::string const model_name(
			current_mesh->model().get());

		model_name_to_instance_map::iterator model_name_and_instance(
			model_name_to_instance_.find(
				model_name));

		if(model_name_and_instance != model_name_to_instance_.end())
			continue;

		sge::model::obj::prototype const new_prototype(
			model_base_path_.get() / (model_name+FCPPT_TEXT(".obj")));

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

		fcppt::container::ptr::insert_unique_ptr_map(
			model_name_to_instance_,
			model_name,
			fcppt::make_unique_ptr<sge::model::obj::instance>(
				fcppt::ref(
					_renderer),
				fcppt::ref(
					*model_vertex_declaration_),
				fcppt::cref(
					new_prototype)));
	}
}

void
sge::scenic::scene::manager::activate_lights(
	sge::renderer::context::object &_context)
{
	sge::renderer::scoped_transform scoped_world(
		_context,
		sge::renderer::matrix_mode::world,
		sge::camera::matrix_conversion::world(
			camera_.coordinate_system()));

	if(prototype_->lights().size() > 8u)
		throw
			sge::scenic::exception(
				FCPPT_TEXT("Found more than 8 lights in the scene.\nThat's currently not supported."));

	sge::renderer::light::index current_light_index(
		0u);

	for(
		sge::scenic::light_sequence::const_iterator current_light =
			prototype_->lights().begin();
		current_light != prototype_->lights().end();
		current_light++)
	{
		_context.enable_light(
			current_light_index,
			true);

		_context.light(
			current_light_index,
			*current_light);

		++current_light_index;
	}
}

void
sge::scenic::scene::manager::render_mesh(
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
		_mesh.rotation().get() *
		fcppt::math::matrix::scaling(
			_mesh.scale().get()));

	state_changes_++;

	sge::model::obj::instance &model(
		*(model_name_to_instance_.find(
			_mesh.model().get())->second));

	sge::renderer::scoped_vertex_buffer scoped_vertex_buffer(
		_context,
		model.vertex_buffer());

	state_changes_++;

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

		state_changes_++;

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

			state_changes_++;
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
sge::scenic::scene::manager::render_mesh_better(
	sge::scenic::mesh const &_mesh,
	sge::scenic::render_context::object &_context)
{
	sge::model::obj::instance &model(
		*(model_name_to_instance_.find(
			_mesh.model().get())->second));

	_context.current_vertex_buffer(
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

		_context.current_material(
			material.renderer_material());

		if(material.texture().get().empty())
		{
			_context.current_texture(
				fcppt::optional<sge::renderer::texture::planar &>());
		}
		else
		{
			_context.current_texture(
				fcppt::optional<sge::renderer::texture::planar &>(
					texture_manager_.texture_for_path(
						texture_base_path_.get() / material.texture().get())));
		}

		_context.add_mesh(
			sge::camera::matrix_conversion::world(
				camera_.coordinate_system()) *
			fcppt::math::matrix::translation(
				_mesh.position().get()) *
			_mesh.rotation().get() *
			fcppt::math::matrix::scaling(
				_mesh.scale().get()),
			model.index_buffer(),
			material_name_and_index_buffer_range->second);
	}
}
