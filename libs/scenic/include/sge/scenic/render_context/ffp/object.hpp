//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SCENIC_RENDER_CONTEXT_FFP_OBJECT_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_FFP_OBJECT_HPP_INCLUDED

#include <sge/renderer/context/ffp_ref.hpp>
#include <sge/renderer/state/core/blend/object_unique_ptr.hpp>
#include <sge/renderer/state/core/blend/scoped.hpp>
#include <sge/renderer/state/core/depth_stencil/object_unique_ptr.hpp>
#include <sge/renderer/state/core/depth_stencil/scoped.hpp>
#include <sge/renderer/state/core/rasterizer/object_unique_ptr.hpp>
#include <sge/renderer/state/core/rasterizer/scoped.hpp>
#include <sge/renderer/state/core/sampler/object_unique_ptr.hpp>
#include <sge/renderer/state/core/sampler/scoped.hpp>
#include <sge/renderer/state/ffp/lighting/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/lighting/light/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/lighting/light/parameters_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/material/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/transform/object_unique_ptr.hpp>
#include <sge/renderer/vertex/buffer_fwd.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/scoped_buffer_fwd.hpp>
#include <sge/renderer/vertex/scoped_declaration.hpp>
#include <sge/scenic/detail/symbol.hpp>
#include <sge/scenic/render_context/base.hpp>
#include <sge/scenic/render_context/ffp/manager_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace scenic
{
namespace render_context
{
namespace ffp
{
class object
:
	public sge::scenic::render_context::base
{
FCPPT_NONCOPYABLE(
	object);
public:
	SGE_SCENIC_DETAIL_SYMBOL
	object(
		sge::scenic::render_context::ffp::manager &_manager,
		sge::renderer::context::ffp_ref
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

	SGE_SCENIC_DETAIL_SYMBOL
	sge::renderer::target::base &
	target()
	override;

	SGE_SCENIC_DETAIL_SYMBOL
	~object()
	override;
private:
	friend class sge::scenic::render_context::ffp::manager;

	sge::scenic::render_context::ffp::manager &manager_;

	sge::renderer::context::ffp_ref const context_;

	sge::renderer::vertex::scoped_declaration scoped_vertex_declaration_;

	typedef
	fcppt::optional::object<
		sge::renderer::state::ffp::transform::object_unique_ptr
	>
	optional_transform_unique_ptr;

	optional_transform_unique_ptr projection_transform_;

	optional_transform_unique_ptr world_transform_;

	sge::renderer::vertex::count current_vertex_buffer_size_;

	typedef
	fcppt::unique_ptr<
		sge::renderer::vertex::scoped_buffer
	>
	scoped_vertex_buffer_unique_ptr;

	typedef
	fcppt::optional::object<
		scoped_vertex_buffer_unique_ptr
	>
	optional_scoped_vertex_buffer_unique_ptr;

	optional_scoped_vertex_buffer_unique_ptr current_vertex_buffer_;

	typedef
	fcppt::optional::object<
		sge::renderer::state::ffp::lighting::material::object_unique_ptr
	>
	optional_material_unique_ptr;

	optional_material_unique_ptr current_material_;

	typedef
	std::vector<
		sge::renderer::state::ffp::lighting::light::object_unique_ptr
	>
	light_ptr_vector;

	light_ptr_vector lights_;

	sge::renderer::state::core::sampler::object_unique_ptr const diffuse_texture_sampler_;

	sge::renderer::state::core::sampler::scoped scoped_sampler_;

	sge::renderer::state::ffp::lighting::object_unique_ptr const current_lighting_;

	sge::renderer::state::core::depth_stencil::object_unique_ptr const depth_stencil_state_;

	sge::renderer::state::core::blend::object_unique_ptr const blend_state_;

	sge::renderer::state::core::rasterizer::object_unique_ptr const rasterizer_state_;

	sge::renderer::state::core::depth_stencil::scoped scoped_depth_stencil_state_;

	sge::renderer::state::core::blend::scoped scoped_blend_state_;

	sge::renderer::state::core::rasterizer::scoped scoped_rasterizer_state_;
};

}
}
}
}

#endif
