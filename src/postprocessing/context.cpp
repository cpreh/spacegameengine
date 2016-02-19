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


#include <sge/config/media_path.hpp>
#include <sge/image/ds/format.hpp>
#include <sge/postprocessing/context.hpp>
#include <sge/renderer/color_buffer/optional_surface_ref.hpp>
#include <sge/renderer/color_buffer/surface.hpp>
#include <sge/renderer/color_buffer/writable_surface.hpp>
#include <sge/renderer/depth_stencil_buffer/optional_surface_ref.hpp>
#include <sge/renderer/depth_stencil_buffer/surface.hpp>
#include <sge/renderer/depth_stencil_buffer/surface_parameters.hpp>
#include <sge/renderer/depth_stencil_buffer/surface_unique_ptr.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/context/core.hpp>
#include <sge/renderer/context/scoped_core.hpp>
#include <sge/renderer/target/from_texture.hpp>
#include <sge/renderer/state/core/sampler/object.hpp>
#include <sge/renderer/target/offscreen.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/target/onscreen_unique_ptr.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/renderer/target/viewport_size.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/color_format.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/renderer/texture/planar_parameters.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/planar_unique_ptr.hpp>
#include <sge/renderer/state/core/sampler/const_object_ref.hpp>
#include <sge/renderer/state/core/sampler/const_object_ref_map.hpp>
#include <sge/renderer/state/core/sampler/parameters.hpp>
#include <sge/renderer/state/core/sampler/address/default.hpp>
#include <sge/renderer/state/core/sampler/scoped.hpp>
#include <sge/renderer/state/core/sampler/filter/point.hpp>
	/*
#include <sge/renderer/texture/address_mode.hpp>
#include <sge/renderer/texture/address_mode2.hpp>
#include <sge/renderer/texture/set_address_mode2.hpp>
	*/
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/renderer/vertex/declaration.hpp>
#include <sge/renderer/vertex/scoped_declaration.hpp>
#include <sge/shader/scoped_pair.hpp>
#include <sge/viewport/manage_callback.hpp>
#include <sge/viewport/manager.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/optional/assign.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/assign/make_map.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/object_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/dim/to_signed.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::postprocessing::context::context(
	sge::renderer::device::core &_renderer,
	sge::viewport::manager &_viewport_manager,
	sge::shader::context &_shader_context)
:
	renderer_(
		_renderer),
	quad_vertex_declaration_(
		sge::postprocessing::fullscreen_quad::create_vertex_declaration(
			renderer_)),
	point_sampler_(
		renderer_.create_sampler_state(
			sge::renderer::state::core::sampler::parameters(
				sge::renderer::state::core::sampler::address::default_(),
				sge::renderer::state::core::sampler::filter::point()))),
	fullscreen_quad_(
		renderer_,
		*quad_vertex_declaration_),
	finalize_shader_(
		_shader_context,
		*quad_vertex_declaration_,
		sge::shader::vertex_program_path(
			sge::config::media_path() / FCPPT_TEXT("shaders") / FCPPT_TEXT("postprocessing") / FCPPT_TEXT("finalize.cg")),
		sge::shader::pixel_program_path(
			sge::config::media_path() / FCPPT_TEXT("shaders") / FCPPT_TEXT("postprocessing") / FCPPT_TEXT("finalize.cg")),
		sge::shader::optional_cflags()),
	finalize_input_texture_parameter_(
		finalize_shader_.pixel_program(),
		sge::shader::parameter::name(
			sge::cg::string(
				"input_texture")),
		finalize_shader_,
		renderer_,
		sge::shader::parameter::planar_texture::optional_value()),
	viewport_connection_(
		_viewport_manager.manage_callback(
			sge::viewport::manage_callback{
				std::bind(
					&sge::postprocessing::context::viewport_callback,
					this
				)
			}
		)
	),
	rendering_result_texture_(),
	offscreen_target_(),
	depth_stencil_surface_()/*,
	offscreen_downsampled_target_(),
	downsampled_texture_0_(),
	downsampled_texture_1_()*/
{
}

FCPPT_PP_POP_WARNING

sge::renderer::context::scoped_core_unique_ptr
sge::postprocessing::context::create_render_context()
{
	this->switch_target_texture(
		*FCPPT_ASSERT_OPTIONAL_ERROR(
			rendering_result_texture_
		)
	);

	return
		fcppt::make_unique_ptr<
			sge::renderer::context::scoped_core
		>(
			renderer_,
			*FCPPT_ASSERT_OPTIONAL_ERROR(
				offscreen_target_
			)
		);
}

