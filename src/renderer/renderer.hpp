/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_RENDERER_HPP_INCLUDED
#define SGE_RENDERER_HPP_INCLUDED

#include "../shared_ptr.hpp"
#include "types.hpp"
#include "vertex_buffer.hpp"
#include "index_buffer.hpp"
#include "texture_base.hpp"
#include "texture.hpp"
#include "cube_texture.hpp"
#include "volume_texture.hpp"
#include "render_target.hpp"
#include "light.hpp"
#include "../math/matrix.hpp"
#include "../window.hpp"

namespace sge
{

namespace int_state
{
	enum type {
		stencil_clear_val
	};
}

namespace float_state
{
	enum type {
		zbuffer_clear_val,
		fog_start,
		fog_end,
		fog_density
	};
}

namespace bool_state
{
	enum type {
		clear_zbuffer,
		clear_backbuffer,
		clear_stencil,
		enable_fog,
		enable_stencil,
		enable_alpha_blending,
		enable_zbuffer,
		enable_lighting,
		enable_culling
	};
}

namespace color_state
{
	enum type {
		clear_color,
		ambient_light_color,
		fog_color
	};
}

namespace cull_mode
{
	enum type {
		back,
		front
	};
}

namespace depth_func
{
	enum type {
		never,
		less,
		equal,
		less_equal,
		greater,
		not_equal,
		greater_equal,
		always
	};
}

namespace fog_mode
{
	enum type {
		linear,
		exp,
		exp2
	};
}

namespace indexed_primitive_type
{
	enum type {
		line,
		triangle
	};
}

namespace nonindexed_primitive_type
{
	enum type {
		point,
		line_strip,
		line_loop,
		triangle_strip,
		triangle_fan
	};
}

namespace source_blend_func
{
	enum type {
		zero,
		one,
		dest_color,
		inv_dest_color,
		src_alpha,
		inv_src_alpha,
		dest_alpha,
		inv_dest_alpha,
		src_alpha_sat
	};
}

namespace dest_blend_func
{
	enum type {
		zero,
		one,
		src_color,
		inv_src_color,
		src_alpha,
		inv_src_alpha,
		dest_alpha,
		inv_dest_alpha
	};
}

class renderer {
public:
	typedef uint32         int_type;
	typedef space_unit     float_type;
	typedef bool           bool_type;

	virtual void begin_rendering() = 0;
	virtual void end_rendering() = 0;
	virtual void render(vertex_buffer_ptr vb,
	                    index_buffer_ptr ib,
	                    vertex_buffer::size_type first_vertex,
	                    vertex_buffer::size_type num_vertices,
	                    indexed_primitive_type::type ptype,
	                    index_buffer::size_type primitive_count,
	                    index_buffer::size_type first_index) = 0;
	virtual void render(vertex_buffer_ptr vb,
	                    vertex_buffer::size_type first_vertex,
	                    vertex_buffer::size_type num_vertices,
	                    nonindexed_primitive_type::type ptype) = 0;

	virtual void set_int_state(int_state::type, int_type value) = 0;
	virtual void set_float_state(float_state::type, float_type value) = 0;
	virtual void set_bool_state(bool_state::type, bool_type value) = 0;
	virtual void set_color_state(color_state::type, color value) = 0;
	virtual void set_cull_mode(cull_mode::type) = 0;
	virtual void set_depth_func(depth_func::type) = 0;
	virtual void set_fog_mode(fog_mode::type) = 0;
	virtual void set_blend_func(source_blend_func::type, dest_blend_func::type) = 0;
	virtual void set_texture(texture_base_ptr tex, stage_type stage = 0) = 0;
	virtual void set_material(const material& mat) = 0;
	virtual void transform(const math::space_matrix& mat) = 0;
	virtual void projection(const math::space_matrix& mat) = 0;
	virtual void set_render_target(texture_ptr target = texture_ptr()) = 0;
	virtual void set_viewport(const viewport&) = 0;
	virtual void enable_light(light_index index, bool enable) = 0;
	virtual void set_light(light_index index, const light&) = 0;

	virtual render_target_ptr get_render_target() const = 0;

	virtual texture_ptr create_texture(texture::const_pointer data,
	                                   texture::size_type width,
	                                   texture::size_type height,
	                                   const filter_args& filter,
	                                   resource_flag_t flags = resource_flags::default_) = 0;

	virtual volume_texture_ptr create_volume_texture(volume_texture::const_pointer data,
	                                                 volume_texture::size_type width,
	                                                 volume_texture::size_type height,
	                                                 volume_texture::size_type depth,
	                                                 const filter_args& filter,
	                                                 resource_flag_t flags = resource_flags::default_) = 0;

	virtual cube_texture_ptr create_cube_texture(const cube_side_array* data,
	                                             cube_texture::size_type size,
	                                             const filter_args& filter,
	                                             resource_flag_t flags = resource_flags::default_) = 0;

	virtual vertex_buffer_ptr create_vertex_buffer(const vertex_format& format,
	                                               vertex_buffer::size_type size,
	                                               resource_flag_t flags = resource_flags::default_,
	                                               vertex_buffer::const_pointer data = 0) = 0;

	virtual index_buffer_ptr create_index_buffer(index_buffer::size_type size,
	                                             resource_flag_t flags = resource_flags::default_,
	                                             index_buffer::const_pointer data = 0) = 0;

	virtual const renderer_caps& caps() const = 0;
	virtual screen_size_t screen_size() const = 0;
	screen_unit screen_width() const;
	screen_unit screen_height() const;
	virtual window_ptr get_window() const = 0;

	virtual ~renderer(){}
};

typedef shared_ptr<renderer> renderer_ptr;

}

#endif
