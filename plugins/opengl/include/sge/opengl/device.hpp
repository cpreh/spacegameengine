//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_DEVICE_HPP_INCLUDED
#define SGE_OPENGL_DEVICE_HPP_INCLUDED

#include <sge/opengl/backend/context_unique_ptr.hpp>
#include <sge/opengl/backend/scoped_current.hpp>
#include <sge/opengl/backend/system_ref.hpp>
#include <sge/opengl/context/object.hpp>
#include <sge/opengl/info/context.hpp>
#include <sge/opengl/platform/device_state_fwd.hpp>
#include <sge/opengl/platform/system_ref.hpp>
#include <sge/opengl/texture/basic_parameters_fwd.hpp>
#include <sge/renderer/config.hpp>
#include <sge/renderer/caps/device.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/context/core_unique_ptr.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/context/ffp_unique_ptr.hpp>
#include <sge/renderer/depth_stencil_buffer/surface_parameters_fwd.hpp>
#include <sge/renderer/depth_stencil_buffer/surface_unique_ptr.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/display_mode/container.hpp>
#include <sge/renderer/display_mode/optional_fullscreen_fwd.hpp>
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
#include <sge/renderer/target/base_ref.hpp>
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
#include <sge/window/object_ref.hpp>
#include <awl/timer/unique_ptr.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/log/object_reference.hpp>
#include <fcppt/signal/auto_connection.hpp>

#if defined(SGE_RENDERER_HAVE_CG)
#include <sge/cg/context/object_fwd.hpp>
#include <sge/cg/parameter/object_fwd.hpp>
#include <sge/cg/profile/object_fwd.hpp>
#include <sge/cg/profile/shader_type_fwd.hpp>
#include <sge/cg/program/compile_options.hpp>
#include <sge/cg/program/object_ref.hpp>
#include <sge/cg/program/source.hpp>
#include <sge/renderer/cg/loaded_program_unique_ptr.hpp>
#include <sge/renderer/cg/loaded_texture_unique_ptr.hpp>
#include <sge/renderer/texture/base_ref.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#endif


