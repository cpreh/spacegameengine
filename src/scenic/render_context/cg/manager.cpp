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


#include <sge/config/media_path.hpp>
#include <sge/renderer/vector3.hpp>
#include <sge/renderer/vector4.hpp>
#include <sge/renderer/state/core/blend/object.hpp>
#include <sge/renderer/state/core/blend/parameters.hpp>
#include <sge/renderer/state/core/blend/write_mask_all.hpp>
#include <sge/renderer/state/core/depth_stencil/object.hpp>
#include <sge/renderer/state/core/depth_stencil/parameters.hpp>
#include <sge/renderer/state/core/rasterizer/object.hpp>
#include <sge/renderer/state/core/rasterizer/parameters.hpp>
#include <sge/renderer/state/core/sampler/object.hpp>
#include <sge/renderer/state/core/sampler/parameters.hpp>
#include <sge/renderer/state/core/sampler/address/default.hpp>
#include <sge/renderer/state/core/sampler/filter/mipmap.hpp>
#include <sge/scenic/render_context/cg/manager.hpp>
#include <sge/scenic/render_context/cg/object.hpp>
#include <sge/scenic/render_context/cg/light/directional.hpp>
#include <sge/scenic/render_context/cg/light/point.hpp>
#include <sge/shader/context.hpp>
#include <fcppt/insert_to_std_string.hpp>
#include <fcppt/make_unique_ptr_fcppt.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/algorithm/array_fold.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <fcppt/config/external_end.hpp>


sge::scenic::render_context::cg::manager::manager(
	sge::shader::context &_shader_context,
	sge::renderer::vertex::declaration &_vertex_declaration)
