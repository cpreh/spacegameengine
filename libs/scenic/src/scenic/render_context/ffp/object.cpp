/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/image/color/predef.hpp>
#include <sge/renderer/primitive_type.hpp>
#include <sge/renderer/caps/device.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/state/core/blend/object.hpp>
#include <sge/renderer/state/core/blend/parameters.hpp>
#include <sge/renderer/state/core/blend/write_mask_all.hpp>
#include <sge/renderer/state/core/depth_stencil/object.hpp>
#include <sge/renderer/state/core/depth_stencil/parameters.hpp>
#include <sge/renderer/state/core/rasterizer/object.hpp>
#include <sge/renderer/state/core/rasterizer/parameters.hpp>
#include <sge/renderer/state/core/sampler/object.hpp>
#include <sge/renderer/state/core/sampler/parameters.hpp>
#include <sge/renderer/state/core/sampler/address/mode_all.hpp>
#include <sge/renderer/state/core/sampler/address/parameters.hpp>
#include <sge/renderer/state/core/sampler/filter/trilinear.hpp>
#include <sge/renderer/state/ffp/lighting/diffuse_from_vertex.hpp>
#include <sge/renderer/state/ffp/lighting/enabled.hpp>
#include <sge/renderer/state/ffp/lighting/object.hpp>
#include <sge/renderer/state/ffp/lighting/parameters.hpp>
#include <sge/renderer/state/ffp/lighting/light/const_object_ref_vector.hpp>
#include <sge/renderer/state/ffp/lighting/light/object.hpp>
#include <sge/renderer/state/ffp/lighting/light/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/lighting/light/parameters.hpp>
#include <sge/renderer/state/ffp/lighting/material/object.hpp>
#include <sge/renderer/state/ffp/lighting/material/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/lighting/material/parameters.hpp>
#include <sge/renderer/state/ffp/transform/mode.hpp>
#include <sge/renderer/state/ffp/transform/object.hpp>
#include <sge/renderer/state/ffp/transform/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/transform/parameters.hpp>
#include <sge/renderer/texture/base.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/vertex/buffer.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <sge/renderer/vertex/scoped_buffer.hpp>
#include <sge/scenic/index_buffer_range.hpp>
#include <sge/scenic/render_context/transform_matrix_type.hpp>
#include <sge/scenic/render_context/ffp/manager.hpp>
#include <sge/scenic/render_context/ffp/object.hpp>
#include <sge/scenic/render_context/material/object.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/optional/assign.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/variant/apply_unary.hpp>


namespace
{
struct light_visitor
{
	typedef
	sge::renderer::state::ffp::lighting::light::variant
	result_type;

	result_type
	operator()(
		sge::scenic::render_context::light::point const &p) const
	{
		return
			sge::renderer::state::ffp::lighting::light::variant{
				sge::renderer::state::ffp::lighting::light::point(
					sge::renderer::state::ffp::lighting::light::position(
						p.position().get()
					),
					sge::renderer::state::ffp::lighting::light::attenuation(
						sge::renderer::state::ffp::lighting::light::constant_attenuation(
							p.attenuation().constant_attenuation().get()
						),
						sge::renderer::state::ffp::lighting::light::linear_attenuation(
							p.attenuation().linear_attenuation().get()
						),
						sge::renderer::state::ffp::lighting::light::quadratic_attenuation(
							p.attenuation().quadratic_attenuation().get()
						)
					)
				)
			};
	}

	result_type
	operator()(
		sge::scenic::render_context::light::directional const &p) const
	{
		return
			sge::renderer::state::ffp::lighting::light::variant{
				sge::renderer::state::ffp::lighting::light::directional(
					sge::renderer::state::ffp::lighting::light::direction(
						p.direction().get()
					)
				)
			};
	}
};

sge::renderer::state::ffp::lighting::light::parameters
transform_light(
	sge::scenic::render_context::light::object const &_light)
{
	return
		sge::renderer::state::ffp::lighting::light::parameters(
			sge::renderer::state::ffp::lighting::diffuse_color(
				_light.diffuse_color().get()),
			sge::renderer::state::ffp::lighting::specular_color(
				_light.specular_color().get()),
			sge::renderer::state::ffp::lighting::ambient_color(
				_light.ambient_color().get()),
			fcppt::variant::apply_unary(
				light_visitor(),
				_light.variant()));
}
}

sge::scenic::render_context::ffp::object::object(
	sge::scenic::render_context::ffp::manager &_manager,
	sge::renderer::context::ffp &_context)
