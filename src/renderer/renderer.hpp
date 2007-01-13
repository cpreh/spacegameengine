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
#include "./types.hpp"
#include "./vertex_buffer.hpp"
#include "./index_buffer.hpp"
#include "./texture_base.hpp"
#include "./texture.hpp"
#include "./cube_texture.hpp"
#include "./volume_texture.hpp"
#include "./render_target.hpp"
#include "../math/matrix.hpp"
#include "../window.hpp"

namespace sge
{

class renderer {
public:
	virtual void begin_rendering() = 0;
	virtual void end_rendering() = 0;
	virtual void render(vertex_buffer_ptr vb, index_buffer_ptr ib, unsigned first_vertex, unsigned num_vertices, primitive_type ptype, unsigned primitive_count, unsigned first_index = 0) = 0;

	virtual void set_int_state(int_state _state, int_type value) = 0;
	virtual void set_float_state(float_state _state, float_type value) = 0;
	virtual void set_bool_state(bool_state _state, bool_type value) = 0;
	virtual void set_texture_stage_op(stage_type stage, stage_op type, stage_op_value value) = 0;
	virtual void set_texture_stage_arg(stage_type stage, stage_arg type, stage_arg_value value) = 0;
	virtual void set_filter_state(filter_arg type, filter_arg_value arg, stage_type stage = 0) = 0;
	virtual void set_texture(texture_base_ptr tex, stage_type stage = 0) = 0;
	virtual void set_material(const material& mat) = 0;
	virtual void transform(const math::space_matrix& mat) = 0;
	virtual void projection(const math::space_matrix& mat) = 0;
	virtual void set_render_target(texture_ptr target) = 0;
	virtual void set_viewport(const viewport&) = 0;

	virtual render_target_ptr get_render_target() const = 0;

	virtual texture_ptr create_texture(texture::const_pointer data, texture::size_type width, texture::size_type height, unsigned mip_levels = 0, resource_flag_t flags = RF_Default) = 0;
	virtual volume_texture_ptr create_volume_texture(volume_texture::const_pointer data, volume_texture::size_type width, volume_texture::size_type height, volume_texture::size_type depth, resource_flag_t flags = RF_Default) = 0;
	virtual cube_texture_ptr create_cube_texture(const cube_side_array* data, cube_texture::size_type size, resource_flag_t flags = RF_Default) = 0;
	virtual vertex_buffer_ptr create_vertex_buffer(const vertex_format& format, vertex_buffer::size_type size, resource_flag_t flags = RF_Default, vertex_buffer::const_pointer data = 0) = 0;
	virtual index_buffer_ptr create_index_buffer(index_buffer::size_type size, resource_flag_t flags = RF_Default, index_buffer::const_pointer data = 0) = 0;
//	virtual render_target_ptr create_render_target(render_target::size_type width, render_target::size_type height) = 0;

	virtual const renderer_caps& caps() const = 0;
	virtual unsigned screen_width() const = 0;
	virtual unsigned screen_height() const = 0;
	virtual window_ptr get_window() const = 0;

	virtual ~renderer(){}
};

typedef shared_ptr<renderer> renderer_ptr;

}

#endif
