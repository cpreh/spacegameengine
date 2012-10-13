/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include <sge/renderer/scoped_vertex_buffer_fwd.hpp>
#include <sge/renderer/scoped_vertex_declaration.hpp>
#include <sge/renderer/vertex_count.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/state/core/blend/object_scoped_ptr.hpp>
#include <sge/renderer/state/core/blend/scoped.hpp>
#include <sge/renderer/state/core/depth_stencil/object_scoped_ptr.hpp>
#include <sge/renderer/state/core/depth_stencil/scoped.hpp>
#include <sge/renderer/state/core/rasterizer/object_scoped_ptr.hpp>
#include <sge/renderer/state/core/rasterizer/scoped.hpp>
#include <sge/renderer/state/core/sampler/object_scoped_ptr.hpp>
#include <sge/renderer/state/core/sampler/scoped.hpp>
#include <sge/renderer/state/ffp/lighting/object_scoped_ptr.hpp>
#include <sge/renderer/state/ffp/lighting/light/parameters_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/material/object_scoped_ptr.hpp>
#include <sge/renderer/state/ffp/transform/object_scoped_ptr.hpp>
#include <sge/scenic/symbol.hpp>
#include <sge/scenic/render_context/base.hpp>
#include <sge/scenic/render_context/ffp/manager_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>


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
	SGE_SCENIC_SYMBOL
	object(
		sge::scenic::render_context::ffp::manager &_manager,
		sge::renderer::context::ffp &);

	SGE_SCENIC_SYMBOL
	void
	transform(
		sge::scenic::render_context::transform_matrix_type::type,
		sge::renderer::matrix4 const &);

	SGE_SCENIC_SYMBOL
	void
	material(
		sge::scenic::render_context::material::object const &);

	SGE_SCENIC_SYMBOL
	void
	lights(
		sge::scenic::render_context::light::sequence const &);

	SGE_SCENIC_SYMBOL
	void
	vertex_buffer(
		sge::renderer::vertex_buffer const &);

	SGE_SCENIC_SYMBOL
	void
	fog(
		sge::scenic::render_context::fog::optional_properties const &);

	SGE_SCENIC_SYMBOL
	void
	render(
		sge::renderer::index_buffer const &,
		sge::scenic::index_buffer_range const &);

	SGE_SCENIC_SYMBOL
	sge::renderer::target::base &
	target();

	SGE_SCENIC_SYMBOL
	~object();
private:
	friend class sge::scenic::render_context::ffp::manager;

	sge::scenic::render_context::ffp::manager &manager_;
	sge::renderer::context::ffp &context_;
	sge::renderer::scoped_vertex_declaration scoped_vertex_declaration_;
	sge::renderer::state::ffp::transform::object_scoped_ptr projection_transform_;
	sge::renderer::state::ffp::transform::object_scoped_ptr world_transform_;
	sge::renderer::vertex_count current_vertex_buffer_size_;
	fcppt::scoped_ptr<sge::renderer::scoped_vertex_buffer> current_vertex_buffer_;
	sge::renderer::state::ffp::lighting::material::object_scoped_ptr current_material_;
	sge::renderer::state::core::sampler::object_scoped_ptr const diffuse_texture_sampler_;
	sge::renderer::state::core::sampler::scoped scoped_sampler_;
	sge::renderer::state::ffp::lighting::object_scoped_ptr const current_lighting_;
	sge::renderer::state::core::depth_stencil::object_scoped_ptr const depth_stencil_state_;
	sge::renderer::state::core::blend::object_scoped_ptr const blend_state_;
	sge::renderer::state::core::rasterizer::object_scoped_ptr const rasterizer_state_;
	sge::renderer::state::core::depth_stencil::scoped scoped_depth_stencil_state_;
	sge::renderer::state::core::blend::scoped scoped_blend_state_;
	sge::renderer::state::core::rasterizer::scoped scoped_rasterizer_state_;
};
}
}
}
}

#endif
