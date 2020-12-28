//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/primitive_type.hpp>
#include <sge/renderer/context/core.hpp>
#include <sge/renderer/context/core_ref.hpp>
#include <sge/renderer/state/core/sampler/const_object_ref.hpp>
#include <sge/renderer/state/core/sampler/const_object_ref_map.hpp>
#include <sge/renderer/vertex/buffer.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <sge/scenic/index_buffer_range.hpp>
#include <sge/scenic/impl/render_context/cg/any_color_to_vector4.hpp>
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
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/math/matrix/arithmetic.hpp>
#include <fcppt/math/matrix/identity.hpp>
#include <fcppt/math/matrix/inverse.hpp>
#include <fcppt/math/matrix/transform_point.hpp>
#include <fcppt/math/matrix/transpose.hpp>
#include <fcppt/math/vector/narrow_cast.hpp>
#include <fcppt/math/vector/push_back.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/variant/to_optional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <fcppt/config/external_end.hpp>


sge::scenic::render_context::cg::object::object(
	fcppt::reference<
		sge::scenic::render_context::cg::manager
	> const _manager,
	sge::renderer::context::core_ref const _context
)
:
	sge::scenic::render_context::base(),
	manager_(
		_manager
	),
	context_(
		_context
	),
	scoped_vd_(
		_context,
		_manager.get().vertex_declaration_
	),
	depth_stencil_state_(
		_context,
		fcppt::make_cref(
			*manager_.get().depth_stencil_state_
		)
	),
	blend_state_(
		_context,
		fcppt::make_cref(
			*manager_.get().blend_state_
		)
	),
	rasterizer_state_(
		_context,
		fcppt::make_cref(
			*manager_.get().rasterizer_state_
		)
	),
	scoped_shader_(
		_context,
		fcppt::make_ref(
			manager_.get().shader_
		)
	),
	sampler_state_{
		_context,
		sge::renderer::state::core::sampler::const_object_ref_map{
			sge::renderer::state::core::sampler::const_object_ref_map::value_type{
				// I'd love to write this, but for this, the texture would have to be scoped, which it isn't yet
				//manager_.diffuse_texture_.stage(),
				sge::renderer::texture::stage{
					0U
				},
				sge::renderer::state::core::sampler::const_object_ref{
					*manager_.get().mipmap_sampler_state_
				}
			},
			sge::renderer::state::core::sampler::const_object_ref_map::value_type{
				// I'd love to write this, but for this, the texture would have to be scoped, which it isn't yet
				//manager_.specular_texture_.stage(),
				sge::renderer::texture::stage{
					1U
				},
				sge::renderer::state::core::sampler::const_object_ref{
					*manager_.get().mipmap_sampler_state_
				}
			}
		}
	},
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
	sge::renderer::matrix4 const &_matrix
)
{
	switch(
		_matrix_mode
	)
	{
	case sge::scenic::render_context::transform_matrix_type::world:
		current_world_ =
			_matrix;

		manager_.get().world_matrix_.set(
			current_world_);

		manager_.get().world_inverse_transpose_matrix_.set(
			fcppt::math::matrix::inverse(
				fcppt::math::matrix::transpose(
					current_world_
				)
			)
		);

		manager_.get().world_projection_matrix_.set(
			current_projection_ * current_world_
		);
		break;
	case sge::scenic::render_context::transform_matrix_type::projection:
		current_projection_ =
			_matrix;

		manager_.get().world_projection_matrix_.set(
			current_projection_ * current_world_
		);
		break;
	}
}

