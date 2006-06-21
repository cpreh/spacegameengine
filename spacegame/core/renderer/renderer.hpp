#ifndef SGE_RENDERER_HPP_INCLUDED
#define SGE_RENDERER_HPP_INCLUDED

#include "../main/shared_ptr.hpp"
#include "./renderer_types.hpp"
#include "./vertex_buffer.hpp"
#include "./index_buffer.hpp"
#include "./texture_base.hpp"
#include "./texture.hpp"
#include "./cube_texture.hpp"
#include "./volume_texture.hpp"
#include "./render_target.hpp"

namespace sge
{

class renderer {
public:
	typedef sge::matrix4x4<space_unit> matrix4x4;

	virtual void begin_rendering() = 0;
	virtual void end_rendering() = 0;
	virtual void render(vertex_buffer_ptr vb, index_buffer_ptr ib, unsigned first_vertex, unsigned num_vertices, primitive_type ptype, unsigned pcount, unsigned first_index = 0) = 0;
	virtual void set_int_state(int_state _state, int_type value) = 0;
	virtual void set_float_state(float_state _state, float_type value) = 0;
	virtual void set_bool_state(bool_state _state, bool_type value) = 0;
	virtual void set_texture_stage_op(stage_type stage, stage_op type, stage_op_value value) = 0;
	virtual void set_texture_stage_arg(stage_type stage, stage_arg type, stage_arg_value value) = 0;
	virtual void set_filter_state(stage_type stage, filter_arg type, filter_arg_value arg) = 0;
	virtual void set_texture(stage_type stage, texture_base_ptr tex) = 0;
	virtual void set_material(const material& mat) = 0;
	virtual void set_matrix(matrix_usage usage, const matrix4x4& mat) = 0;
	virtual void set_render_target(render_target_ptr target) = 0;
	virtual unsigned get_screen_width() const = 0;
	virtual unsigned get_screen_height() const = 0;
	virtual window_ptr get_window() const = 0;

	virtual texture_ptr create_texture(texture::const_pointer data, texture::size_type width, texture::size_type height, unsigned mip_levels = 1, resource_flag_t flags = RF_Default) = 0;
	virtual volume_texture_ptr create_volume_texture(volume_texture::const_pointer data, volume_texture::size_type width, volume_texture::size_type height, volume_texture::size_type depth, resource_flag_t flags = RF_Default) = 0;
	virtual cube_texture_ptr create_cube_texture(const cube_side_src_array* data, cube_texture::size_type size, resource_flag_t flags = RF_Default) = 0;
	virtual vertex_buffer_ptr create_vertex_buffer(const vertex_format& format, vertex_buffer::size_type size, resource_flag_t flags = RF_Default, vertex_buffer::const_pointer data = 0) = 0;
	virtual index_buffer_ptr create_index_buffer(index_buffer::size_type size, resource_flag_t flags = RF_Default, index_buffer::const_pointer data = 0) = 0;
	virtual render_target_ptr create_render_target(render_target::size_type width, render_target::size_type height) = 0;

	virtual void reset(const renderer_parameters* param) = 0;
	virtual void get_caps(renderer_caps& caps) const = 0;

	virtual ~renderer(){}
};

typedef shared_ptr<renderer> renderer_ptr;

}

#endif
