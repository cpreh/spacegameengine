/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include <sge/renderer/vf/dynamic/const_view_fwd.hpp>
#include <sge/renderer/vf/dynamic/format_fwd.hpp>
#include <sge/renderer/filter/texture_fwd.hpp>
#include <sge/renderer/glsl/program_ptr.hpp>
#include <sge/renderer/glsl/optional_string.hpp>
#include <sge/renderer/glsl/string.hpp>
#include <sge/renderer/glsl/optional_istream.hpp>
#include <sge/renderer/glsl/vertex_shader_ptr.hpp>
#include <sge/renderer/glsl/pixel_shader_ptr.hpp>
#include <sge/renderer/state/list_fwd.hpp>
#include <sge/renderer/index/dynamic/const_view.hpp>
#include <sge/renderer/index/dynamic/format.hpp>
#include <sge/renderer/any_matrix.hpp>
#include <sge/renderer/vertex_buffer_ptr.hpp>
#include <sge/renderer/index_buffer_ptr.hpp>
#include <sge/renderer/const_texture_base_ptr.hpp>
#include <sge/renderer/texture_ptr.hpp>
#include <sge/renderer/cube_texture_ptr.hpp>
//#include <sge/renderer/volume_texture_ptr.hpp>
#include <sge/renderer/target_ptr.hpp>
#include <sge/renderer/light_index.hpp>
#include <sge/renderer/indexed_primitive_type.hpp>
#include <sge/renderer/nonindexed_primitive_type.hpp>
#include <sge/renderer/texture_stage_op.hpp>
#include <sge/renderer/texture_stage_op_value.hpp>
#include <sge/renderer/texture_stage_arg.hpp>
#include <sge/renderer/texture_stage_arg_value.hpp>
#include <sge/renderer/stage_type.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/dim_type.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/viewport_mode.hpp>
#include <sge/renderer/light_fwd.hpp>
#include <sge/renderer/material_fwd.hpp>
#include <sge/renderer/caps_fwd.hpp>
#include <sge/renderer/viewport_fwd.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/first_vertex.hpp>
#include <sge/renderer/vertex_count.hpp>
#include <sge/renderer/primitive_count.hpp>
#include <sge/renderer/first_index.hpp>
#include <sge/renderer/matrix_mode.hpp>
#include <sge/renderer/clip_plane_index.hpp>
#include <sge/renderer/clip_plane.hpp>
#include <sge/image/view/const_object.hpp>
#include <sge/image/color/format.hpp>
#include <sge/window/instance_ptr.hpp>
#include <sge/symbol.hpp>
#include <sge/class_symbol.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace renderer
{

class SGE_CLASS_SYMBOL device
{
	FCPPT_NONCOPYABLE(device)
protected:
	SGE_SYMBOL device();
public:
	virtual void
	begin_rendering() = 0;

	virtual void
	end_rendering() = 0;

	virtual void
	render(
		const_index_buffer_ptr,
		first_vertex,
		vertex_count,
		indexed_primitive_type::type ptype,
		primitive_count,
		first_index
	) = 0;

	virtual void
	render(
		first_vertex,
		vertex_count,
		nonindexed_primitive_type::type ptype
	) = 0;

	virtual void
	set_vertex_buffer(
		const_vertex_buffer_ptr
	) = 0;

	virtual void
	unset_vertex_buffer(
		const_vertex_buffer_ptr
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
		light_index,
		bool enable
	) = 0;

	virtual void
	light(
		light_index,
		renderer::light const &
	) = 0;

	virtual void
	enable_clip_plane(
		clip_plane_index,
		bool enable
	) = 0;

	virtual void
	clip_plane(
		clip_plane_index,
		renderer::clip_plane const &
	) = 0;

	virtual void
	texture_stage_op(
		stage_type,
		renderer::texture_stage_op::type,
		renderer::texture_stage_op_value::type
	) = 0;

	virtual void
	texture_stage_arg(
		stage_type,
		renderer::texture_stage_arg::type,
		renderer::texture_stage_arg_value::type
	) = 0;

	SGE_SYMBOL static const_texture_base_ptr const no_texture;

	virtual void
	texture(
		const_texture_base_ptr,
		stage_type = 0 
	) = 0;

	virtual void
	transform(
		matrix_mode::type,
		any_matrix const &
	) = 0;

	SGE_SYMBOL static texture_ptr const default_target;

	virtual void
	target(
		texture_ptr
	) = 0;

	virtual void
	viewport(
		renderer::viewport const &
	) = 0;

	virtual void
	viewport_mode(
		renderer::viewport_mode::type
	) = 0;

	SGE_SYMBOL
	glsl::program_ptr const
	create_glsl_program(
		glsl::optional_string const &vertex_shader_source,
		glsl::optional_string const &pixel_shader_source
	);

	SGE_SYMBOL
	glsl::program_ptr const
	create_glsl_program(
		glsl::optional_istream const &vertex_shader_source,
		glsl::optional_istream const &pixel_shader_source
	);

	virtual glsl::program_ptr const
	create_glsl_program() = 0;

	virtual glsl::vertex_shader_ptr const
	create_glsl_vertex_shader(
		glsl::string const &
	) = 0;

	virtual glsl::pixel_shader_ptr const
	create_glsl_pixel_shader(
		glsl::string const &
	) = 0;

	SGE_SYMBOL static glsl::program_ptr const no_program;

	virtual void
	glsl_program(
		renderer::glsl::program_ptr
	) = 0;

	virtual const_target_ptr const
	target() const = 0;

	SGE_SYMBOL texture_ptr const
	create_texture(
		image::view::const_object const &,
		filter::texture const &,
		resource_flags_field const &
	);

	virtual texture_ptr const
	create_texture(
		dim_type const &,
		image::color::format::type,
		filter::texture const &,
		resource_flags_field const &
	) = 0;

	/*
	SGE_SYMBOL volume_texture_ptr const
	create_volume_texture(
		image::view::const_object3 const &,
		filter::texture const &filter,
		resource_flags_field const & flags);

	virtual volume_texture_ptr const
	create_volume_texture(
		dim3_type const &dim,
		image::color::format::type format,
		filter::texture const &filter,
		resource_flags_field const & flags) = 0;
	*/

	virtual cube_texture_ptr const
	create_cube_texture(
		size_type border_size,
		image::color::format::type format,
		filter::texture const &filter,
		resource_flags_field const &
	) = 0;

	SGE_SYMBOL vertex_buffer_ptr const
	create_vertex_buffer(
		vf::dynamic::const_view const &,
		resource_flags_field const &
	);

	virtual vertex_buffer_ptr const
	create_vertex_buffer(
		vf::dynamic::format const &,
		size_type size,
		resource_flags_field const &
	) = 0;

	SGE_SYMBOL index_buffer_ptr const
	create_index_buffer(
		index::dynamic::const_view const &,
		resource_flags_field const &
	);

	virtual index_buffer_ptr const
	create_index_buffer(
		index::dynamic::format::type,
		size_type size,
		resource_flags_field const &
	) = 0;

	virtual renderer::caps const
	caps() const = 0;

	virtual renderer::screen_size const
	screen_size() const = 0;

	virtual sge::window::instance_ptr const
	window() const = 0;

	SGE_SYMBOL virtual ~device();
};

}
}

#endif