void
sge::scenic::render_context::cg::object::material(
	sge::scenic::render_context::material::object const &_material)
{
	manager_.get().material_diffuse_color_.set(
		sge::scenic::impl::render_context::cg::any_color_to_vector4(
			_material.diffuse_color().get()));

	manager_.get().material_specular_color_.set(
		sge::scenic::impl::render_context::cg::any_color_to_vector4(
			_material.specular_color().get()));

	manager_.get().material_emissive_color_.set(
		sge::scenic::impl::render_context::cg::any_color_to_vector4(
			_material.emissive_color().get()));

	manager_.get().material_ambient_color_.set(
		sge::scenic::impl::render_context::cg::any_color_to_vector4(
			_material.ambient_color().get()));

	manager_.get().material_shininess_.set(
		_material.shininess().get());

	manager_.get().use_diffuse_texture_.set(
		_material.diffuse_texture().has_value());

	manager_.get().diffuse_texture_.set(
		_material.diffuse_texture().has_value()
		?
			sge::shader::parameter::planar_texture::optional_value(
				_material.diffuse_texture())
		:
			sge::shader::parameter::planar_texture::optional_value());

	manager_.get().use_specular_texture_.set(
		_material.specular_texture().has_value());

	manager_.get().specular_texture_.set(
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
		// TODO(philipp): This should be done using a visitor!
		fcppt::optional::maybe_void(
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
				sge::scenic::render_context::light::point const &_point_light
			)
			{
				sge::scenic::render_context::cg::light::point &current_light(
					*manager_.get().point_lights_.get_unsafe(static_cast<std::size_t>(point_light_count++)));

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

		fcppt::optional::maybe_void(
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
					*manager_.get().directional_lights_.get_unsafe(static_cast<std::size_t>(directional_light_count++))
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
							fcppt::math::vector::push_back(
								_directional_light.direction().get(),
								static_cast<sge::renderer::scalar>(
									0.0f)))));
			}
		);
	}

	manager_.get().point_light_count_.set(
		point_light_count);

	manager_.get().directional_light_count_.set(
		directional_light_count);
}

void
sge::scenic::render_context::cg::object::vertex_buffer(
	sge::renderer::vertex::buffer const &_new_vertex_buffer
)
{
	fcppt::optional::maybe_void(
		current_vertex_buffer_,
		[
			this
		](
			fcppt::reference<
				sge::renderer::vertex::buffer const
			> const _vertex_buffer
		)
		{
			context_.get().deactivate_vertex_buffer(
				_vertex_buffer.get()
			);
		}
	);


	current_vertex_buffer_ =
		optional_vertex_buffer(
			fcppt::make_cref(
				_new_vertex_buffer
			)
		);

	context_.get().activate_vertex_buffer(
		fcppt::make_cref(
			_new_vertex_buffer
		)
	);
}

void
sge::scenic::render_context::cg::object::fog(
	sge::scenic::render_context::fog::optional_properties const &_opt_fog)
{
	manager_.get().use_fog_.set(
		_opt_fog.has_value());

	fcppt::optional::maybe_void(
		_opt_fog,
		[
			this
		](
			sge::scenic::render_context::fog::properties const &_fog
		)
		{
			manager_.get().fog_start_.set(
				_fog.start().get());
			manager_.get().fog_end_.set(
				_fog.end().get());
			manager_.get().fog_color_.set(
				sge::scenic::impl::render_context::cg::any_color_to_vector4(
					_fog.color().get()));
		}
	);
}

void
sge::scenic::render_context::cg::object::render(
	sge::renderer::index::buffer const &_index_buffer,
	sge::scenic::index_buffer_range const &_index_buffer_range)
{
	context_.get().render_indexed(
		_index_buffer,
		sge::renderer::vertex::first(
			0U
		),
		sge::renderer::vertex::count(
			FCPPT_ASSERT_OPTIONAL_ERROR(
				current_vertex_buffer_
			).get().linear_size()
		),
		sge::renderer::primitive_type::triangle_list,
		_index_buffer_range.first_index(),
		_index_buffer_range.index_count()
	);
}

sge::renderer::target::base &
sge::scenic::render_context::cg::object::target()
{
	return
		context_.get().target();
}

sge::scenic::render_context::cg::object::~object()
{
	fcppt::optional::maybe_void(
		current_vertex_buffer_,
		[
			this
		](
			fcppt::reference<
				sge::renderer::vertex::buffer const
			> const _vertex_buffer
		)
		{
			context_.get().deactivate_vertex_buffer(
				_vertex_buffer.get()
			);
		}
	);
}
