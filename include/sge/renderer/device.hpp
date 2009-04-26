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

#include <sge/renderer/any_matrix.hpp>
#include <sge/renderer/vertex_buffer_fwd.hpp>
#include <sge/renderer/index_buffer_fwd.hpp>
#include <sge/renderer/texture_base_fwd.hpp>
#include <sge/renderer/texture_fwd.hpp>
#include <sge/renderer/cube_texture_fwd.hpp>
//#include <sge/renderer/volume_texture.hpp>
#include <sge/renderer/target_fwd.hpp>
#include <sge/renderer/vf/dynamic_view.hpp>
#include <sge/renderer/light_index.hpp>
#include <sge/renderer/glsl/program_fwd.hpp>
#include <sge/renderer/glsl/string.hpp>
#include <sge/renderer/glsl/istream.hpp>
#include <sge/renderer/primitive.hpp>
#include <sge/renderer/image_view.hpp>
#include <sge/renderer/color_format.hpp>
#include <sge/renderer/texture_stage.hpp>
#include <sge/renderer/stage_type.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/dim_type.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/resource_flags.hpp>
#include <sge/renderer/viewport_mode.hpp>
#include <sge/renderer/index/view.hpp>
#include <sge/renderer/index/format.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/window/instance_fwd.hpp>
#include <sge/export.hpp>
#include <sge/noncopyable.hpp>

namespace sge
{
namespace renderer
{
namespace state
{
class list;
}

namespace vf
{
class dynamic_format;
}

namespace filter
{
class texture;
}

class viewport;
class material;
class caps;
class light;

class SGE_CLASS_SYMBOL device {
	SGE_NONCOPYABLE(device)
protected:
	SGE_SYMBOL device();
public:
	virtual void begin_rendering() = 0;
	virtual void end_rendering() = 0;
	virtual void render(
		const_vertex_buffer_ptr vb,
		const_index_buffer_ptr ib,
		size_type first_vertex,
		size_type num_vertices,
		indexed_primitive_type::type ptype,
		size_type primitive_count,
		size_type first_index) = 0;
	virtual void render(
		const_vertex_buffer_ptr vb,
		size_type first_vertex,
		size_type num_vertices,
		nonindexed_primitive_type::type ptype) = 0;

	virtual void state(
		renderer::state::list const &) = 0;
	virtual void push_state(
		renderer::state::list const &) = 0;
	virtual void pop_state() = 0;

	virtual void material(
		renderer::material const &mat) = 0;
	virtual void enable_light(
		light_index index,
		bool enable) = 0;
	virtual void light(
		light_index index,
		renderer::light const &) = 0;
	virtual void texture_stage_op(
		stage_type stage,
		renderer::texture_stage_op::type,
		renderer::texture_stage_op_value::type) = 0;
	virtual void texture_stage_arg(
		stage_type stage,
		renderer::texture_stage_arg::type,
		renderer::texture_stage_arg_value::type) = 0;

	SGE_SYMBOL static texture_ptr const no_texture;
	virtual void texture(
		const_texture_base_ptr tex,
		stage_type stage = 0) = 0;

	virtual void transform(
		any_matrix const &mat) = 0;
	virtual void projection(
		any_matrix const &mat) = 0;
	virtual void texture_transform(
		any_matrix const &mat) = 0;

	SGE_SYMBOL static texture_ptr const default_target;
	virtual void target(texture_ptr) = 0;

	virtual void viewport(
		renderer::viewport const &) = 0;

	virtual void viewport_mode(
		renderer::viewport_mode::type) = 0;

	virtual glsl::program_ptr const
	create_glsl_program(
		glsl::string const &vertex_shader_source,
		glsl::string const &pixel_shader_source) = 0;
	virtual glsl::program_ptr const
	create_glsl_program(
		glsl::istream &vertex_shader_source,
		glsl::istream &pixel_shader_source) = 0;

	SGE_SYMBOL static glsl::program_ptr const no_program;
	virtual void glsl_program(renderer::glsl::program_ptr) = 0;

	virtual const_target_ptr const target() const = 0;

	SGE_SYMBOL texture_ptr const create_texture(
		const_image_view const &,
		filter::texture const &filter,
		resource_flag_t flags);

	virtual texture_ptr const create_texture(
		dim_type const &dim,
		color_format::type format,
		filter::texture const &filter,
		resource_flag_t flags) = 0;

	/*virtual const volume_texture_ptr create_volume_texture(
		volume_texture::image_view_array const &,
		filter::texture const &filter,
		resource_flag_t flags) = 0;*/

	virtual cube_texture_ptr const
	create_cube_texture(
		size_type border_size,
		color_format::type format,
		filter::texture const &filter,
		resource_flag_t flags) = 0;

	SGE_SYMBOL vertex_buffer_ptr const
	create_vertex_buffer(
		vf::const_dynamic_view const &,
		resource_flag_t flags);
	
	virtual vertex_buffer_ptr const
	create_vertex_buffer(
		vf::dynamic_format const &,
		size_type size,
		resource_flag_t flags) = 0;

	SGE_SYMBOL index_buffer_ptr const
	create_index_buffer(
		index::const_view const &,
		resource_flag_t flags);

	virtual index_buffer_ptr const
	create_index_buffer(
		index::format::type,
		size_type size,
		resource_flag_t flags) = 0;

	virtual renderer::caps const caps() const = 0;
	virtual renderer::screen_size const screen_size() const = 0;
	virtual sge::window::instance_ptr const window() const = 0;

	SGE_SYMBOL virtual ~device();
};

}
}

#endif
