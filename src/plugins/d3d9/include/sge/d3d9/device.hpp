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


#ifndef SGE_D3D9_DEVICE_HPP_INCLUDED
#define SGE_D3D9_DEVICE_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/resource_manager.hpp>
#include <sge/d3d9/swapchain/d3d_scoped_ptr.hpp>
#include <sge/d3d9/target/onscreen_fwd.hpp>
#include <sge/d3d9/state/core/defaults_fwd.hpp>
#include <sge/d3d9/state/ffp/defaults_fwd.hpp>
#include <sge/renderer/config.hpp>
#include <sge/renderer/caps/device_fwd.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/context/core_unique_ptr.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/context/ffp_unique_ptr.hpp>
#include <sge/renderer/depth_stencil_buffer/surface_parameters_fwd.hpp>
#include <sge/renderer/depth_stencil_buffer/surface_unique_ptr.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/device/parameters_fwd.hpp>
#include <sge/renderer/display_mode/object_fwd.hpp>
#include <sge/renderer/index/buffer_parameters_fwd.hpp>
#include <sge/renderer/index/buffer_unique_ptr.hpp>
#include <sge/renderer/occlusion_query/object_unique_ptr.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
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
#include <fcppt/com_deleter.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_impl.hpp>
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
namespace d3d9
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
		IDirect3D9 &,
		sge::renderer::device::parameters const &,
		sge::renderer::caps::device const &
	);

	~device();
private:
	sge::renderer::context::core_unique_ptr
	begin_rendering(
		sge::renderer::target::base &
	);

	void
	end_rendering(
		sge::renderer::context::core &
	);

	sge::renderer::target::offscreen_unique_ptr
	create_target();

	sge::renderer::texture::planar_unique_ptr
	create_planar_texture(
		sge::renderer::texture::planar_parameters const &
	);

	sge::renderer::texture::depth_stencil_unique_ptr
	create_depth_stencil_texture(
		sge::renderer::texture::depth_stencil_parameters const &
	);

	sge::renderer::depth_stencil_buffer::surface_unique_ptr
	create_depth_stencil_surface(
		sge::renderer::depth_stencil_buffer::surface_parameters const &
	);

	sge::renderer::texture::volume_unique_ptr
	create_volume_texture(
		sge::renderer::texture::volume_parameters const &
	);

	sge::renderer::texture::cube_unique_ptr
	create_cube_texture(
		sge::renderer::texture::cube_parameters const &
	);

	sge::renderer::vertex::declaration_unique_ptr
	create_vertex_declaration(
		sge::renderer::vertex::declaration_parameters const &
	);

	sge::renderer::vertex::buffer_unique_ptr
	create_vertex_buffer(
		sge::renderer::vertex::buffer_parameters const &
	);

	sge::renderer::index::buffer_unique_ptr
	create_index_buffer(
		sge::renderer::index::buffer_parameters const &
	);

	sge::renderer::occlusion_query::object_unique_ptr
	create_occlusion_query();

	sge::renderer::state::core::blend::object_unique_ptr
	create_blend_state(
		sge::renderer::state::core::blend::parameters const &
	);

	sge::renderer::state::core::depth_stencil::object_unique_ptr
	create_depth_stencil_state(
		sge::renderer::state::core::depth_stencil::parameters const &
	);

	sge::renderer::state::core::rasterizer::object_unique_ptr
	create_rasterizer_state(
		sge::renderer::state::core::rasterizer::parameters const &
	);

	sge::renderer::state::core::sampler::object_unique_ptr
	create_sampler_state(
		sge::renderer::state::core::sampler::parameters const &
	);
#if defined(SGE_RENDERER_HAVE_CG)
	sge::cg::profile::object const
	create_cg_profile(
		sge::cg::profile::shader_type
	);

	sge::cg::program::compile_options const
	cg_compile_options(
		sge::cg::context::object const &,
		sge::cg::profile::object const &
	);

	sge::renderer::cg::loaded_program_unique_ptr
	load_cg_program(
		sge::cg::program::object &
	);

	sge::renderer::cg::loaded_texture_unique_ptr
	load_cg_texture(
		sge::cg::parameter::object const &,
		sge::renderer::texture::base &
	);

	sge::cg::program::source const
	transform_cg_vertex_program(
		sge::renderer::vertex::declaration const &,
		sge::cg::program::source const &
	);
#endif

	sge::renderer::target::onscreen &
	onscreen_target() const;

	sge::renderer::caps::device const &
	caps() const;

	sge::renderer::display_mode::object const
	display_mode() const;

	sge::renderer::context::ffp_unique_ptr
	begin_rendering_ffp(
		sge::renderer::target::base &
	);

	void
	end_rendering_ffp(
		sge::renderer::context::ffp &
	);

	sge::renderer::state::ffp::alpha_test::object_unique_ptr
	create_alpha_test_state(
		sge::renderer::state::ffp::alpha_test::parameters const &
	);

	sge::renderer::state::ffp::clip_plane::object_unique_ptr
	create_clip_plane_state(
		sge::renderer::state::ffp::clip_plane::parameters const &
	);

	sge::renderer::state::ffp::fog::object_unique_ptr
	create_fog_state(
		sge::renderer::state::ffp::fog::parameters const &
	);

	sge::renderer::state::ffp::lighting::object_unique_ptr
	create_lighting_state(
		sge::renderer::state::ffp::lighting::parameters const &
	);

	sge::renderer::state::ffp::lighting::light::object_unique_ptr
	create_light_state(
		sge::renderer::state::ffp::lighting::light::parameters const &
	);

	sge::renderer::state::ffp::lighting::material::object_unique_ptr
	create_material_state(
		sge::renderer::state::ffp::lighting::material::parameters const &
	);

	sge::renderer::state::ffp::misc::object_unique_ptr
	create_misc_state(
		sge::renderer::state::ffp::misc::parameters const &
	);

	sge::renderer::state::ffp::sampler::object_unique_ptr
	create_ffp_sampler_state(
		sge::renderer::state::ffp::sampler::parameters const &
	);

	sge::renderer::state::ffp::transform::object_unique_ptr
	create_transform_state(
		sge::renderer::state::ffp::transform::parameters const &
	);

	template<
		typename Ptr
	>
	std::unique_ptr<
		Ptr
	>
	add_resource(
		std::unique_ptr<
			Ptr
		> &&
	);

	void
	reset();

	void
	reinit();

	void
	release();

	sge::renderer::pixel_format::srgb const srgb_;

	sge::renderer::caps::device const &caps_;

	D3DPRESENT_PARAMETERS present_parameters_;

	typedef fcppt::scoped_ptr<
		IDirect3DDevice9,
		fcppt::com_deleter
	> d3d_device_scoped_ptr;

	d3d_device_scoped_ptr const device_;

	sge::d3d9::resource_manager resources_;

	sge::d3d9::swapchain::d3d_scoped_ptr const swap_chain_;

	typedef fcppt::scoped_ptr<
		sge::d3d9::target::onscreen
	> onscreen_target_scoped_ptr;

	onscreen_target_scoped_ptr const onscreen_target_;

	typedef fcppt::scoped_ptr<
		sge::d3d9::state::core::defaults
	> core_defaults_scoped_ptr;

	core_defaults_scoped_ptr const core_defaults_;

	typedef fcppt::scoped_ptr<
		sge::d3d9::state::ffp::defaults
	> ffp_defaults_scoped_ptr;

	ffp_defaults_scoped_ptr const ffp_defaults_;
};

}
}

#endif
