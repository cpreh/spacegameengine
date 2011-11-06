/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RENDERER_DEVICE_HPP_INCLUDED
#define SGE_RENDERER_DEVICE_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/renderer/caps_fwd.hpp>
#include <sge/renderer/clear_flags_field.hpp>
#include <sge/renderer/clip_plane.hpp>
#include <sge/renderer/clip_plane_index.hpp>
#include <sge/renderer/const_optional_vertex_declaration_fwd.hpp>
#include <sge/renderer/depth_stencil_format.hpp>
#include <sge/renderer/depth_stencil_surface_ptr.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/first_index.hpp>
#include <sge/renderer/first_vertex.hpp>
#include <sge/renderer/index_buffer_fwd.hpp>
#include <sge/renderer/index_buffer_ptr.hpp>
#include <sge/renderer/index_count.hpp>
#include <sge/renderer/indexed_primitive_type.hpp>
#include <sge/renderer/material_fwd.hpp>
#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/matrix_mode.hpp>
#include <sge/renderer/nonindexed_primitive_type.hpp>
#include <sge/renderer/onscreen_target_fwd.hpp>
#include <sge/renderer/optional_target_fwd.hpp>
#include <sge/renderer/primitive_count.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/sampler_stage_arg.hpp>
#include <sge/renderer/sampler_stage_arg_value.hpp>
#include <sge/renderer/sampler_stage_op.hpp>
#include <sge/renderer/sampler_stage_op_value.hpp>
#include <sge/renderer/stage.hpp>
#include <sge/renderer/symbol.hpp>
#include <sge/renderer/target_ptr.hpp>
#include <sge/renderer/vertex_buffer_fwd.hpp>
#include <sge/renderer/vertex_buffer_ptr.hpp>
#include <sge/renderer/vertex_count.hpp>
#include <sge/renderer/vertex_declaration_fwd.hpp>
#include <sge/renderer/vertex_declaration_ptr.hpp>
#include <sge/renderer/glsl/const_optional_program_fwd.hpp>
#include <sge/renderer/glsl/geometry_shader_ptr.hpp>
#include <sge/renderer/glsl/pixel_shader_ptr.hpp>
#include <sge/renderer/glsl/program_ptr.hpp>
#include <sge/renderer/glsl/string.hpp>
#include <sge/renderer/glsl/vertex_shader_ptr.hpp>
#include <sge/renderer/index/dynamic/format.hpp>
#include <sge/renderer/light/index.hpp>
#include <sge/renderer/light/object_fwd.hpp>
#include <sge/renderer/state/list_fwd.hpp>
#include <sge/renderer/texture/const_optional_base_fwd.hpp>
#include <sge/renderer/texture/cube_parameters_fwd.hpp>
#include <sge/renderer/texture/cube_ptr.hpp>
#include <sge/renderer/texture/depth_stencil_parameters_fwd.hpp>
#include <sge/renderer/texture/depth_stencil_ptr.hpp>
#include <sge/renderer/texture/planar_parameters_fwd.hpp>
#include <sge/renderer/texture/planar_ptr.hpp>
#include <sge/renderer/texture/volume_parameters_fwd.hpp>
#include <sge/renderer/texture/volume_ptr.hpp>
#include <sge/renderer/texture/filter/object_fwd.hpp>
#include <sge/renderer/vf/dynamic/format_fwd.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <sge/window/instance_ptr.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{

/**
 * \brief Renders primitives and creates renderer ressources
 *
 * sge::renderer::device is the most important class that a renderer plugin
 * implements. It can render indexed and nonindexed primitives and create
 * various ressources like textures and vertex and index buffers. It also
 * manages all state that a renderer might have. A window is always associated
 * with the device.
 */
class SGE_CLASS_SYMBOL device
{
	FCPPT_NONCOPYABLE(
		device
	);
protected:
	SGE_RENDERER_SYMBOL
	device();
public:
	/**
	 * \brief Begins the rendering operation
	 *
	 * To be able to call device::render_indexed or
	 * device::render_nonindexed, this function must be called first. It
	 * will also call clear() which will clear various buffers depending on
	 * the sge::renderer::state::bool_ flags set.  To end the rendering
	 * process and present it, use device::end_rendering.
	*/
	virtual void
	begin_rendering() = 0;

	/**
	 * \brief Ends the rendering operation
	 *
	 * After a call to device::begin_rendering this function must
	 * be called to present the rendered things in between.
	*/
	virtual void
	end_rendering() = 0;

	/**
	 * \brief Clears various buffers
	 *
	 * Clears the back buffer, depth buffer or stencil buffer depending on
	 * \a flags
	 *
	 * \param flags The buffers to clear
	*/
	virtual void
	clear(
		renderer::clear_flags_field const &flags
	) = 0;

	/**
	 * \brief Renders indexed geometry
	 *
	 * Renders indexed geometry using \a index_buffer and the currently set
	 * vertex buffers. \a primitive_count primitives are rendered. The
	 * indices necessary for this are extracted from \a index_buffer from
	 * position \a first_index to \a first_index +
	 * renderer::indices_per_primitive(primitive_type) * primitive_count.
	 * The possible values for the indices range from \a first_vertex to \a
	 * first_vertex + \a vertex_count. \a first_vertex and \a vertex_count
	 * should be considered as a possibility for optimization, in case only
	 * a portion of the vertex buffers is referenced by the call. The most
	 * conservative use is to pass 0 and vertex_buffer::size.
	 *
	 * \param index_buffer The index buffer to use
	 * \param first_vertex The minimum value for all used indices
	 * \param vertex_count The maximum value for all used indices
	 * \param primitive_type The type of primitive to render
	 * \param primitive_count The number of primitives to render
	 * \param first_index The offset into the index buffer
	 */
	virtual void
	render_indexed(
		renderer::index_buffer const &index_buffer,
		renderer::first_vertex first_vertex,
		renderer::vertex_count vertex_count,
		renderer::indexed_primitive_type::type primitive_type,
		renderer::primitive_count primitive_count,
		renderer::first_index first_index
	) = 0;