:
	manager_(
		_manager),
	context_(
		_context),
	scoped_vertex_declaration_(
		context_,
		manager_.vertex_declaration_),
	projection_transform_(),
	world_transform_(),
	current_vertex_buffer_size_(
		0u),
	current_vertex_buffer_(),
	current_material_(),
	diffuse_texture_sampler_(
		manager_.renderer_.create_sampler_state(
			sge::renderer::state::core::sampler::parameters(
				sge::renderer::state::core::sampler::address::parameters(
					sge::renderer::state::core::sampler::address::mode_all(
						sge::renderer::state::core::sampler::address::mode::repeat)),
				sge::renderer::state::core::sampler::filter::trilinear()))),
	scoped_sampler_{
		_context,
		sge::renderer::state::core::sampler::const_object_ref_map{
			sge::renderer::state::core::sampler::const_object_ref_map::value_type{
				sge::renderer::texture::stage{
					0u
				},
				fcppt::make_cref(
					*diffuse_texture_sampler_
				)
			}
		}
	},
	current_lighting_(
		manager_.renderer_.create_lighting_state(
			sge::renderer::state::ffp::lighting::parameters(
				sge::renderer::state::ffp::lighting::variant(
					sge::renderer::state::ffp::lighting::enabled(
						sge::renderer::state::ffp::lighting::ambient_color(
							sge::image::color::predef::black()
						),
						sge::renderer::state::ffp::lighting::diffuse_from_vertex(
							false
						)
					)
				)
			)
		)
	),
	depth_stencil_state_(
		manager_.renderer_.create_depth_stencil_state(
			sge::renderer::state::core::depth_stencil::parameters(
				sge::renderer::state::core::depth_stencil::depth::variant(
					sge::renderer::state::core::depth_stencil::depth::enabled(
						sge::renderer::state::core::depth_stencil::depth::func::less,
						sge::renderer::state::core::depth_stencil::depth::write_enable(
							true
						)
					)
				),
				sge::renderer::state::core::depth_stencil::stencil::variant(
					sge::renderer::state::core::depth_stencil::stencil::off()
				)
			)
		)
	),
	blend_state_(
		manager_.renderer_.create_blend_state(
			sge::renderer::state::core::blend::parameters(
				sge::renderer::state::core::blend::alpha_variant(
					sge::renderer::state::core::blend::alpha_off()
				),
				sge::renderer::state::core::blend::write_mask_all()
			)
		)
	),
	rasterizer_state_(
		manager_.renderer_.create_rasterizer_state(
			sge::renderer::state::core::rasterizer::parameters(
				sge::renderer::state::core::rasterizer::cull_mode::counter_clockwise,
				sge::renderer::state::core::rasterizer::fill_mode::solid,
				sge::renderer::state::core::rasterizer::enable_scissor_test(
					false
				)
			)
		)
	),
	scoped_depth_stencil_state_(
		_context,
		*depth_stencil_state_),
	scoped_blend_state_(
		_context,
		*blend_state_),
	scoped_rasterizer_state_(
		_context,
		*rasterizer_state_)
{
	context_.lighting_state(
		sge::renderer::state::ffp::lighting::const_optional_object_ref(
			fcppt::make_cref(
				*current_lighting_
			)
		)
	);
}

void
sge::scenic::render_context::ffp::object::transform(
	sge::scenic::render_context::transform_matrix_type const _type,
	sge::renderer::matrix4 const &_matrix)
{
	switch(
		_type
	)
	{
	case sge::scenic::render_context::transform_matrix_type::projection:
		{
			sge::renderer::state::ffp::transform::object_unique_ptr const &cur_transform(
				fcppt::optional::assign(
					projection_transform_,
					manager_.renderer_.create_transform_state(
						sge::renderer::state::ffp::transform::parameters(
							_matrix
						)
					)
				)
			);

			context_.transform(
				sge::renderer::state::ffp::transform::mode::projection,
				sge::renderer::state::ffp::transform::const_optional_object_ref(
					fcppt::make_cref(
						*cur_transform
					)
				)
			);

		break;
		}
	case sge::scenic::render_context::transform_matrix_type::world:
		{
			sge::renderer::state::ffp::transform::object_unique_ptr const &cur_transform(
				fcppt::optional::assign(
					world_transform_,
					manager_.renderer_.create_transform_state(
						sge::renderer::state::ffp::transform::parameters(
							_matrix
						)
					)
				)
			);

			context_.transform(
				sge::renderer::state::ffp::transform::mode::world,
				sge::renderer::state::ffp::transform::const_optional_object_ref(
					fcppt::make_cref(
						*cur_transform
					)
				)
			);

		break;
		}
	}
}

