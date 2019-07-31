//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_RENDER_CONTEXT_OBJECT_HPP_INCLUDED
#define SGE_D3D9_RENDER_CONTEXT_OBJECT_HPP_INCLUDED

#include <sge/d3d9/render_context/parameters.hpp>
#include <sge/d3d9/render_context/scoped_target.hpp>
#include <sge/renderer/config.hpp>
#include <sge/renderer/primitive_count.hpp>
#include <sge/renderer/primitive_type_fwd.hpp>
#include <sge/renderer/clear/parameters_fwd.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/index/buffer_fwd.hpp>
#include <sge/renderer/index/count.hpp>
#include <sge/renderer/index/first.hpp>
#include <sge/renderer/state/core/blend/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/core/depth_stencil/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/core/rasterizer/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/core/sampler/const_optional_object_ref_map.hpp>
#include <sge/renderer/state/ffp/alpha_test/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/ffp/clip_plane/const_object_ref_vector.hpp>
#include <sge/renderer/state/ffp/fog/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/light/const_object_ref_vector.hpp>
#include <sge/renderer/state/ffp/lighting/material/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/ffp/misc/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/ffp/sampler/const_object_ref_vector.hpp>
#include <sge/renderer/state/ffp/transform/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/ffp/transform/mode_fwd.hpp>
#include <sge/renderer/target/base_fwd.hpp>
#include <sge/renderer/target/offscreen_fwd.hpp>
#include <sge/renderer/texture/const_optional_base_ref_fwd.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <sge/renderer/vertex/buffer_fwd.hpp>
#include <sge/renderer/vertex/const_optional_declaration_ref_fwd.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional/reference.hpp>

#if defined(SGE_RENDERER_HAVE_CG)
#include <sge/d3d9/cg/scoped_device.hpp>
#include <sge/renderer/cg/loaded_program_fwd.hpp>
#include <sge/renderer/cg/loaded_texture_fwd.hpp>
#endif


namespace sge
{
namespace d3d9
{
namespace render_context
{

class object
:
	public sge::renderer::context::ffp
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	explicit
	object(
		sge::d3d9::render_context::parameters const &
	);

	~object()
	override;

	bool
	needs_present() const;
private:
	sge::renderer::target::base &
	target()
	override;

	void
	clear(
		sge::renderer::clear::parameters const &
	)
	override;

	void
	offscreen_target(
		sge::renderer::target::optional_offscreen_ref const &
	)
	override;

	void
	render_indexed(
		sge::renderer::index::buffer const &,
		sge::renderer::vertex::first,
		sge::renderer::vertex::count,
		sge::renderer::primitive_type,
		sge::renderer::index::first,
		sge::renderer::index::count
	)
	override;

	void
	render_nonindexed(
		sge::renderer::vertex::first,
		sge::renderer::vertex::count,
		sge::renderer::primitive_type
	)
	override;

	void
	activate_vertex_buffer(
		sge::renderer::vertex::buffer const &
	)
	override;

	void
	deactivate_vertex_buffer(
		sge::renderer::vertex::buffer const &
	)
	override;

	void
	vertex_declaration(
		sge::renderer::vertex::const_optional_declaration_ref const &
	)
	override;

	void
	texture(
		sge::renderer::texture::const_optional_base_ref const &,
		sge::renderer::texture::stage
	)
	override;

	void
	blend_state(
		sge::renderer::state::core::blend::const_optional_object_ref const &
	)
	override;

	void
	depth_stencil_state(
		sge::renderer::state::core::depth_stencil::const_optional_object_ref const &
	)
	override;

	void
	rasterizer_state(
		sge::renderer::state::core::rasterizer::const_optional_object_ref const &
	)
	override;

	void
	sampler_state(
		sge::renderer::state::core::sampler::const_optional_object_ref_map const &
	)
	override;

#if defined(SGE_RENDERER_HAVE_CG)
	void
	set_cg_program(
		sge::renderer::cg::loaded_program const &
	)
	override;

	void
	unset_cg_program(
		sge::renderer::cg::loaded_program const &
	)
	override;

	sge::renderer::texture::stage const
	set_cg_texture(
		sge::renderer::cg::loaded_texture const &
	)
	override;

	void
	unset_cg_texture(
		sge::renderer::cg::loaded_texture const &
	)
	override;
#endif

	void
	alpha_test_state(
		sge::renderer::state::ffp::alpha_test::const_optional_object_ref const &
	)
	override;

	void
	clip_plane_state(
		sge::renderer::state::ffp::clip_plane::const_object_ref_vector const &
	)
	override;

	void
	fog_state(
		sge::renderer::state::ffp::fog::const_optional_object_ref const &
	)
	override;

	void
	lighting_state(
		sge::renderer::state::ffp::lighting::const_optional_object_ref const &
	)
	override;

	void
	lights_state(
		sge::renderer::state::ffp::lighting::light::const_object_ref_vector const &
	)
	override;

	void
	material_state(
		sge::renderer::state::ffp::lighting::material::const_optional_object_ref const &
	)
	override;

	void
	misc_state(
		sge::renderer::state::ffp::misc::const_optional_object_ref const &
	)
	override;

	void
	sampler_ffp_state(
		sge::renderer::state::ffp::sampler::const_object_ref_vector const &
	)
	override;

	void
	transform(
		sge::renderer::state::ffp::transform::mode,
		sge::renderer::state::ffp::transform::const_optional_object_ref const &
	)
	override;

	sge::d3d9::render_context::parameters const parameters_;

	sge::d3d9::render_context::scoped_target const scoped_target_;

	typedef
	fcppt::optional::reference<
		sge::d3d9::target::base
	>
	optional_target_base_ref;

	optional_target_base_ref offscreen_target_;

#if defined(SGE_RENDERER_HAVE_CG)
	sge::d3d9::cg::scoped_device const scoped_cg_device_;
#endif
};

}
}
}

#endif
