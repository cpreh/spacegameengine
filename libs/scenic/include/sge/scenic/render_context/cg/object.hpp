//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SCENIC_RENDER_CONTEXT_CG_OBJECT_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_CG_OBJECT_HPP_INCLUDED

#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/context/core_ref.hpp>
#include <sge/renderer/index/buffer_fwd.hpp>
#include <sge/renderer/state/core/blend/scoped.hpp>
#include <sge/renderer/state/core/depth_stencil/scoped.hpp>
#include <sge/renderer/state/core/rasterizer/scoped.hpp>
#include <sge/renderer/state/core/sampler/scoped.hpp>
#include <sge/renderer/texture/planar_fwd.hpp>
#include <sge/renderer/vertex/buffer_fwd.hpp>
#include <sge/renderer/vertex/scoped_declaration.hpp>
#include <sge/scenic/index_buffer_range_fwd.hpp>
#include <sge/scenic/detail/symbol.hpp>
#include <sge/scenic/render_context/base.hpp>
#include <sge/scenic/render_context/optional_planar_texture.hpp>
#include <sge/scenic/render_context/transform_matrix_type.hpp>
#include <sge/scenic/render_context/cg/manager_fwd.hpp>
#include <sge/scenic/render_context/light/sequence.hpp>
#include <sge/scenic/render_context/material/object_fwd.hpp>
#include <sge/shader/scoped_pair.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/math/matrix/object_impl.hpp>
#include <fcppt/optional/reference.hpp>


namespace sge
{
namespace scenic
{
namespace render_context
{
namespace cg
{

class object
:
	public sge::scenic::render_context::base
{
	FCPPT_NONMOVABLE(
		object
	);
public:
	SGE_SCENIC_DETAIL_SYMBOL
	object(
		fcppt::reference<
			sge::scenic::render_context::cg::manager
		>,
		sge::renderer::context::core_ref
	);

	SGE_SCENIC_DETAIL_SYMBOL
	void
	transform(
		sge::scenic::render_context::transform_matrix_type,
		sge::renderer::matrix4 const &
	)
	override;

	SGE_SCENIC_DETAIL_SYMBOL
	void
	material(
		sge::scenic::render_context::material::object const &
	)
	override;

	SGE_SCENIC_DETAIL_SYMBOL
	void
	lights(
		sge::scenic::render_context::light::sequence const &
	)
	override;

	SGE_SCENIC_DETAIL_SYMBOL
	void
	vertex_buffer(
		sge::renderer::vertex::buffer const &
	)
	override;

	SGE_SCENIC_DETAIL_SYMBOL
	void
	fog(
		sge::scenic::render_context::fog::optional_properties const &
	)
	override;

	SGE_SCENIC_DETAIL_SYMBOL
	void
	render(
		sge::renderer::index::buffer const &,
		sge::scenic::index_buffer_range const &
	)
	override;

	[[nodiscard]]
	SGE_SCENIC_DETAIL_SYMBOL
	sge::renderer::target::base &
	target()
	override;

	SGE_SCENIC_DETAIL_SYMBOL
	~object()
	override;
private:
	using
	optional_vertex_buffer
	=
	fcppt::optional::reference<
		sge::renderer::vertex::buffer const
	>;

	fcppt::reference<
		sge::scenic::render_context::cg::manager
	> const manager_;
	sge::renderer::context::core_ref const context_;
	sge::renderer::vertex::scoped_declaration scoped_vd_;
	sge::renderer::state::core::depth_stencil::scoped depth_stencil_state_;
	sge::renderer::state::core::blend::scoped blend_state_;
	sge::renderer::state::core::rasterizer::scoped rasterizer_state_;
	sge::shader::scoped_pair scoped_shader_;
	sge::renderer::state::core::sampler::scoped sampler_state_;
	sge::renderer::matrix4 current_world_;
	sge::renderer::matrix4 current_projection_;
	optional_vertex_buffer current_vertex_buffer_;
};
}
}
}
}

#endif
