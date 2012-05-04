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


#ifndef SGE_OPENGL_DEVICE_HPP_INCLUDED
#define SGE_OPENGL_DEVICE_HPP_INCLUDED

#include <sge/opengl/device_state_fwd.hpp>
#include <sge/opengl/onscreen_target_fwd.hpp>
#include <sge/opengl/context/object.hpp>
#include <sge/opengl/glew/scoped_init.hpp>
#include <sge/renderer/adapter.hpp>
#include <sge/renderer/config.hpp>
#include <sge/renderer/depth_stencil_buffer.hpp>
#include <sge/renderer/depth_stencil_format.hpp>
#include <sge/renderer/depth_stencil_surface_unique_ptr.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/index_buffer_unique_ptr.hpp>
#include <sge/renderer/index_count.hpp>
#include <sge/renderer/parameters_fwd.hpp>
#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/vertex_buffer_unique_ptr.hpp>
#include <sge/renderer/vertex_count.hpp>
#include <sge/renderer/vertex_declaration_fwd.hpp>
#include <sge/renderer/vertex_declaration_unique_ptr.hpp>
#include <sge/renderer/caps/object_fwd.hpp>
#include <sge/renderer/context/object_fwd.hpp>
#include <sge/renderer/context/object_unique_ptr.hpp>
#include <sge/renderer/index/dynamic/format.hpp>
#include <sge/renderer/glsl/geometry_shader_unique_ptr.hpp>
#include <sge/renderer/glsl/pixel_shader_unique_ptr.hpp>
#include <sge/renderer/glsl/program_unique_ptr.hpp>
#include <sge/renderer/glsl/string.hpp>
#include <sge/renderer/glsl/vertex_shader_unique_ptr.hpp>
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
#include <sge/renderer/vf/dynamic/format_fwd.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <awl/window/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_impl.hpp>

#if defined(SGE_RENDERER_HAVE_CG)
#include <sge/cg/context/object_fwd.hpp>
#include <sge/cg/parameter/object_fwd.hpp>
#include <sge/cg/program/compile_options.hpp>
#include <sge/cg/program/object_fwd.hpp>
#include <sge/cg/profile/object_unique_ptr.hpp>
#include <sge/cg/profile/shader_type.hpp>
#include <sge/renderer/cg/loaded_program_unique_ptr.hpp>
#include <sge/renderer/cg/loaded_texture_unique_ptr.hpp>
#include <sge/renderer/texture/base_fwd.hpp>
#endif


namespace sge
{
namespace opengl
{

class device
:
	public sge::renderer::device
{
	FCPPT_NONCOPYABLE(
		device
	);
public:
	device(
		sge::renderer::parameters const &,
		sge::renderer::adapter,
		awl::window::object &
	);

	~device();

	sge::renderer::context::object_unique_ptr
	begin_rendering(
		sge::renderer::target::base &
	);

	void
	end_rendering(
		sge::renderer::context::object &
	);

	sge::renderer::glsl::program_unique_ptr
	create_glsl_program();

	sge::renderer::glsl::vertex_shader_unique_ptr
	create_glsl_vertex_shader(
		sge::renderer::glsl::string const &
	);

	sge::renderer::glsl::pixel_shader_unique_ptr
	create_glsl_pixel_shader(
		sge::renderer::glsl::string const &
	);

	sge::renderer::glsl::geometry_shader_unique_ptr
	create_glsl_geometry_shader(
		sge::renderer::glsl::string const &
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

	sge::renderer::depth_stencil_surface_unique_ptr
	create_depth_stencil_surface(
		sge::renderer::dim2 const &,
		sge::renderer::depth_stencil_format::type
	);

	sge::renderer::texture::volume_unique_ptr
	create_volume_texture(
		sge::renderer::texture::volume_parameters const &
	);

	sge::renderer::texture::cube_unique_ptr
	create_cube_texture(
		sge::renderer::texture::cube_parameters const &
	);

	sge::renderer::vertex_declaration_unique_ptr
	create_vertex_declaration(
		sge::renderer::vf::dynamic::format const &
	);

	sge::renderer::vertex_buffer_unique_ptr
	create_vertex_buffer(
		sge::renderer::vertex_declaration const &,
		sge::renderer::vf::dynamic::part_index,
		sge::renderer::vertex_count,
		sge::renderer::resource_flags_field const &
	);

	sge::renderer::index_buffer_unique_ptr
	create_index_buffer(
		sge::renderer::index::dynamic::format::type,
		sge::renderer::index_count,
		sge::renderer::resource_flags_field const &
	);

#if defined(SGE_RENDERER_HAVE_CG)
	sge::cg::profile::object_unique_ptr
	create_cg_profile(
		sge::cg::profile::shader_type::type
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
		sge::renderer::texture::base const &
	);
#endif

	sge::renderer::target::onscreen &
	onscreen_target() const;

	sge::renderer::caps::object const &
	caps() const;
private:
	sge::renderer::depth_stencil_buffer::type const depth_stencil_buffer_;

	sge::opengl::context::object context_;

	typedef fcppt::scoped_ptr<
		sge::opengl::device_state
	> device_state_scoped_ptr;

	device_state_scoped_ptr const device_state_;

	typedef fcppt::scoped_ptr<
		sge::opengl::onscreen_target
	> onscreen_target_scoped_ptr;

	onscreen_target_scoped_ptr const onscreen_target_;

	sge::opengl::glew::scoped_init const glew_init_;

	typedef fcppt::scoped_ptr<
		sge::renderer::caps::object
	> caps_scoped_ptr;

	caps_scoped_ptr const caps_;
};

}
}

#endif
