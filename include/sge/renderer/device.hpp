/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include "../export.hpp"
#include "../window.hpp"
#include "../shared_ptr.hpp"
#include "../math/matrix.hpp"
#include "types.hpp"
#include "vertex_buffer.hpp"
#include "index_buffer.hpp"
#include "texture_base.hpp"
#include "texture.hpp"
#include "cube_texture.hpp"
#include "volume_texture.hpp"
#include "target.hpp"
#include "light.hpp"
#include "glsl/program.hpp"
#include "primitive.hpp"
#include "caps.hpp"
#include "states.hpp"
#include "image_view.hpp"
#include "color_format.hpp"

namespace sge
{
namespace renderer
{

struct viewport;
struct filter_args;
struct material;

namespace texture_stage_op
{
	enum type {
		color,
		alpha
	};
}

namespace texture_stage_op_value
{
	enum type {
		arg0,
		modulate,
		modulate2x,
		modulate4x,
		add,
		add2x,
		add4x,
		substract,
		add_signed,
		add_signed2x,
		interpolate
	};
}

namespace texture_stage_arg
{
	enum type {
		rgb0,
		rgb1,
		rgb2,
		alpha0,
		alpha1,
		alpha2
	};
}

namespace texture_stage_arg_value
{
	enum type {
		current,
		texture,
		constant
	};
}

class device {
public:
	typedef uint32     int_type;
	typedef int32      signed_type;
	typedef uint32     unsigned_type;
	typedef space_unit float_type;
	typedef bool       bool_type;

	virtual void begin_rendering() = 0;
	virtual void end_rendering() = 0;
	virtual void render(
		vertex_buffer_ptr vb,
		index_buffer_ptr ib,
		vertex_buffer::size_type first_vertex,
		vertex_buffer::size_type num_vertices,
		indexed_primitive_type::type ptype,
		index_buffer::size_type primitive_count,
		index_buffer::size_type first_index) = 0;
	virtual void render(
		vertex_buffer_ptr vb,
		vertex_buffer::size_type first_vertex,
		vertex_buffer::size_type num_vertices,
		nonindexed_primitive_type::type ptype) = 0;

	virtual void set_state(const state_list &) = 0;
	virtual void push_state(const state_list &) = 0;
	virtual void pop_level() = 0;

	virtual void set_material(const material& mat) = 0;
	virtual void enable_light(light_index index, bool enable) = 0;
	virtual void set_light(light_index index, const light&) = 0;
	virtual void set_texture_stage_op(
		stage_type stage,
		texture_stage_op::type,
		texture_stage_op_value::type) = 0;
	virtual void set_texture_stage_arg(
		stage_type stage,
		texture_stage_arg::type,
		texture_stage_arg_value::type) = 0;

	SGE_SYMBOL static const texture_ptr no_texture;
	virtual void set_texture(texture_base_ptr tex, stage_type stage = 0) = 0;
	virtual void transform(const math::space_matrix& mat) = 0;
	virtual void projection(const math::space_matrix& mat) = 0;

	SGE_SYMBOL static const texture_ptr default_render_target;
	virtual void set_render_target(texture_ptr target) = 0;
	virtual void set_viewport(const viewport&) = 0;

	virtual const glsl::program_ptr create_glsl_program(
		const std::string& vertex_shader_source,
		const std::string& pixel_shader_source) = 0;

	SGE_SYMBOL static const glsl::program_ptr no_program;
	virtual void set_glsl_program(glsl::program_ptr) = 0;

	virtual const target_ptr get_target() const = 0;

	SGE_SYMBOL texture_ptr const create_texture(
		const_image_view const &,
		filter_args const &filter,
		resource_flag_t flags);

	virtual const texture_ptr create_texture(
		texture::dim_type const &dim,
		color_format::type format,
		filter_args const &filter,
		resource_flag_t flags) = 0;

	/*virtual const volume_texture_ptr create_volume_texture(
		volume_texture::image_view_array const &,
		filter_args const &filter,
		resource_flag_t flags) = 0;*/

	virtual cube_texture_ptr const create_cube_texture(
		cube_texture::size_type border_size,
		color_format::type format,
		filter_args const &filter,
		resource_flag_t flags) = 0;

	vertex_buffer_ptr const create_vertex_buffer(
		const_vertex_view const &,
		resource_flag_t flags);
	
	virtual vertex_buffer_ptr const create_vertex_buffer(
		vertex_format const &,
		vertex_buffer::size_type size,
		resource_flag_t flags) = 0;

	index_buffer_ptr const create_index_buffer(
		const_dynamic_index_view const &,
		resource_flag_t flags);

	virtual index_buffer_ptr const create_index_buffer(
		index_format::type,
		index_buffer::size_type size,
		resource_flag_t flags) = 0;

	virtual caps const &get_caps() const = 0;
	virtual screen_size_t const screen_size() const = 0;
	virtual window_ptr const get_window() const = 0;

	SGE_SYMBOL screen_unit screen_width() const;
	SGE_SYMBOL screen_unit screen_height() const;
	SGE_SYMBOL space_unit aspect() const;

	virtual ~device();
};

typedef shared_ptr<device> device_ptr;

}
}

#endif