void
sge::postprocessing::context::render()
{
	this->render_and_return_overlay();
}

sge::renderer::context::scoped_core_unique_ptr
sge::postprocessing::context::render_and_return_overlay()
{
	/*
	this->downsample();
	this->blur_h();
	this->blur_v();
	*/
	return
		this->finalize();
}

sge::postprocessing::context::~context()
{
}

void
sge::postprocessing::context::viewport_callback()
{
	sge::renderer::dim2 const target_size(
		fcppt::math::dim::structure_cast<
			sge::renderer::dim2,
			fcppt::cast::size_fun
		>(
			sge::renderer::target::viewport_size(
				renderer_.onscreen_target()
			)
		)
	);

	/*
	sge::renderer::size_type const downsample_factor =
		4u;

	downsampled_texture_0_.take(
		renderer_.create_planar_texture(
			sge::renderer::texture::planar_parameters(
				target_size / downsample_factor,
				sge::image::color::format::r32f,
				sge::renderer::texture::mipmap::off(),
				sge::renderer::resource_flags_field::null(),
				sge::renderer::texture::capabilities_field(
					sge::renderer::texture::capabilities::render_target))));

	downsampled_texture_1_.take(
		renderer_.create_planar_texture(
			sge::renderer::texture::planar_parameters(
				target_size / downsample_factor,
				sge::image::color::format::r32f,
				sge::renderer::texture::mipmap::off(),
				sge::renderer::resource_flags_field::null(),
				sge::renderer::texture::capabilities_field(
					sge::renderer::texture::capabilities::render_target))));
	*/

	sge::renderer::texture::planar_unique_ptr const &result_texture(
		fcppt::optional::assign(
			rendering_result_texture_,
			renderer_.create_planar_texture(
				sge::renderer::texture::planar_parameters(
					target_size,
					sge::renderer::texture::color_format(
						sge::image::color::format::rgba32f,
						sge::renderer::texture::emulate_srgb::no),
					sge::renderer::texture::mipmap::off(),
					sge::renderer::resource_flags_field::null(),
					sge::renderer::texture::capabilities_field{
						sge::renderer::texture::capabilities::render_target
					}
				)
			)
		)
	);

	finalize_input_texture_parameter_.set(
		sge::shader::parameter::planar_texture::optional_value(
			fcppt::make_ref(
				*result_texture
			)
		)
	);

	/*
	finalize_blurred_texture_parameter_.set(
		*downsampled_texture_0_);
		*/

	sge::renderer::target::offscreen_unique_ptr const &offscreen_target(
		fcppt::optional::assign(
			offscreen_target_,
			sge::renderer::target::from_texture(
				renderer_,
				*result_texture
			)
		)
	);

	/*
	offscreen_downsampled_target_.take(
		sge::renderer::target::from_texture(
			renderer_,
			*downsampled_texture_0_));
			*/

	sge::renderer::depth_stencil_buffer::surface_unique_ptr const &depth_stencil_surface(
		fcppt::optional::assign(
			depth_stencil_surface_,
			renderer_.create_depth_stencil_surface(
				sge::renderer::depth_stencil_buffer::surface_parameters(
					target_size,
					sge::image::ds::format::d32
				)
			)
		)
	);

	offscreen_target->depth_stencil_surface(
		sge::renderer::depth_stencil_buffer::optional_surface_ref(
			fcppt::make_ref(
				*depth_stencil_surface
			)
		)
	);
}

	/*
void
sge::postprocessing::context::switch_downsampled_target_texture(
	sge::renderer::texture::planar &_new_texture)
{
	offscreen_downsampled_target_->color_surface(
		sge::renderer::color_buffer::optional_surface_ref(
			_new_texture.level(
				sge::renderer::texture::mipmap::level(
					0u))),
		sge::renderer::target::surface_index(
			0u));

	offscreen_downsampled_target_->viewport(
		sge::renderer::target::viewport(
			sge::renderer::pixel_rect(
				sge::renderer::pixel_rect::vector::null(),
				fcppt::math::dim::structure_cast<sge::renderer::pixel_rect::dim>(
					_new_texture.size()))));
}
	*/

