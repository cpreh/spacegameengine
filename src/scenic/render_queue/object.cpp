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


#include <sge/renderer/default_material.hpp>
#include <sge/renderer/material.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/context/object.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/scenic/render_context/base.hpp>
#include <sge/scenic/render_queue/object.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/next_prior.hpp>
#include <algorithm>
#include <iterator>
#include <fcppt/config/external_end.hpp>


namespace
{
template<typename StateSequence>
void
change_context_state(
	StateSequence &_states,
	typename StateSequence::value_type _state_ptr,
	sge::scenic::render_queue::index_type &_current_state)
{
	typename StateSequence::const_iterator it =
		std::find(
			_states.begin(),
			_states.end(),
			_state_ptr);

	if(it == _states.end())
	{
		_states.push_back(
			_state_ptr);

		it =
			boost::prior(
				_states.end());
	}

	typename StateSequence::const_iterator begin(
		_states.begin());

	_current_state =
		static_cast<
			sge::scenic::render_queue::index_type
		>(
			std::distance(
				begin,
				it));
}
}

sge::scenic::render_queue::object::object()
:
	materials_(),
	vertex_buffers_(),
	diffuse_textures_(),
	specular_textures_(),
	meshes_(),
	current_material_(
		static_cast<sge::scenic::render_queue::index_type>(
			-1)),
	current_vertex_buffer_(
		static_cast<sge::scenic::render_queue::index_type>(
			-1)),
	current_diffuse_texture_(
		static_cast<sge::scenic::render_queue::index_type>(
			-1)),
	current_specular_texture_(
		static_cast<sge::scenic::render_queue::index_type>(
			-1))
{
}

void
sge::scenic::render_queue::object::current_material(
	sge::renderer::material const &_material)
{
	change_context_state(
		materials_,
		&_material,
		current_material_);
}

void
sge::scenic::render_queue::object::current_vertex_buffer(
	sge::renderer::vertex_buffer &_vertex_buffer)
{
	change_context_state(
		vertex_buffers_,
		&_vertex_buffer,
		current_vertex_buffer_);
}

void
sge::scenic::render_queue::object::current_diffuse_texture(
	fcppt::optional<sge::renderer::texture::planar &> _texture)
{
	if(_texture)
		change_context_state(
			diffuse_textures_,
			&(*_texture),
			current_diffuse_texture_);
	else
		change_context_state(
			diffuse_textures_,
			0,
			current_diffuse_texture_);
}

void
sge::scenic::render_queue::object::current_specular_texture(
	fcppt::optional<sge::renderer::texture::planar &> _texture)
{
	if(_texture)
		change_context_state(
			specular_textures_,
			&(*_texture),
			current_specular_texture_);
	else
		change_context_state(
			specular_textures_,
			0,
			current_specular_texture_);
}

void
sge::scenic::render_queue::object::add_mesh(
	sge::renderer::matrix4 const &_modelview,
	sge::renderer::index_buffer &_index_buffer,
	sge::scenic::index_buffer_range const &_index_buffer_range)
{
	meshes_.push_back(
		sge::scenic::render_queue::mesh(
			current_material_,
			current_vertex_buffer_,
			current_diffuse_texture_,
			current_specular_texture_,
			_modelview,
			_index_buffer,
			_index_buffer_range));
}

sge::scenic::render_queue::state_change_count const
sge::scenic::render_queue::object::render(
	sge::scenic::render_context::base &_context)
{
	std::sort(
		meshes_.begin(),
		meshes_.end());

	index_type const invalid_index =
		static_cast<index_type>(
			-1);

	index_type
		current_render_material =
			invalid_index,
		current_render_vertex_buffer =
			invalid_index,
		current_render_diffuse_texture =
			invalid_index,
		current_render_specular_texture =
			invalid_index;

	sge::scenic::render_queue::state_change_count state_changes(
		0u);

	for(
		mesh_sequence::const_iterator current_mesh =
			meshes_.begin();
		current_mesh != meshes_.end();
		++current_mesh)
	{
		if(current_mesh->material() != current_render_material)
		{
			state_changes++;

			_context.material(
				*materials_[
					static_cast<material_sequence::size_type>(
						current_mesh->material())]);

			current_render_material =
				current_mesh->material();
		}

		if(current_mesh->vertex_buffer() != current_render_vertex_buffer)
		{
			state_changes++;

			_context.vertex_buffer(
				*vertex_buffers_[
					static_cast<vertex_buffer_sequence::size_type>(
						current_mesh->vertex_buffer())]);

			current_render_vertex_buffer =
				current_mesh->vertex_buffer();
		}

		if(current_mesh->diffuse_texture() != current_render_diffuse_texture)
		{
			state_changes++;

			if(current_mesh->diffuse_texture() == invalid_index || !diffuse_textures_[static_cast<texture_sequence::size_type>(current_mesh->diffuse_texture())])
				_context.diffuse_texture(
					sge::scenic::render_context::optional_planar_texture());
			else
				_context.diffuse_texture(
					sge::scenic::render_context::optional_planar_texture(
						*diffuse_textures_[
							static_cast<texture_sequence::size_type>(
								current_mesh->diffuse_texture())]));

			current_render_diffuse_texture =
				current_mesh->diffuse_texture();
		}

		if(current_mesh->specular_texture() != current_render_specular_texture)
		{
			state_changes++;

			if(current_mesh->specular_texture() == invalid_index || !specular_textures_[static_cast<texture_sequence::size_type>(current_mesh->specular_texture())])
				_context.specular_texture(
					sge::scenic::render_context::optional_planar_texture());
			else
				_context.specular_texture(
					sge::scenic::render_context::optional_planar_texture(
						*specular_textures_[
							static_cast<texture_sequence::size_type>(
								current_mesh->specular_texture())]));

			current_render_specular_texture =
				current_mesh->specular_texture();
		}

		state_changes++;
		_context.transform(
			sge::renderer::matrix_mode::world,
			current_mesh->modelview());

		_context.render(
			current_mesh->index_buffer(),
			current_mesh->index_buffer_range());
	}

	return
		state_changes;
}

sge::scenic::render_queue::object::~object()
{
}
