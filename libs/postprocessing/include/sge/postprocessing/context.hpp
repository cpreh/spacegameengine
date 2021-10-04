//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_POSTPROCESSING_CONTEXT_HPP_INCLUDED
#define SGE_POSTPROCESSING_CONTEXT_HPP_INCLUDED

#include <sge/postprocessing/fullscreen_quad.hpp>
#include <sge/postprocessing/detail/symbol.hpp>
#include <sge/renderer/context/scoped_core_unique_ptr.hpp>
#include <sge/renderer/depth_stencil_buffer/surface_unique_ptr.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/state/core/sampler/object_unique_ptr.hpp>
#include <sge/renderer/target/offscreen_unique_ptr.hpp>
#include <sge/renderer/texture/planar_ref.hpp>
#include <sge/renderer/texture/planar_unique_ptr.hpp>
#include <sge/renderer/vertex/declaration_unique_ptr.hpp>
#include <sge/shader/context_ref.hpp>
#include <sge/shader/pair.hpp>
#include <sge/shader/parameter/planar_texture.hpp>
#include <sge/shader/parameter/vector.hpp>
#include <sge/viewport/manager_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/optional/object_decl.hpp>
#include <fcppt/signal/auto_connection.hpp>


namespace sge::postprocessing
{

class context
{
	FCPPT_NONMOVABLE(
		context
	);
public:
	SGE_POSTPROCESSING_DETAIL_SYMBOL
	context(
		sge::renderer::device::core_ref,
		sge::viewport::manager_ref,
		sge::shader::context_ref
	);

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
	sge::renderer::device::core_ref const renderer_;
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
	fcppt::signal::auto_connection const viewport_connection_;

	using
	optional_planar_texture_ptr
	=
	fcppt::optional::object<
		sge::renderer::texture::planar_unique_ptr
	>;

	optional_planar_texture_ptr rendering_result_texture_;

	using
	optional_offscreen_target_ptr
	=
	fcppt::optional::object<
		sge::renderer::target::offscreen_unique_ptr
	>;

	optional_offscreen_target_ptr offscreen_target_;

	using
	optional_depth_stencil_surface_ptr
	=
	fcppt::optional::object<
		sge::renderer::depth_stencil_buffer::surface_unique_ptr
	>;

	optional_depth_stencil_surface_ptr depth_stencil_surface_;
		/*
	sge::renderer::target::offscreen_unique_ptr offscreen_downsampled_target_;
	sge::renderer::texture::planar_unique_ptr downsampled_texture_0_;
	sge::renderer::texture::planar_unique_ptr downsampled_texture_1_;
		*/

	void
	viewport_callback();

	void
	switch_target_texture(
		sge::renderer::texture::planar_ref
	);

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

	[[nodiscard]]
	sge::renderer::context::scoped_core_unique_ptr
	finalize();
};

}

#endif