void
sge::postprocessing::context::switch_target_texture(
	sge::renderer::texture::planar &_new_texture)
{
	FCPPT_ASSERT_OPTIONAL_ERROR(
		offscreen_target_
	)->color_surface(
		sge::renderer::color_buffer::optional_surface_ref(
			fcppt::reference_to_base<
				sge::renderer::color_buffer::surface
			>(
				fcppt::make_ref(
					_new_texture.level(
						sge::renderer::texture::mipmap::level(
							0u
						)
					)
				)
			)
		),
		sge::renderer::target::surface_index(
			0u
		)
	);

	FCPPT_ASSERT_OPTIONAL_ERROR(
		offscreen_target_
	)->viewport(
		sge::renderer::target::viewport(
			sge::renderer::pixel_rect(
				fcppt::math::vector::null<
					sge::renderer::pixel_rect::vector
				>(),
				fcppt::math::dim::structure_cast<
					sge::renderer::pixel_rect::dim,
					fcppt::cast::size_fun
				>(
					fcppt::math::dim::to_signed(
						_new_texture.size()
					)
				)
			)
		)
	);
}

	/*
void
sge::postprocessing::context::downsample()
{
	this->switch_downsampled_target_texture(
		*downsampled_texture_0_);

	sge::renderer::context::scoped_core const scoped_block(
		renderer_,
		*offscreen_downsampled_target_);

	downsample_input_texture_parameter_.set(
		*rendering_result_texture_);

	sge::shader::scoped_pair scoped_shader(
		scoped_block.get(),
		downsample_shader_);

	sge::renderer::texture::filter::scoped scoped_texture_filter(
		scoped_block.get(),
		downsample_input_texture_parameter_.stage(),
		sge::renderer::texture::filter::linear());

	fullscreen_quad_.render(
		scoped_block.get());
}

void
sge::postprocessing::context::blur_h()
{
	this->switch_downsampled_target_texture(
		*downsampled_texture_1_);

	sge::renderer::context::scoped_core const scoped_block(
		renderer_,
		*offscreen_downsampled_target_);

	blur_h_input_texture_parameter_.set(
		*downsampled_texture_0_);

	sge::shader::scoped_pair scoped_shader(
		scoped_block.get(),
		blur_h_shader_);

	sge::renderer::texture::set_address_mode2(
		scoped_block.get(),
		blur_h_input_texture_parameter_.stage(),
		sge::renderer::texture::address_mode2(
			sge::renderer::texture::address_mode::clamp));

	sge::renderer::texture::filter::scoped scoped_texture_filter(
		scoped_block.get(),
		blur_h_input_texture_parameter_.stage(),
		sge::renderer::texture::filter::point());

	fullscreen_quad_.render(
		scoped_block.get());
}

void
sge::postprocessing::context::blur_v()
{
	this->switch_downsampled_target_texture(
		*downsampled_texture_0_);

	sge::renderer::context::scoped_core const scoped_block(
		renderer_,
		*offscreen_downsampled_target_);

	blur_v_input_texture_parameter_.set(
		*downsampled_texture_1_);

	sge::shader::scoped_pair scoped_shader(
		scoped_block.get(),
		blur_v_shader_);

	sge::renderer::texture::set_address_mode2(
		scoped_block.get(),
		blur_v_input_texture_parameter_.stage(),
		sge::renderer::texture::address_mode2(
			sge::renderer::texture::address_mode::clamp));

	sge::renderer::texture::filter::scoped scoped_texture_filter(
		scoped_block.get(),
		blur_v_input_texture_parameter_.stage(),
		sge::renderer::texture::filter::point());

	fullscreen_quad_.render(
		scoped_block.get());
}

void
sge::postprocessing::context::blur()
{
	unsigned const blur_iterations = 2;

	for(unsigned i = 0; i < blur_iterations; ++i)
	{
		this->blur_h();
		this->blur_v();
	}
}
	*/

sge::renderer::context::scoped_core_unique_ptr
sge::postprocessing::context::finalize()
{
	sge::renderer::context::scoped_core_unique_ptr result(
		fcppt::make_unique_ptr<
			sge::renderer::context::scoped_core
		>(
			renderer_,
			renderer_.onscreen_target()
		)
	);

	sge::shader::scoped_pair scoped_shader(
		result->get(),
		finalize_shader_);

	sge::renderer::state::core::sampler::scoped scoped_filter(
		result->get(),
		fcppt::assign::make_map<sge::renderer::state::core::sampler::const_object_ref_map>
			(
				finalize_input_texture_parameter_.stage(),
				sge::renderer::state::core::sampler::const_object_ref(
					*point_sampler_)));

	/*
	sge::renderer::texture::filter::scoped scoped_texture_filter_1(
		result->get(),
		finalize_blurred_texture_parameter_.stage(),
		sge::renderer::texture::filter::linear());
	*/

	fullscreen_quad_.render(
		result->get());

	return
		result;
}