	/**
	 * \brief Renders non indexed geometry
	 *
	 * Renders non indexed geometry using the currently set vertex buffers.
	 * It uses renderer::nonindexed_primitive_count(\a vertex_count, \a
	 * primitive_type) vertices starting at \a first_vertex.
	 * For lines or a line strip, \a vertex_count must be at least 2, for
	 * triangles, a triangle strip or a triangle, \a vertex_count must be
	 * at least 3.
	 * For lines, vertex_count must be a multiple of 2, for triangles,
	 * vertex_count must be a multiple of 3.
	 *
	 * \param first_vertex The offset into the vertex buffer
	 * \param vertex_count The number of vertices to use
	 * \param primitive_type The type of primitive to render
	*/
	virtual void
	render_nonindexed(
		renderer::first_vertex first_vertex,
		renderer::vertex_count vertex_count,
		renderer::nonindexed_primitive_type::type primitive_type
	) = 0;

	virtual void
	activate_vertex_buffer(
		renderer::vertex_buffer const &
	) = 0;

	virtual void
	deactivate_vertex_buffer(
		renderer::vertex_buffer const &
	) = 0;

	virtual void
	vertex_declaration(
		renderer::const_optional_vertex_declaration const &
	) = 0;

	virtual void
	state(
		renderer::state::list const &
	) = 0;

	virtual void
	push_state(
		renderer::state::list const &
	) = 0;

	virtual void
	pop_state() = 0;

	virtual void
	material(
		renderer::material const &
	) = 0;

	virtual void
	enable_light(
		renderer::light::index,
		bool enable
	) = 0;

	virtual void
	light(
		renderer::light::index,
		renderer::light::object const &
	) = 0;

	virtual void
	enable_clip_plane(
		renderer::clip_plane_index,
		bool enable
	) = 0;

	virtual void
	clip_plane(
		renderer::clip_plane_index,
		renderer::clip_plane const &
	) = 0;

	virtual void
	sampler_stage_op(
		renderer::stage,
		renderer::sampler_stage_op::type,
		renderer::sampler_stage_op_value::type
	) = 0;

	virtual void
	sampler_stage_arg(
		renderer::stage,
		renderer::sampler_stage_arg::type,
		renderer::sampler_stage_arg_value::type
	) = 0;

	virtual void
	texture_filter(
		renderer::texture::filter::object const &,
		renderer::stage
	) = 0;

	virtual void
	texture(
		renderer::texture::const_optional_base const &,
		renderer::stage
	) = 0;

	virtual void
	transform(
		renderer::matrix_mode::type,
		renderer::matrix4 const &
	) = 0;

	virtual void
	target(
		renderer::optional_target const &
	) = 0;

	virtual renderer::glsl::program_ptr const
	create_glsl_program() = 0;

	virtual renderer::glsl::vertex_shader_ptr const
	create_glsl_vertex_shader(
		renderer::glsl::string const &
	) = 0;

	virtual renderer::glsl::pixel_shader_ptr const
	create_glsl_pixel_shader(
		renderer::glsl::string const &
	) = 0;

	virtual renderer::glsl::geometry_shader_ptr const
	create_glsl_geometry_shader(
		renderer::glsl::string const &
	) = 0;

	virtual void
	glsl_program(
		renderer::glsl::const_optional_program const &
	) = 0;

	virtual renderer::target_ptr const
	create_target() = 0;

	virtual renderer::texture::planar_ptr const
	create_planar_texture(
		renderer::texture::planar_parameters const &
	) = 0;

	virtual renderer::texture::depth_stencil_ptr const
	create_depth_stencil_texture(
		renderer::texture::depth_stencil_parameters const &
	) = 0;

	virtual renderer::depth_stencil_surface_ptr const
	create_depth_stencil_surface(
		renderer::dim2 const &,
		renderer::depth_stencil_format::type
	) = 0;

	virtual renderer::texture::volume_ptr const
	create_volume_texture(
		renderer::texture::volume_parameters const &
	) = 0;

	virtual renderer::texture::cube_ptr const
	create_cube_texture(
		renderer::texture::cube_parameters const &
	) = 0;

	virtual renderer::vertex_declaration_ptr const
	create_vertex_declaration(
		renderer::vf::dynamic::format const &
	) = 0;

	virtual renderer::vertex_buffer_ptr const
	create_vertex_buffer(
		renderer::vertex_declaration const &,
		renderer::vf::dynamic::part_index,
		renderer::vertex_count,
		renderer::resource_flags_field const &
	) = 0;

	virtual renderer::index_buffer_ptr const
	create_index_buffer(
		renderer::index::dynamic::format::type,
		renderer::index_count,
		renderer::resource_flags_field const &
	) = 0;

	virtual renderer::onscreen_target &
	onscreen_target() const = 0;

	virtual renderer::optional_target const
	target() const = 0;

	virtual renderer::caps const
	caps() const = 0;

	virtual sge::window::instance &
	window() const = 0;

	SGE_RENDERER_SYMBOL
	virtual ~device() = 0;
};

}
}

#endif
