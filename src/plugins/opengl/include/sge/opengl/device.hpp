/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include <sge/opengl/device_state/context_scoped_ptr.hpp>
#include <sge/opengl/device_state/object_fwd.hpp>
#include <sge/opengl/device_state/scoped_current.hpp>
#include <sge/opengl/device_state/system_fwd.hpp>
#include <sge/opengl/context/device/object.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
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
#include <sge/renderer/display_mode/object_fwd.hpp>
#include <sge/renderer/index/buffer_parameters_fwd.hpp>
#include <sge/renderer/index/buffer_unique_ptr.hpp>
#include <sge/renderer/occlusion_query/object_unique_ptr.hpp>
#include <sge/renderer/parameters/object_fwd.hpp>
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
#include <sge/renderer/target/onscreen_scoped_ptr.hpp>
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
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_impl.hpp>

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
		sge::renderer::parameters::object const &,
		awl::window::object &,
		sge::opengl::device_state::system &,
		sge::opengl::context::system::object &,
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
		renderer::texture::planar_parameters const &
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

	sge::renderer::display_mode::object const
	display_mode() const;

	sge::opengl::texture::basic_parameters const
	texture_parameters();

	sge::opengl::context::system::object &system_context_;

	sge::opengl::context::device::object device_context_;

	sge::renderer::caps::device const &caps_;

	typedef fcppt::scoped_ptr<
		sge::opengl::device_state::object
	> device_state_scoped_ptr;

	device_state_scoped_ptr const device_state_;

	sge::opengl::device_state::context_scoped_ptr const context_;

	sge::opengl::device_state::scoped_current const scoped_current_;

	sge::renderer::target::onscreen_scoped_ptr const onscreen_target_;
};

}
}

#endif
