/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/renderer/primitive_type.hpp>
#include <sge/renderer/context/core.hpp>
#include <sge/renderer/state/core/sampler/const_object_ref.hpp>
#include <sge/renderer/state/core/sampler/const_object_ref_map.hpp>
#include <sge/renderer/vertex/buffer.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <sge/scenic/index_buffer_range.hpp>
#include <sge/scenic/render_context/transform_matrix_type.hpp>
#include <sge/scenic/render_context/cg/manager.hpp>
#include <sge/scenic/render_context/cg/object.hpp>
#include <sge/scenic/render_context/cg/light/count.hpp>
#include <sge/scenic/render_context/cg/light/directional.hpp>
#include <sge/scenic/render_context/cg/light/point.hpp>
#include <sge/scenic/render_context/fog/optional_properties.hpp>
#include <sge/scenic/render_context/fog/properties.hpp>
#include <sge/scenic/render_context/light/object.hpp>
#include <sge/scenic/render_context/material/object.hpp>
#include <sge/src/scenic/render_context/cg/any_color_to_vector4.hpp>
#include <fcppt/maybe_void.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/assign/make_map.hpp>
#include <fcppt/math/matrix/arithmetic.hpp>
#include <fcppt/math/matrix/identity.hpp>
#include <fcppt/math/matrix/inverse.hpp>
#include <fcppt/math/matrix/transform_point.hpp>
#include <fcppt/math/matrix/transpose.hpp>
#include <fcppt/variant/to_optional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <fcppt/config/external_end.hpp>


sge::scenic::render_context::cg::object::object(
	sge::scenic::render_context::cg::manager &_manager,
	sge::renderer::context::core &_context)
:
	sge::scenic::render_context::base(),
	manager_(
		_manager),
	context_(
		_context),
	scoped_vd_(
		_context,
		_manager.vertex_declaration_),
	depth_stencil_state_(
		_context,
		*manager_.depth_stencil_state_),
	blend_state_(
		_context,
		*manager_.blend_state_),
	rasterizer_state_(
		_context,
		*manager_.rasterizer_state_),
	scoped_shader_(
		_context,
		manager_.shader_),
	sampler_state_(
		_context,
		fcppt::assign::make_map<sge::renderer::state::core::sampler::const_object_ref_map>
			(
				// I'd love to write this, but for this, the texture would have to be scoped, which it isn't yet
				//manager_.diffuse_texture_.stage(),
				sge::renderer::texture::stage(
					0u),
				sge::renderer::state::core::sampler::const_object_ref(
					*manager_.mipmap_sampler_state_))
			(
				// I'd love to write this, but for this, the texture would have to be scoped, which it isn't yet
				//manager_.specular_texture_.stage(),
				sge::renderer::texture::stage(
					1u),
				sge::renderer::state::core::sampler::const_object_ref(
					*manager_.mipmap_sampler_state_))),
	current_world_(
		fcppt::math::matrix::identity<
			sge::renderer::matrix4
		>()
	),
	current_projection_(
		fcppt::math::matrix::identity<
			sge::renderer::matrix4
		>()
	),
	current_vertex_buffer_()
{
}

void
sge::scenic::render_context::cg::object::transform(
	sge::scenic::render_context::transform_matrix_type const _matrix_mode,
	sge::renderer::matrix4 const &_matrix)
{
	switch(_matrix_mode)
	{
	case sge::scenic::render_context::transform_matrix_type::world:
		current_world_ =
			_matrix;

		manager_.world_matrix_.set(
			current_world_);

		manager_.world_inverse_transpose_matrix_.set(
			fcppt::math::matrix::inverse(
				fcppt::math::matrix::transpose(
					current_world_)));

		manager_.world_projection_matrix_.set(
			current_projection_ * current_world_);
		break;
	case sge::scenic::render_context::transform_matrix_type::projection:
		current_projection_ =
			_matrix;

		manager_.world_projection_matrix_.set(
			current_projection_ * current_world_);
		break;
	}
}

void
sge::scenic::render_context::cg::object::material(
	sge::scenic::render_context::material::object const &_material)
{
	manager_.material_diffuse_color_.set(
		sge::scenic::render_context::cg::any_color_to_vector4(
			_material.diffuse_color().get()));

	manager_.material_specular_color_.set(
		sge::scenic::render_context::cg::any_color_to_vector4(
			_material.specular_color().get()));

	manager_.material_emissive_color_.set(
		sge::scenic::render_context::cg::any_color_to_vector4(
			_material.emissive_color().get()));

	manager_.material_ambient_color_.set(
		sge::scenic::render_context::cg::any_color_to_vector4(
			_material.ambient_color().get()));

	manager_.material_shininess_.set(
		_material.shininess().get());

	manager_.use_diffuse_texture_.set(
		_material.diffuse_texture().has_value());

	manager_.diffuse_texture_.set(
		_material.diffuse_texture().has_value()
		?
			sge::shader::parameter::planar_texture::optional_value(
				_material.diffuse_texture())
		:
			sge::shader::parameter::planar_texture::optional_value());

	manager_.use_specular_texture_.set(
		_material.specular_texture().has_value());

	manager_.specular_texture_.set(
		_material.specular_texture().has_value()
		?
			sge::shader::parameter::planar_texture::optional_value(
				_material.specular_texture())
		:
			sge::shader::parameter::planar_texture::optional_value());
}