:
	sge::scenic::render_context::manager_base(),
	vertex_declaration_(
		_vertex_declaration),
	shader_(
		_shader_context,
		_vertex_declaration,
		sge::shader::vertex_program_path(
			sge::config::media_path() / FCPPT_TEXT("shaders") / FCPPT_TEXT("ffp.cg")),
		sge::shader::pixel_program_path(
			sge::config::media_path() / FCPPT_TEXT("shaders") / FCPPT_TEXT("ffp.cg")),
		sge::shader::optional_cflags(
			sge::shader::optional_cflags::string_sequence{
				"-DMAX_POINT_LIGHTS="+fcppt::insert_to_std_string(max_point_lights::value),
				"-DMAX_DIRECTIONAL_LIGHTS="+fcppt::insert_to_std_string(max_directional_lights::value)
			}
		)
	),
	world_matrix_(
		shader_.vertex_program(),
		sge::shader::parameter::name(
			"camera.world"),
		_shader_context.renderer(),
		sge::shader::parameter::is_projection_matrix(
			false),
		sge::renderer::matrix4::identity()),
	world_projection_matrix_(
		shader_.vertex_program(),
		sge::shader::parameter::name(
			"camera.world_projection"),
		_shader_context.renderer(),
		sge::shader::parameter::is_projection_matrix(
			true),
		sge::renderer::matrix4::identity()),
	world_inverse_transpose_matrix_(
		shader_.vertex_program(),
		sge::shader::parameter::name(
			"camera.world_it"),
		_shader_context.renderer(),
		sge::shader::parameter::is_projection_matrix(
			false),
		sge::renderer::matrix4::identity()),
	material_diffuse_color_(
		shader_.pixel_program(),
		sge::shader::parameter::name(
			"current_material.diffuse_color"),
		sge::renderer::vector4::null()),
	material_specular_color_(
		shader_.pixel_program(),
		sge::shader::parameter::name(
			"current_material.specular_color"),
		sge::renderer::vector4::null()),
	material_ambient_color_(
		shader_.pixel_program(),
		sge::shader::parameter::name(
			"current_material.ambient_color"),
		sge::renderer::vector4::null()),
	material_emissive_color_(
		shader_.pixel_program(),
		sge::shader::parameter::name(
			"current_material.emissive_color"),
		sge::renderer::vector4::null()),
	material_shininess_(
		shader_.pixel_program(),
		sge::shader::parameter::name(
			"current_material.shininess"),
		sge::renderer::scalar()),
	use_diffuse_texture_(
		shader_.pixel_program(),
		sge::shader::parameter::name(
			"use_diffuse_texture"),
		false),
	diffuse_texture_(
		shader_.pixel_program(),
		sge::shader::parameter::name(
			"diffuse_texture"),
		shader_,
		shader_.context().renderer(),
		sge::shader::parameter::planar_texture::optional_value()),
	use_specular_texture_(
		shader_.pixel_program(),
		sge::shader::parameter::name(
			"use_specular_texture"),
		false),
	specular_texture_(
		shader_.pixel_program(),
		sge::shader::parameter::name(
			"specular_texture"),
		shader_,
		shader_.context().renderer(),
		sge::shader::parameter::planar_texture::optional_value()),
	point_light_count_(
		shader_.pixel_program(),
		sge::shader::parameter::name(
			"point_light_count"),
		0),
	directional_light_count_(
		shader_.pixel_program(),
		sge::shader::parameter::name(
			"directional_light_count"),
		0),
	use_fog_(
		shader_.pixel_program(),
		sge::shader::parameter::name(
			"fog_information.enabled"),
		false),
	fog_start_(
		shader_.pixel_program(),
		sge::shader::parameter::name(
			"fog_information.start"),
		sge::renderer::scalar()),
	fog_end_(
		shader_.pixel_program(),
		sge::shader::parameter::name(
			"fog_information.end"),
		sge::renderer::scalar()),
	fog_color_(
		shader_.pixel_program(),
		sge::shader::parameter::name(
			"fog_information.color"),
		sge::renderer::vector4::null()),
	point_lights_(
		fcppt::algorithm::array_fold<
			point_light_array
		>(
			[
				this
			](
				std::size_t const _index
			)
			{
				return
					fcppt::make_unique_ptr_fcppt<
						sge::scenic::render_context::cg::light::point
					>(
						shader_.pixel_program(),
						sge::scenic::render_context::cg::light::index(
							_index
						)
					);
			}
		)
	),
	directional_lights_(
		fcppt::algorithm::array_fold<
			directional_light_array
		>(
			[
				this
			](
				std::size_t const _index
			)
			{
				return
					fcppt::make_unique_ptr_fcppt<
						sge::scenic::render_context::cg::light::directional
					>(
						shader_.pixel_program(),
						sge::scenic::render_context::cg::light::index(
							_index
						)
					);
			}
		)
	),
	depth_stencil_state_(
		_shader_context.renderer().create_depth_stencil_state(
			sge::renderer::state::core::depth_stencil::parameters(
				sge::renderer::state::core::depth_stencil::depth::variant(
					sge::renderer::state::core::depth_stencil::depth::enabled(
						sge::renderer::state::core::depth_stencil::depth::func::less,
						sge::renderer::state::core::depth_stencil::depth::write_enable(
							true))),
				sge::renderer::state::core::depth_stencil::stencil::off()))),
	blend_state_(
		_shader_context.renderer().create_blend_state(
			sge::renderer::state::core::blend::parameters(
				sge::renderer::state::core::blend::alpha_off(),
				sge::renderer::state::core::blend::write_mask_all()))),
	rasterizer_state_(
		_shader_context.renderer().create_rasterizer_state(
			sge::renderer::state::core::rasterizer::parameters(
				sge::renderer::state::core::rasterizer::cull_mode::counter_clockwise,
				sge::renderer::state::core::rasterizer::fill_mode::solid,
				sge::renderer::state::core::rasterizer::enable_scissor_test(
					false)))),
	mipmap_sampler_state_(
		_shader_context.renderer().create_sampler_state(
			sge::renderer::state::core::sampler::parameters(
				sge::renderer::state::core::sampler::address::default_(),
				sge::renderer::state::core::sampler::filter::mipmap())))
{
}

sge::scenic::render_context::base_unique_ptr
sge::scenic::render_context::cg::manager::create_context(
	sge::renderer::context::core &_context)
{
	return
		fcppt::unique_ptr_to_base<
			sge::scenic::render_context::base
		>(
			fcppt::make_unique_ptr_fcppt<sge::scenic::render_context::cg::object>(
				*this,
				_context));
}

sge::scenic::render_context::cg::manager::~manager()
{
}
