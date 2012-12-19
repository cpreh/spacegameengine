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
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/ptr/replace_unique_ptr.hpp>


sge::scenic::render_context::cg::manager::manager(
	sge::shader::context &_shader_context,
	sge::renderer::vertex_declaration &_vertex_declaration)
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
			fcppt::assign::make_container<sge::shader::optional_cflags::string_sequence>
				("-DMAX_POINT_LIGHTS="+fcppt::insert_to_std_string(max_point_lights::value))
				("-DMAX_DIRECTIONAL_LIGHTS="+fcppt::insert_to_std_string(max_directional_lights::value)))),
	world_matrix_(
		shader_.vertex_program(),
		sge::shader::parameter::name(
			"camera.world"),
		_shader_context.renderer(),
		sge::shader::parameter::is_projection_matrix(
			false),
		sge::renderer::matrix4()),
	world_projection_matrix_(
		shader_.vertex_program(),
		sge::shader::parameter::name(
			"camera.world_projection"),
		_shader_context.renderer(),
		sge::shader::parameter::is_projection_matrix(
			true),
		sge::renderer::matrix4()),
	world_inverse_transpose_matrix_(
		shader_.vertex_program(),
		sge::shader::parameter::name(
			"camera.world_it"),
		_shader_context.renderer(),
		sge::shader::parameter::is_projection_matrix(
			false),
		sge::renderer::matrix4()),
	material_diffuse_color_(
		shader_.pixel_program(),
		sge::shader::parameter::name(
			"current_material.diffuse_color"),
		sge::renderer::vector4()),
	material_specular_color_(
		shader_.pixel_program(),
		sge::shader::parameter::name(
			"current_material.specular_color"),
		sge::renderer::vector4()),
	material_ambient_color_(
		shader_.pixel_program(),
		sge::shader::parameter::name(
			"current_material.ambient_color"),
		sge::renderer::vector4()),
	material_emissive_color_(
		shader_.pixel_program(),
		sge::shader::parameter::name(
			"current_material.emissive_color"),
		sge::renderer::vector4()),
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
		sge::renderer::vector4()),
	point_lights_(),
	directional_lights_(),
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
	for(point_light_array::size_type i = 0; i < point_lights_.size(); ++i)
		fcppt::container::ptr::replace_unique_ptr(
			point_lights_,
			i,
			fcppt::make_unique_ptr<sge::scenic::render_context::cg::light::point>(
				shader_.pixel_program(),
				sge::scenic::render_context::cg::light::index(
					i)));

	for(directional_light_array::size_type i = 0; i < directional_lights_.size(); ++i)
		fcppt::container::ptr::replace_unique_ptr(
			directional_lights_,
			i,
			fcppt::make_unique_ptr<sge::scenic::render_context::cg::light::directional>(
				shader_.pixel_program(),
				sge::scenic::render_context::cg::light::index(
					i)));
}

sge::scenic::render_context::base_unique_ptr
sge::scenic::render_context::cg::manager::create_context(
	sge::renderer::context::core &_context)
{
	return
		sge::scenic::render_context::base_unique_ptr(
			fcppt::make_unique_ptr<sge::scenic::render_context::cg::object>(
				*this,
				_context));
}

sge::scenic::render_context::cg::manager::~manager()
{
}
