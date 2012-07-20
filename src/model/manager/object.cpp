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
#include <sge/camera/matrix_conversion/world.hpp>
#include <sge/renderer/texture/address_mode2.hpp>
#include <sge/renderer/texture/set_address_mode2.hpp>
#include <sge/model/manager/object.hpp>
#include <sge/model/manager/vf/format.hpp>
#include <sge/model/manager/vf/format_part.hpp>
#include <sge/model/manager/vf/from_obj_map.hpp>
#include <sge/model/obj/create.hpp>
#include <sge/model/obj/loader.hpp>
#include <sge/model/obj/vb_converter/convert.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/scoped_transform.hpp>
#include <sge/renderer/scoped_vertex_buffer.hpp>
#include <sge/renderer/scoped_vertex_declaration.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/vertex_declaration.hpp>
#include <sge/renderer/context/object.hpp>
#include <sge/renderer/state/cull_mode.hpp>
#include <sge/renderer/state/depth_func.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/scoped.hpp>
#include <sge/renderer/texture/create_planar_from_path.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/scoped.hpp>
#include <sge/renderer/texture/mipmap/all_levels.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error_message.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/filesystem/extension_without_dot.hpp>
#include <fcppt/filesystem/stem.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/operations.hpp>
#include <fcppt/config/external_end.hpp>


sge::model::manager::object::object(
	sge::renderer::device &_renderer,
	sge::image2d::system &_image_system,
	sge::camera::base &_camera,
	sge::model::manager::model_directory const &_model_directory,
	sge::model::manager::texture_directory const &_texture_directory)
:
	renderer_(
		_renderer),
	camera_(
		_camera),
	vertex_declaration_(
		renderer_.create_vertex_declaration(
		sge::renderer::vf::dynamic::make_format<sge::model::manager::vf::format>())),
	identifier_to_vertex_buffer_(),
	identifier_to_texture_(),
	model_loader_(
		sge::model::obj::create())
{
	for(
		boost::filesystem::directory_iterator current_file(
			_model_directory.get());
		current_file != boost::filesystem::directory_iterator();
		++current_file)
	{
		FCPPT_ASSERT_ERROR_MESSAGE(
			boost::filesystem::is_regular_file(
				*current_file),
			FCPPT_TEXT("The model directory is supposed to contain only models"));

		FCPPT_ASSERT_ERROR_MESSAGE(
			fcppt::filesystem::extension_without_dot(
				*current_file) == FCPPT_TEXT("obj"),
			FCPPT_TEXT("A model has non-.obj extension."));

		fcppt::string const stem =
			fcppt::filesystem::stem(
				*current_file);

		fcppt::container::ptr::insert_unique_ptr_map(
			identifier_to_vertex_buffer_,
			sge::model::manager::instance::identifier(
				stem),
			sge::model::obj::vb_converter::convert
			<
				sge::model::manager::vf::format_part,
				sge::model::manager::vf::from_obj_map
			>(
				renderer_,
				*vertex_declaration_,
				sge::renderer::resource_flags::none,
				*(model_loader_->load(
					*current_file))));

		boost::filesystem::path const texture_file(
			_texture_directory.get() / (stem+FCPPT_TEXT(".png")));

		FCPPT_ASSERT_ERROR_MESSAGE(
			boost::filesystem::is_regular_file(
				texture_file),
			FCPPT_TEXT("The texture corresponding to a model was not found."));

		fcppt::container::ptr::insert_unique_ptr_map(
			identifier_to_texture_,
			sge::model::manager::instance::identifier(
				stem),
			sge::renderer::texture::create_planar_from_path(
				texture_file,
				renderer_,
				_image_system,
				// -- Configurable --
				sge::renderer::texture::mipmap::all_levels(
					sge::renderer::texture::mipmap::auto_generate::yes),
				sge::renderer::resource_flags::none));
	}
}

void
sge::model::manager::object::render(
	sge::renderer::context::object &_context,
	sge::model::manager::instance::sequence const &_instances)
{
	sge::renderer::state::scoped scoped_state(
		_context,
		sge::renderer::state::list
			(sge::renderer::state::depth_func::less)
			(sge::renderer::state::cull_mode::counter_clockwise));

	sge::renderer::texture::set_address_mode2(
		_context,
		sge::renderer::texture::stage(0u),
		sge::renderer::texture::address_mode2(
			sge::renderer::texture::address_mode::repeat));

	sge::renderer::scoped_vertex_declaration scoped_vertex_declaration(
		_context,
		*vertex_declaration_);

	sge::model::manager::instance::identifier previous_identifier(
		fcppt::string(
			FCPPT_TEXT("")));

	// -- Configurable --
	sge::renderer::scoped_transform scoped_projection(
		_context,
		sge::renderer::matrix_mode::projection,
		camera_.projection_matrix().get());

	fcppt::scoped_ptr<sge::renderer::scoped_vertex_buffer> scoped_vb;
	fcppt::scoped_ptr<sge::renderer::texture::scoped> scoped_texture;
	fcppt::optional<sge::renderer::vertex_buffer &> current_vertex_buffer;

	// -- Configurable texture filter and address mode --

	for(
		sge::model::manager::instance::sequence::const_iterator child =
			_instances.begin();
		child != _instances.end();
		++child)
	{
		if(child->identifier() != previous_identifier)
		{
			vertex_buffer_map::iterator vertex_buffer =
				identifier_to_vertex_buffer_.find(
					child->identifier());

			current_vertex_buffer =
				fcppt::optional<sge::renderer::vertex_buffer &>(
					*(vertex_buffer->second));

			texture_map::iterator texture =
				identifier_to_texture_.find(
					child->identifier());

			FCPPT_ASSERT_ERROR_MESSAGE(
				vertex_buffer != identifier_to_vertex_buffer_.end() &&
				texture != identifier_to_texture_.end(),
				FCPPT_TEXT("Internal texture/vertex buffer identifier inconsistency"));

			scoped_vb.take(
				fcppt::make_unique_ptr<sge::renderer::scoped_vertex_buffer>(
					fcppt::ref(
						_context),
					fcppt::ref(
						*(vertex_buffer->second))));

			scoped_texture.take(
				fcppt::make_unique_ptr<sge::renderer::texture::scoped>(
					fcppt::ref(
						_context),
					fcppt::cref(
						*(texture->second)),
					sge::renderer::texture::stage(
						0u)));
		}

		sge::camera::coordinate_system::object const moved_coordinate_system(
			camera_.coordinate_system().right(),
			camera_.coordinate_system().up(),
			camera_.coordinate_system().forward(),
			sge::camera::coordinate_system::position(
				camera_.coordinate_system().position().get() +
				child->position().get()));

		sge::renderer::scoped_transform scoped_world(
			_context,
			sge::renderer::matrix_mode::world,
			sge::camera::matrix_conversion::world(
				moved_coordinate_system));

		FCPPT_ASSERT_ERROR_MESSAGE(
			current_vertex_buffer,
			FCPPT_TEXT("We have no vertex buffer to render to!"));

		_context.render_nonindexed(
			sge::renderer::first_vertex(
				0u),
			sge::renderer::vertex_count(
				current_vertex_buffer->size()),
			sge::renderer::primitive_type::triangle_list);
	}
}

sge::model::manager::object::~object()
{
}
