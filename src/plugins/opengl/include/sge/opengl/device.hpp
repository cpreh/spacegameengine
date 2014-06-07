/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_OPENGL_DEVICE_HPP_INCLUDED
#define SGE_OPENGL_DEVICE_HPP_INCLUDED

#include <sge/opengl/backend/context_unique_ptr.hpp>
#include <sge/opengl/backend/scoped_current.hpp>
#include <sge/opengl/backend/system_fwd.hpp>
#include <sge/opengl/context/device/object.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/platform/device_state_fwd.hpp>
#include <sge/opengl/platform/system_fwd.hpp>
#include <sge/opengl/texture/basic_parameters_fwd.hpp>
#include <sge/renderer/config.hpp>
#include <sge/renderer/caps/device_fwd.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/context/core_unique_ptr.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/context/ffp_unique_ptr.hpp>
#include <sge/renderer/depth_stencil_buffer/surface_parameters_fwd.hpp>
#include <sge/renderer/depth_stencil_buffer/surface_unique_ptr.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/display_mode/optional_object_fwd.hpp>
#include <sge/renderer/display_mode/parameters_fwd.hpp>
#include <sge/renderer/index/buffer_parameters_fwd.hpp>
#include <sge/renderer/index/buffer_unique_ptr.hpp>
#include <sge/renderer/occlusion_query/object_unique_ptr.hpp>
#include <sge/renderer/state/core/blend/object_unique_ptr.hpp>
#include <sge/renderer/state/core/blend/parameters_fwd.hpp>
#include <sge/renderer/state/core/depth_stencil/object_unique_ptr.hpp>
#include <sge/renderer/state/core/depth_stencil/parameters_fwd.hpp>
#include <sge/renderer/state/core/rasterizer/object_unique_ptr.hpp>
#include <sge/renderer/state/core/rasterizer/parameters_fwd.hpp>
#include <sge/renderer/state/core/sampler/object_unique_ptr.hpp>
#include <sge/renderer/state/core/sampler/parameters_fwd.hpp>
#include <sge/renderer/state/ffp/alpha_test/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/alpha_test/parameters_fwd.hpp>
#include <sge/renderer/state/ffp/clip_plane/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/clip_plane/parameters_fwd.hpp>
#include <sge/renderer/state/ffp/fog/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/fog/parameters_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/lighting/parameters_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/light/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/lighting/light/parameters_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/material/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/lighting/material/parameters_fwd.hpp>
#include <sge/renderer/state/ffp/misc/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/misc/parameters_fwd.hpp>
#include <sge/renderer/state/ffp/sampler/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/sampler/parameters_fwd.hpp>
#include <sge/renderer/state/ffp/transform/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/transform/parameters_fwd.hpp>
#include <sge/renderer/target/base_fwd.hpp>
#include <sge/renderer/target/offscreen_unique_ptr.hpp>
#include <sge/renderer/target/onscreen_fwd.hpp>
#include <sge/renderer/target/onscreen_unique_ptr.hpp>
#include <sge/renderer/texture/cube_parameters_fwd.hpp>
#include <sge/renderer/texture/cube_unique_ptr.hpp>
#include <sge/renderer/texture/depth_stencil_parameters_fwd.hpp>
#include <sge/renderer/texture/depth_stencil_unique_ptr.hpp>
#include <sge/renderer/texture/planar_parameters_fwd.hpp>
#include <sge/renderer/texture/planar_unique_ptr.hpp>
#include <sge/renderer/texture/volume_parameters_fwd.hpp>
#include <sge/renderer/texture/volume_unique_ptr.hpp>
#include <sge/renderer/vertex/buffer_parameters_fwd.hpp>
#include <sge/renderer/vertex/buffer_unique_ptr.hpp>
#include <sge/renderer/vertex/declaration_parameters_fwd.hpp>
#include <sge/renderer/vertex/declaration_unique_ptr.hpp>
#include <awl/window/object_fwd.hpp>
#include <awl/window/event/processor_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>

#if defined(SGE_RENDERER_HAVE_CG)
#include <sge/cg/context/object_fwd.hpp>
#include <sge/cg/parameter/object_fwd.hpp>
#include <sge/cg/program/compile_options.hpp>
#include <sge/cg/program/object_fwd.hpp>
#include <sge/cg/program/source.hpp>
#include <sge/cg/profile/object_fwd.hpp>
#include <sge/cg/profile/shader_type_fwd.hpp>
#include <sge/renderer/cg/loaded_program_unique_ptr.hpp>
#include <sge/renderer/cg/loaded_texture_unique_ptr.hpp>
#include <sge/renderer/texture/base_fwd.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#endif


