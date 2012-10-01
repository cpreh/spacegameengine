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


#ifndef SGE_SCENIC_RENDER_CONTEXT_CG_OBJECT_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_CG_OBJECT_HPP_INCLUDED

#include <sge/renderer/index_buffer_fwd.hpp>
#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/scoped_vertex_declaration.hpp>
#include <sge/renderer/vertex_buffer_fwd.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/state/core/blend/scoped.hpp>
#include <sge/renderer/state/core/depth_stencil/scoped.hpp>
#include <sge/renderer/state/core/rasterizer/scoped.hpp>
#include <sge/renderer/state/core/sampler/scoped.hpp>
#include <sge/renderer/texture/planar_fwd.hpp>
#include <sge/scenic/index_buffer_range_fwd.hpp>
#include <sge/scenic/symbol.hpp>
#include <sge/scenic/render_context/base.hpp>
#include <sge/scenic/render_context/optional_planar_texture.hpp>
#include <sge/scenic/render_context/transform_matrix_type.hpp>
#include <sge/scenic/render_context/cg/manager_fwd.hpp>
#include <sge/scenic/render_context/light/sequence.hpp>
#include <sge/scenic/render_context/material/object_fwd.hpp>
#include <sge/shader/scoped_pair.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional.hpp>
#include <fcppt/math/matrix/object_impl.hpp>


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
FCPPT_NONCOPYABLE(
	object);
public:
	SGE_SCENIC_SYMBOL
	object(
		sge::scenic::render_context::cg::manager &,
		sge::renderer::context::core &);

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
	typedef
	fcppt::optional<sge::renderer::vertex_buffer const &>
	optional_vertex_buffer;

	sge::scenic::render_context::cg::manager &manager_;
	sge::renderer::context::core &context_;
	sge::renderer::scoped_vertex_declaration scoped_vd_;
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
