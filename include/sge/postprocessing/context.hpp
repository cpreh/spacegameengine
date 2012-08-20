#ifndef SGE_POSTPROCESSING_CONTEXT_HPP_INCLUDED
#define SGE_POSTPROCESSING_CONTEXT_HPP_INCLUDED

#include <sge/postprocessing/fullscreen_quad.hpp>
#include <sge/postprocessing/symbol.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/vertex_buffer_scoped_ptr.hpp>
#include <sge/renderer/vertex_declaration_scoped_ptr.hpp>
#include <sge/renderer/context/scoped_unique_ptr.hpp>
#include <sge/renderer/target/offscreen_scoped_ptr.hpp>
#include <sge/renderer/texture/planar_scoped_ptr.hpp>
#include <sge/renderer/depth_stencil_surface_scoped_ptr.hpp>
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
	SGE_POSTPROCESSING_SYMBOL
	context(
		sge::renderer::device &,
		sge::viewport::manager &,
		sge::shader::context &);

	SGE_POSTPROCESSING_SYMBOL
	sge::renderer::context::scoped_unique_ptr
	create_render_context();

	SGE_POSTPROCESSING_SYMBOL
	void
	render();

	SGE_POSTPROCESSING_SYMBOL
	sge::renderer::context::scoped_unique_ptr
	render_and_return_overlay();

	SGE_POSTPROCESSING_SYMBOL
	~context();
private:
	sge::renderer::device &renderer_;
	sge::renderer::vertex_declaration_scoped_ptr const quad_vertex_declaration_;
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
	fcppt::signal::scoped_connection viewport_connection_;
	sge::renderer::texture::planar_scoped_ptr rendering_result_texture_;
	sge::renderer::target::offscreen_scoped_ptr offscreen_target_;
	sge::renderer::depth_stencil_surface_scoped_ptr depth_stencil_surface_;
		/*
	sge::renderer::target::offscreen_scoped_ptr offscreen_downsampled_target_;
	sge::renderer::texture::planar_scoped_ptr downsampled_texture_0_;
	sge::renderer::texture::planar_scoped_ptr downsampled_texture_1_;
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

	sge::renderer::context::scoped_unique_ptr
	finalize();
};
}
}

#endif
