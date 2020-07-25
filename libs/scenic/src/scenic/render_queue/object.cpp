//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/context/core.hpp>
#include <sge/renderer/index/buffer_ref.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/vertex/buffer_ref.hpp>
#include <sge/scenic/texture_manager.hpp>
#include <sge/scenic/texture_manager_ref.hpp>
#include <sge/scenic/render_context/base.hpp>
#include <sge/scenic/render_context/transform_matrix_type.hpp>
#include <sge/scenic/render_queue/object.hpp>
#include <sge/scenic/scene/material/object.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <iterator>
#include <fcppt/config/external_end.hpp>


namespace
{

template<
	typename StateSequence
>
[[nodiscard]]
sge::scenic::render_queue::index_type
change_context_state(
	fcppt::reference<
		StateSequence
	> const _states,
	typename StateSequence::value_type _state
)
{
	// TODO(philipp): find_opt
	auto it =
		std::find(
			_states.get().cbegin(),
			_states.get().cend(),
			_state);

	if(it == _states.get().end())
	{
		_states.get().push_back(
			_state);

		it =
			std::prev(
				_states.get().end());
	}

	auto begin(
		_states.get().cbegin());

	return
		static_cast<sge::scenic::render_queue::index_type>(
			std::distance(
				begin,
				it
			)
		);
}
}

sge::scenic::render_queue::object::object(
	sge::scenic::texture_manager_ref const _texture_manager
)
:
	texture_manager_(
		_texture_manager),
	materials_(),
	vertex_buffers_(),
	meshes_(),
	current_material_(
		static_cast<sge::scenic::render_queue::index_type>(
			-1)),
	current_vertex_buffer_(
		static_cast<sge::scenic::render_queue::index_type>(
			-1))
{
}

void
sge::scenic::render_queue::object::current_material(
	sge::scenic::scene::material::object const &_material)
{
	sge::scenic::render_context::material::object const renderable_material(
		sge::scenic::render_context::diffuse_color(
			_material.diffuse_color().get()),
		sge::scenic::render_context::ambient_color(
			_material.ambient_color().get()),
		sge::scenic::render_context::specular_color(
			_material.specular_color().get()),
		sge::scenic::render_context::emissive_color(
			_material.emissive_color().get()),
		sge::scenic::render_context::material::shininess(
			_material.shininess().get()),
		_material.diffuse_texture().get().empty()
		?
			sge::scenic::render_context::material::diffuse_texture()
		:
			sge::scenic::render_context::material::diffuse_texture(
				fcppt::make_ref(
					texture_manager_.get().texture_for_path(
						_material.diffuse_texture().get()
					)
				)
			)
		,
		_material.specular_texture().get().empty()
		?
			sge::scenic::render_context::material::specular_texture()
		:
			sge::scenic::render_context::material::specular_texture(
				fcppt::make_ref(
					texture_manager_.get().texture_for_path(
						_material.specular_texture().get()
					)
				)
			)
	);

	current_material_ =
		change_context_state(
			fcppt::make_ref(
				materials_
			),
			renderable_material
		);
}

void
sge::scenic::render_queue::object::current_vertex_buffer(
	sge::renderer::vertex::buffer_ref const _vertex_buffer
)
{
	current_vertex_buffer_ =
		change_context_state(
			fcppt::make_ref(
				vertex_buffers_
			),
			&_vertex_buffer.get()
		);
}

void
sge::scenic::render_queue::object::add_mesh(
	sge::renderer::matrix4 const &_modelview,
	sge::renderer::index::buffer_ref const _index_buffer,
	sge::scenic::index_buffer_range const &_index_buffer_range)
{
	meshes_.push_back(
		sge::scenic::render_queue::mesh(
			current_material_,
			current_vertex_buffer_,
			_modelview,
			_index_buffer,
			_index_buffer_range
		)
	);
}

sge::scenic::render_queue::state_change_count
sge::scenic::render_queue::object::render(
	sge::scenic::render_context::base &_context)
{
	std::sort(
		meshes_.begin(),
		meshes_.end());

	auto const invalid_index =
		static_cast<index_type>(
			-1);

	index_type current_render_material{
		invalid_index
	};

	index_type current_render_vertex_buffer{
		invalid_index
	};

	sge::scenic::render_queue::state_change_count state_changes(
		0U);

	for(
		auto const &current_mesh
		:
		meshes_
	)
	{
		if(current_mesh.material() != current_render_material)
		{
			state_changes++;

			_context.material(
				materials_[
					static_cast<material_sequence::size_type>(
						current_mesh.material())]);

			current_render_material =
				current_mesh.material();
		}

		if(current_mesh.vertex_buffer() != current_render_vertex_buffer)
		{
			state_changes++;

			_context.vertex_buffer(
				*vertex_buffers_[
					static_cast<vertex_buffer_sequence::size_type>(
						current_mesh.vertex_buffer())]);

			current_render_vertex_buffer =
				current_mesh.vertex_buffer();
		}

		state_changes++;
		_context.transform(
			sge::scenic::render_context::transform_matrix_type::world,
			current_mesh.modelview());

		_context.render(
			current_mesh.index_buffer(),
			current_mesh.index_buffer_range());
	}

	return
		state_changes;
}

sge::scenic::render_queue::object::~object()
= default;
