/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SCENIC_RENDER_CONTEXT_FFP_OBJECT_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_FFP_OBJECT_HPP_INCLUDED

#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/state/core/blend/object_unique_ptr.hpp>
#include <sge/renderer/state/core/blend/scoped.hpp>
#include <sge/renderer/state/core/depth_stencil/object_unique_ptr.hpp>
#include <sge/renderer/state/core/depth_stencil/scoped.hpp>
#include <sge/renderer/state/core/rasterizer/object_unique_ptr.hpp>
#include <sge/renderer/state/core/rasterizer/scoped.hpp>
#include <sge/renderer/state/core/sampler/object_unique_ptr.hpp>
#include <sge/renderer/state/core/sampler/scoped.hpp>
#include <sge/renderer/state/ffp/lighting/object_unique_ptr.hpp>
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
#include <fcppt/config/external_begin.hpp>
#include <memory>
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
		sge::renderer::context::ffp &
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
	sge::renderer::context::ffp &context_;
	sge::renderer::vertex::scoped_declaration scoped_vertex_declaration_;
	sge::renderer::state::ffp::transform::object_unique_ptr projection_transform_;
	sge::renderer::state::ffp::transform::object_unique_ptr world_transform_;
	sge::renderer::vertex::count current_vertex_buffer_size_;
	std::unique_ptr<sge::renderer::vertex::scoped_buffer> current_vertex_buffer_;
	sge::renderer::state::ffp::lighting::material::object_unique_ptr current_material_;
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
