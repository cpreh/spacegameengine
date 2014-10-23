/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_POSTPROCESSING_CONTEXT_HPP_INCLUDED
#define SGE_POSTPROCESSING_CONTEXT_HPP_INCLUDED

#include <sge/postprocessing/fullscreen_quad.hpp>
#include <sge/postprocessing/detail/symbol.hpp>
#include <sge/renderer/context/scoped_core_unique_ptr.hpp>
#include <sge/renderer/depth_stencil_buffer/surface_unique_ptr.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/state/core/sampler/object_unique_ptr.hpp>
#include <sge/renderer/target/offscreen_unique_ptr.hpp>
#include <sge/renderer/texture/planar_unique_ptr.hpp>
#include <sge/renderer/vertex/declaration_unique_ptr.hpp>
#include <sge/shader/context_fwd.hpp>
#include <sge/shader/pair.hpp>
#include <sge/shader/parameter/planar_texture.hpp>
#include <sge/shader/parameter/vector.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/scoped_connection.hpp>


namespace sge
{
namespace postprocessing
{
class context
{
FCPPT_NONCOPYABLE(
	context);
public:
	SGE_POSTPROCESSING_DETAIL_SYMBOL
	context(
		sge::renderer::device::core &,
		sge::viewport::manager &,
		sge::shader::context &);

	SGE_POSTPROCESSING_DETAIL_SYMBOL
	sge::renderer::context::scoped_core_unique_ptr
	create_render_context();

	SGE_POSTPROCESSING_DETAIL_SYMBOL
	void
	render();

	SGE_POSTPROCESSING_DETAIL_SYMBOL
	sge::renderer::context::scoped_core_unique_ptr
	render_and_return_overlay();

	SGE_POSTPROCESSING_DETAIL_SYMBOL
	~context();
private:
	sge::renderer::device::core &renderer_;
	sge::renderer::vertex::declaration_unique_ptr const quad_vertex_declaration_;
	sge::renderer::state::core::sampler::object_unique_ptr const point_sampler_;
	sge::postprocessing::fullscreen_quad fullscreen_quad_;
		/*
	sge::shader::pair downsample_shader_;
	sge::shader::parameter::planar_texture downsample_input_texture_parameter_;
	sge::shader::pair blur_h_shader_;
	sge::shader::parameter::planar_texture blur_h_input_texture_parameter_;
	sge::shader::pair blur_v_shader_;
	sge::shader::parameter::planar_texture blur_v_input_texture_parameter_;
		*/
	sge::shader::pair finalize_shader_;
	sge::shader::parameter::planar_texture finalize_input_texture_parameter_;
		//sge::shader::parameter::planar_texture finalize_blurred_texture_parameter_;
	fcppt::signal::scoped_connection const viewport_connection_;
	sge::renderer::texture::planar_unique_ptr rendering_result_texture_;
	sge::renderer::target::offscreen_unique_ptr offscreen_target_;
	sge::renderer::depth_stencil_buffer::surface_unique_ptr depth_stencil_surface_;
		/*
	sge::renderer::target::offscreen_unique_ptr offscreen_downsampled_target_;
	sge::renderer::texture::planar_unique_ptr downsampled_texture_0_;
	sge::renderer::texture::planar_unique_ptr downsampled_texture_1_;
		*/

	void
	viewport_callback();

	void
	switch_target_texture(
		sge::renderer::texture::planar &);

		/*
	void
	switch_downsampled_target_texture(
		sge::renderer::texture::planar &);

	void
	downsample();

	void
	blur_h();

	void
	blur_v();

	void
	blur();
		*/

	sge::renderer::context::scoped_core_unique_ptr
	finalize();
};
}
}

#endif