namespace sge
{
namespace opengl
{

class device
:
	public sge::renderer::device::ffp
{
	FCPPT_NONCOPYABLE(
		device
	);
public:
	device(
		sge::renderer::display_mode::parameters const &,
		awl::window::object &,
		awl::window::event::processor &,
		sge::opengl::platform::system &,
		sge::opengl::backend::system &,
		sge::opengl::context::system::object &,
		sge::renderer::caps::device const &
	);

	~device()
	override;
private:
	sge::renderer::context::core_unique_ptr
	begin_rendering(
		sge::renderer::target::base &
	)
	override;

	void
	end_rendering(
		sge::renderer::context::core &
	)
	override;

	sge::renderer::target::offscreen_unique_ptr
	create_target()
	override;

	sge::renderer::texture::planar_unique_ptr
	create_planar_texture(
		renderer::texture::planar_parameters const &
	)
	override;

	sge::renderer::texture::depth_stencil_unique_ptr
	create_depth_stencil_texture(
		sge::renderer::texture::depth_stencil_parameters const &
	)
	override;

	sge::renderer::depth_stencil_buffer::surface_unique_ptr
	create_depth_stencil_surface(
		sge::renderer::depth_stencil_buffer::surface_parameters const &
	)
	override;

	sge::renderer::texture::volume_unique_ptr
	create_volume_texture(
		sge::renderer::texture::volume_parameters const &
	)
	override;

	sge::renderer::texture::cube_unique_ptr
	create_cube_texture(
		sge::renderer::texture::cube_parameters const &
	)
	override;

	sge::renderer::vertex::declaration_unique_ptr
	create_vertex_declaration(
		sge::renderer::vertex::declaration_parameters const &
	)
	override;

	sge::renderer::vertex::buffer_unique_ptr
	create_vertex_buffer(
		sge::renderer::vertex::buffer_parameters const &
	)
	override;

	sge::renderer::index::buffer_unique_ptr
	create_index_buffer(
		sge::renderer::index::buffer_parameters const &
	)
	override;

	sge::renderer::occlusion_query::object_unique_ptr
	create_occlusion_query()
	override;

	sge::renderer::state::core::blend::object_unique_ptr
	create_blend_state(
		sge::renderer::state::core::blend::parameters const &
	)
	override;

	sge::renderer::state::core::depth_stencil::object_unique_ptr
	create_depth_stencil_state(
		sge::renderer::state::core::depth_stencil::parameters const &
	)
	override;

	sge::renderer::state::core::rasterizer::object_unique_ptr
	create_rasterizer_state(
		sge::renderer::state::core::rasterizer::parameters const &
	)
	override;

	sge::renderer::state::core::sampler::object_unique_ptr
	create_sampler_state(
		sge::renderer::state::core::sampler::parameters const &
	)
	override;

#if defined(SGE_RENDERER_HAVE_CG)
	sge::cg::profile::object
	create_cg_profile(
		sge::cg::profile::shader_type
	)
	override;

	sge::cg::program::compile_options
	cg_compile_options(
		sge::cg::context::object const &,
		sge::cg::profile::object const &
	)
	override;

	sge::renderer::cg::loaded_program_unique_ptr
	load_cg_program(
		sge::cg::program::object &
	)
	override;

	sge::renderer::cg::loaded_texture_unique_ptr
	load_cg_texture(
		sge::cg::parameter::object const &,
		sge::renderer::texture::base &
	)
	override;

	sge::cg::program::source
	transform_cg_vertex_program(
		sge::renderer::vertex::declaration const &,
		sge::cg::program::source const &
	)
	override;
#endif
	sge::renderer::target::onscreen &
	onscreen_target() const
	override;

	sge::renderer::caps::device const &
	caps() const
	override;

	sge::renderer::context::ffp_unique_ptr
	begin_rendering_ffp(
		sge::renderer::target::base &
	)
	override;

	void
	end_rendering_ffp(
		sge::renderer::context::ffp &
	)
	override;

	sge::renderer::state::ffp::alpha_test::object_unique_ptr
	create_alpha_test_state(
		sge::renderer::state::ffp::alpha_test::parameters const &
	)
	override;

	sge::renderer::state::ffp::clip_plane::object_unique_ptr
	create_clip_plane_state(
		sge::renderer::state::ffp::clip_plane::parameters const &
	)
	override;

	sge::renderer::state::ffp::fog::object_unique_ptr
	create_fog_state(
		sge::renderer::state::ffp::fog::parameters const &
	)
	override;

	sge::renderer::state::ffp::lighting::object_unique_ptr
	create_lighting_state(
		sge::renderer::state::ffp::lighting::parameters const &
	)
	override;

	sge::renderer::state::ffp::lighting::light::object_unique_ptr
	create_light_state(
		sge::renderer::state::ffp::lighting::light::parameters const &
	)
	override;

	sge::renderer::state::ffp::lighting::material::object_unique_ptr
	create_material_state(
		sge::renderer::state::ffp::lighting::material::parameters const &
	)
	override;

	sge::renderer::state::ffp::misc::object_unique_ptr
	create_misc_state(
		sge::renderer::state::ffp::misc::parameters const &
	)
	override;

	sge::renderer::state::ffp::sampler::object_unique_ptr
	create_ffp_sampler_state(
		sge::renderer::state::ffp::sampler::parameters const &
	)
	override;

	sge::renderer::state::ffp::transform::object_unique_ptr
	create_transform_state(
		sge::renderer::state::ffp::transform::parameters const &
	)
	override;

	sge::renderer::display_mode::optional_object
	display_mode() const
	override;

	void
	display_mode(
		sge::renderer::display_mode::optional_object const &
	) override;

	sge::opengl::texture::basic_parameters const
	texture_parameters();

	sge::opengl::context::system::object &system_context_;

	sge::opengl::context::device::object device_context_;

	sge::renderer::caps::device const &caps_;

	typedef
	std::unique_ptr<
		sge::opengl::platform::device_state
	>
	platform_device_state_unique_ptr;

	platform_device_state_unique_ptr const device_state_;

	sge::opengl::backend::context_unique_ptr const context_;

	sge::opengl::backend::scoped_current const scoped_current_;

	sge::renderer::target::onscreen_unique_ptr const onscreen_target_;
};

}
}

#endif
