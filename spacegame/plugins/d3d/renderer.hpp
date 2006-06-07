#ifndef SGE_D3D_RENDERER_HPP_INCLUDED
#define SGE_D3D_RENDERER_HPP_INCLUDED

#include <vector>
#include <list>

#include "../../core/math/matrix4x4.hpp"
#include "../../core/math/vector3.hpp"
#include "../../core/math/vector4.hpp"
#include "../../core/renderer/renderer.hpp"
#include "../../core/main/win32_window.hpp"
#include "./vertex_format.hpp"

#include "./d3dinclude.hpp"

namespace sge
{
	class render_job_manager;

	namespace d3d
	{
		class resource;

		class renderer : public sge::renderer {
		public:
			renderer(d3d_device_ptr device, const renderer_parameters& param,
				     int adapter, win32_window_ptr wnd, d3d_ptr sys);

			texture_ptr        create_texture(texture::const_pointer data,
			                                  texture::size_type width,
				                              texture::size_type height,
											  unsigned mip_levels, resource_flag_t flags);
			volume_texture_ptr create_volume_texture(volume_texture::const_pointer data,
			                                         volume_texture::size_type width,
				                                     volume_texture::size_type height,
													 volume_texture::size_type depth,
													 resource_flag_t flags);
			cube_texture_ptr   create_cube_texture(const cube_side_src_array* data,
			                                       cube_texture::size_type size,
			                                       resource_flag_t flags);
			vertex_buffer_ptr  create_vertex_buffer(const sge::vertex_format& format,
				                                    vertex_buffer::size_type size,
												    resource_flag_t flags,
			                                        vertex_buffer::const_pointer data);
			index_buffer_ptr   create_index_buffer(index_buffer::size_type size,
				                                   resource_flag_t flags,
			                                       index_buffer::const_pointer data);
			render_target_ptr  create_render_target(render_target::size_type width,
				                                    render_target::size_type height);
		public:
			void set_int_state(int_state, int_type);
			void set_float_state(float_state, float_type);
			void set_bool_state(bool_state, bool_type);
			void set_texture(stage_type stage, texture_base_ptr tex);
			void set_material(const material& m);
			void set_matrix(matrix_usage Usage, const matrix4x4&);
			void set_texture_stage_op(stage_type stage, stage_op type,
			                          stage_op_value value);
			void set_texture_stage_arg(stage_type stage, stage_arg type,
			                           stage_arg_value value);
			void set_filter_state(stage_type stage, filter_arg type,
			                      filter_arg_value value);
			void process_render_job(const render_job& Job);
			void process_text_render_job(const text_render_job& Job,
			                             render_job_manager* rjm);
			void begin_rendering();
			void end_rendering();
			void render_all();
			void reset(const renderer_parameters* param);
			void set_view_port(const view_port& port);
			void set_render_target(render_target_ptr target);
			window_ptr get_render_window() const;
			unsigned get_screen_width() const;
			unsigned get_screen_height() const;
			void get_caps(renderer_caps& caps) const;
		private:
			typedef std::list<resource*> resource_list;
			d3d_ptr                  sys;
			d3d_device_ptr           device;
			d3d_surface_ptr          default_render_target;
			int                      adapter;
			renderer_parameters      parameters;
			win32_window_ptr         render_window;
			resource_list            resources;
			d3d_vertex_declaration_ptr  vertex_declaration;
			bool_type          clear_zbuffer, clear_stencil, clear_back_buffer;
			int_type           clear_color, stencil_clear_val;
			float_type         zbuffer_clear_val;
			renderer_caps      caps;
			vertex_buffer_ptr  vb;
			index_buffer_ptr   ib;
		private:
			void set_projection_matrix(const matrix4x4& matrix);
			void init();
			void release_resources();
			void set_vertex_buffer(vertex_buffer_ptr buffer);
			void set_index_buffer(index_buffer_ptr buffer);

			friend class resource;
		};
	}
}

#endif