void
sge::scenic::render_context::ffp::object::material(
	sge::scenic::render_context::material::object const &_material)
{
	sge::renderer::state::ffp::lighting::material::object_unique_ptr const &current_material(
		fcppt::optional::assign(
			current_material_,
			manager_.renderer_.create_material_state(
				sge::renderer::state::ffp::lighting::material::parameters(
					sge::renderer::state::ffp::lighting::diffuse_color(
						_material.diffuse_color().get()),
					sge::renderer::state::ffp::lighting::ambient_color(
						_material.ambient_color().get()),
					sge::renderer::state::ffp::lighting::specular_color(
						_material.specular_color().get()),
					sge::renderer::state::ffp::lighting::material::emissive_color(
						_material.emissive_color().get()),
					sge::renderer::state::ffp::lighting::material::shininess(
						_material.shininess().get()
					)
				)
			)
		)
	);

	context_.material_state(
		sge::renderer::state::ffp::lighting::material::const_optional_object_ref(
			fcppt::make_cref(
				*current_material
			)
		)
	);

	context_.texture(
		fcppt::optional::map(
			_material.diffuse_texture(),
			[](
				fcppt::reference<
					sge::renderer::texture::planar
				> const _texture
			)
			{
				return
					fcppt::reference_to_base<
						sge::renderer::texture::base const
					>(
						_texture
					);
			}
		),
		sge::renderer::texture::stage(
			0u
		)
	);
}

void
sge::scenic::render_context::ffp::object::lights(
	sge::scenic::render_context::light::sequence const &_lights)
{
	FCPPT_ASSERT_PRE(
		_lights.size() < manager_.renderer_.caps().light_indices().get());

	context_.lights_state(
		sge::renderer::state::ffp::lighting::light::const_object_ref_vector());

	lights_ =
		fcppt::algorithm::map<
			light_ptr_vector
		>(
			_lights,
			[
				this
			](
				sge::scenic::render_context::light::object const &_light
			)
			{
				return
					manager_.renderer_.create_light_state(
						transform_light(
							_light
						)
					);
			}
		);

	context_.lights_state(
		fcppt::algorithm::map<
			sge::renderer::state::ffp::lighting::light::const_object_ref_vector
		>(
			lights_,
			[](
				sge::renderer::state::ffp::lighting::light::object_unique_ptr const &_light
			)
			{
				return
					fcppt::make_cref(
						*_light
					);
			}
		)
	);
}

void
sge::scenic::render_context::ffp::object::vertex_buffer(
	sge::renderer::vertex::buffer const &_vertex_buffer)
{
	current_vertex_buffer_ =
		optional_scoped_vertex_buffer_unique_ptr();

	current_vertex_buffer_ =
		optional_scoped_vertex_buffer_unique_ptr(
			fcppt::make_unique_ptr<
				sge::renderer::vertex::scoped_buffer
			>(
				context_,
				_vertex_buffer
			)
		);

	current_vertex_buffer_size_ =
		sge::renderer::vertex::count{
			_vertex_buffer.linear_size()
		};
}

void
sge::scenic::render_context::ffp::object::fog(
	sge::scenic::render_context::fog::optional_properties const &)
{
}

void
sge::scenic::render_context::ffp::object::render(
	sge::renderer::index::buffer const &_index_buffer,
	sge::scenic::index_buffer_range const &_index_buffer_range)
{
	context_.render_indexed(
		_index_buffer,
		sge::renderer::vertex::first(
			0u),
		current_vertex_buffer_size_,
		sge::renderer::primitive_type::triangle_list,
		_index_buffer_range.first_index(),
		_index_buffer_range.index_count());
}

sge::renderer::target::base &
sge::scenic::render_context::ffp::object::target()
{
	return
		context_.target();
}

sge::scenic::render_context::ffp::object::~object()
{
	context_.material_state(
		sge::renderer::state::ffp::lighting::material::const_optional_object_ref());

	context_.transform(
		sge::renderer::state::ffp::transform::mode::world,
		sge::renderer::state::ffp::transform::const_optional_object_ref());

	context_.transform(
		sge::renderer::state::ffp::transform::mode::projection,
		sge::renderer::state::ffp::transform::const_optional_object_ref());

	context_.texture(
		sge::renderer::texture::const_optional_base_ref(),
		sge::renderer::texture::stage(
			0u));

	context_.sampler_state(
		sge::renderer::state::core::sampler::const_optional_object_ref_map());

	context_.lights_state(
		sge::renderer::state::ffp::lighting::light::const_object_ref_vector());

	context_.lighting_state(
		sge::renderer::state::ffp::lighting::const_optional_object_ref());
}