namespace sge::opengl
{

class device
:
	public sge::renderer::device::ffp
{
	FCPPT_NONMOVABLE(
		device
	);
public:
	device(
		fcppt::log::object_reference,
		sge::renderer::display_mode::parameters const &,
		sge::window::object_ref,
		sge::opengl::platform::system_ref,
		sge::opengl::backend::system_ref
	);

	~device()
	override;
private:
	sge::renderer::context::core_unique_ptr
	begin_rendering(
		sge::renderer::target::base_ref
	)
	override;

	void
	end_rendering(
		sge::renderer::context::core &
	)
	override;

	[[nodiscard]]
	sge::renderer::target::offscreen_unique_ptr
	create_target()
	override;

	[[nodiscard]]
	sge::renderer::texture::planar_unique_ptr
	create_planar_texture(
		renderer::texture::planar_parameters const &
	)
	override;

	[[nodiscard]]
	sge::renderer::texture::depth_stencil_unique_ptr
	create_depth_stencil_texture(
		sge::renderer::texture::depth_stencil_parameters const &
	)
	override;

	[[nodiscard]]
	sge::renderer::depth_stencil_buffer::surface_unique_ptr
	create_depth_stencil_surface(
		sge::renderer::depth_stencil_buffer::surface_parameters const &
	)
	override;

	[[nodiscard]]
	sge::renderer::texture::volume_unique_ptr
	create_volume_texture(
		sge::renderer::texture::volume_parameters const &
	)
	override;

	[[nodiscard]]
	sge::renderer::texture::cube_unique_ptr
	create_cube_texture(
		sge::renderer::texture::cube_parameters const &
	)
	override;

	[[nodiscard]]
	sge::renderer::vertex::declaration_unique_ptr
	create_vertex_declaration(
		sge::renderer::vertex::declaration_parameters const &
	)
	override;

	[[nodiscard]]
	sge::renderer::vertex::buffer_unique_ptr
	create_vertex_buffer(
		sge::renderer::vertex::buffer_parameters const &
	)
	override;

	[[nodiscard]]
	sge::renderer::index::buffer_unique_ptr
	create_index_buffer(
		sge::renderer::index::buffer_parameters const &
	)
	override;

	[[nodiscard]]
	sge::renderer::occlusion_query::object_unique_ptr
	create_occlusion_query()
	override;

	[[nodiscard]]
	sge::renderer::state::core::blend::object_unique_ptr
	create_blend_state(
		sge::renderer::state::core::blend::parameters const &
	)
	override;

	[[nodiscard]]
	sge::renderer::state::core::depth_stencil::object_unique_ptr
	create_depth_stencil_state(
		sge::renderer::state::core::depth_stencil::parameters const &
	)
	override;

	[[nodiscard]]
	sge::renderer::state::core::rasterizer::object_unique_ptr
	create_rasterizer_state(
		sge::renderer::state::core::rasterizer::parameters const &
	)
	override;

	[[nodiscard]]
	sge::renderer::state::core::sampler::object_unique_ptr
	create_sampler_state(
		sge::renderer::state::core::sampler::parameters const &
	)
	override;

#if defined(SGE_RENDERER_HAVE_CG)
	[[nodiscard]]
	sge::cg::profile::object
	create_cg_profile(
		sge::cg::profile::shader_type
	)
	override;

	[[nodiscard]]
	sge::cg::program::compile_options
	cg_compile_options(
		sge::cg::context::object const &,
		sge::cg::profile::object const &
	)
	override;

	[[nodiscard]]
	sge::renderer::cg::loaded_program_unique_ptr
	load_cg_program(
		sge::cg::program::object_ref
	)
	override;

	[[nodiscard]]
	sge::renderer::cg::loaded_texture_unique_ptr
	load_cg_texture(
		sge::cg::parameter::object const &,
		sge::renderer::texture::base_ref
	)
	override;

	[[nodiscard]]
	sge::cg::program::source
	transform_cg_vertex_program(
		sge::renderer::vertex::declaration const &,
		sge::cg::program::source const &
	)
	override;
#endif
	[[nodiscard]]
	sge::renderer::target::onscreen &
	onscreen_target() const
	override;

	[[nodiscard]]
	sge::renderer::caps::device const &
	caps() const
	override;

	[[nodiscard]]
	sge::renderer::context::ffp_unique_ptr
	begin_rendering_ffp(
		sge::renderer::target::base_ref
	)
	override;

	void
	end_rendering_ffp(
		sge::renderer::context::ffp &
	)
	override;

	[[nodiscard]]
	sge::renderer::state::ffp::alpha_test::object_unique_ptr
	create_alpha_test_state(
		sge::renderer::state::ffp::alpha_test::parameters const &
	)
	override;

	[[nodiscard]]
	sge::renderer::state::ffp::clip_plane::object_unique_ptr
	create_clip_plane_state(
		sge::renderer::state::ffp::clip_plane::parameters const &
	)
	override;

	[[nodiscard]]
	sge::renderer::state::ffp::fog::object_unique_ptr
	create_fog_state(
		sge::renderer::state::ffp::fog::parameters const &
	)
	override;

	[[nodiscard]]
	sge::renderer::state::ffp::lighting::object_unique_ptr
	create_lighting_state(
		sge::renderer::state::ffp::lighting::parameters const &
	)
	override;

	[[nodiscard]]
	sge::renderer::state::ffp::lighting::light::object_unique_ptr
	create_light_state(
		sge::renderer::state::ffp::lighting::light::parameters const &
	)
	override;

	[[nodiscard]]
	sge::renderer::state::ffp::lighting::material::object_unique_ptr
	create_material_state(
		sge::renderer::state::ffp::lighting::material::parameters const &
	)
	override;

	[[nodiscard]]
	sge::renderer::state::ffp::misc::object_unique_ptr
	create_misc_state(
		sge::renderer::state::ffp::misc::parameters const &
	)
	override;

	[[nodiscard]]
	sge::renderer::state::ffp::sampler::object_unique_ptr
	create_ffp_sampler_state(
		sge::renderer::state::ffp::sampler::parameters const &
	)
	override;

	[[nodiscard]]
	sge::renderer::state::ffp::transform::object_unique_ptr
	create_transform_state(
		sge::renderer::state::ffp::transform::parameters const &
	)
	override;

	[[nodiscard]]
	sge::renderer::display_mode::optional_object
	display_mode() const
	override;

	void
	fullscreen(
		sge::renderer::display_mode::optional_fullscreen const &
	) override;

	[[nodiscard]]
	sge::renderer::display_mode::container
	display_modes() const
	override;

	[[nodiscard]]
	sge::opengl::texture::basic_parameters
	texture_parameters();

	using
	platform_device_state_unique_ptr
	=
	fcppt::unique_ptr<
		sge::opengl::platform::device_state
	>;

	fcppt::log::object_reference const log_;

	platform_device_state_unique_ptr const device_state_;

	sge::opengl::backend::context_unique_ptr const backend_context_;

	sge::opengl::backend::scoped_current const scoped_current_;

	sge::opengl::info::context const info_;

	sge::opengl::context::object context_;

	sge::renderer::caps::device const caps_;

	sge::renderer::target::onscreen_unique_ptr const onscreen_target_;

	awl::timer::unique_ptr const timer_;

	fcppt::signal::auto_connection const event_connection_;
};

}

#endif