void
sge::scenic::render_context::cg::object::lights(
	sge::scenic::render_context::light::sequence const &_lights)
{
	sge::scenic::render_context::cg::light::count point_light_count = 0;
	sge::scenic::render_context::cg::light::count directional_light_count = 0;

	for(
		sge::scenic::render_context::light::object const &light
		:
		_lights
	)
	{
		// TODO: This should be done using a visitor!
		fcppt::maybe_void(
			fcppt::variant::to_optional<
				sge::scenic::render_context::light::point
			>(
				light.variant()
			),
			[
				&light,
				&point_light_count,
				this
			](
				sge::scenic::render_context::light::point const _point_light
			)
			{
				sge::scenic::render_context::cg::light::point &current_light(
					*manager_.point_lights_[static_cast<std::size_t>(point_light_count++)]);

				current_light.diffuse_color(
					light.diffuse_color());

				current_light.specular_color(
					light.specular_color());

				current_light.ambient_color(
					light.ambient_color());

				current_light.camera_space_position(
					fcppt::math::matrix::transform_point(
						current_world_,
						_point_light.position().get()));

				current_light.attenuation(
					_point_light.attenuation());
			}
		);

		fcppt::maybe_void(
			fcppt::variant::to_optional<
				sge::scenic::render_context::light::directional
			>(
				light.variant()
			),
			[
				&light,
				&directional_light_count,
				this
			](
				sge::scenic::render_context::light::directional const &_directional_light
			)
			{
				sge::scenic::render_context::cg::light::directional &current_light(
					*manager_.directional_lights_[static_cast<std::size_t>(directional_light_count++)]
				);

				current_light.diffuse_color(
					light.diffuse_color());

				current_light.specular_color(
					light.specular_color());

				current_light.ambient_color(
					light.ambient_color());

				current_light.camera_space_direction(
					sge::scenic::render_context::light::direction(
						fcppt::math::vector::narrow_cast<sge::renderer::vector3>(
							current_world_ *
							fcppt::math::vector::construct(
								_directional_light.direction().get(),
								static_cast<sge::renderer::scalar>(
									0.0f)))));
			}
		);
	}

	manager_.point_light_count_.set(
		point_light_count);

	manager_.directional_light_count_.set(
		directional_light_count);
}

void
sge::scenic::render_context::cg::object::vertex_buffer(
	sge::renderer::vertex::buffer const &_new_vertex_buffer
)
{
	fcppt::maybe_void(
		current_vertex_buffer_,
		[
			this
		](
			sge::renderer::vertex::buffer const &_vertex_buffer
		)
		{
			context_.deactivate_vertex_buffer(
				_vertex_buffer
			);
		}
	);


	current_vertex_buffer_ =
		optional_vertex_buffer(
			_new_vertex_buffer);

	context_.activate_vertex_buffer(
		_new_vertex_buffer
	);
}

void
sge::scenic::render_context::cg::object::fog(
	sge::scenic::render_context::fog::optional_properties const &_opt_fog)
{
	manager_.use_fog_.set(
		_opt_fog.has_value());

	fcppt::maybe_void(
		_opt_fog,
		[
			this
		](
			sge::scenic::render_context::fog::properties const &_fog
		)
		{
			manager_.fog_start_.set(
				_fog.start().get());
			manager_.fog_end_.set(
				_fog.end().get());
			manager_.fog_color_.set(
				sge::scenic::render_context::cg::any_color_to_vector4(
					_fog.color().get()));
		}
	);
}

void
sge::scenic::render_context::cg::object::render(
	sge::renderer::index::buffer const &_index_buffer,
	sge::scenic::index_buffer_range const &_index_buffer_range)
{
	context_.render_indexed(
		_index_buffer,
		sge::renderer::vertex::first(
			0u),
		sge::renderer::vertex::count(
			FCPPT_ASSERT_OPTIONAL_ERROR(
				current_vertex_buffer_
			).linear_size()),
		sge::renderer::primitive_type::triangle_list,
		_index_buffer_range.first_index(),
		_index_buffer_range.index_count());
}

sge::renderer::target::base &
sge::scenic::render_context::cg::object::target()
{
	return
		context_.target();
}

sge::scenic::render_context::cg::object::~object()
{
	fcppt::maybe_void(
		current_vertex_buffer_,
		[
			this
		](
			sge::renderer::vertex::buffer const &_vertex_buffer
		)
		{
			context_.deactivate_vertex_buffer(
				_vertex_buffer
			);
		}
	);
}
