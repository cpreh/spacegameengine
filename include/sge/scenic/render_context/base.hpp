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


#ifndef SGE_SCENIC_RENDER_CONTEXT_BASE_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_BASE_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/index/buffer_fwd.hpp>
#include <sge/renderer/target/base_fwd.hpp>
#include <sge/renderer/vertex/buffer_fwd.hpp>
#include <sge/scenic/index_buffer_range_fwd.hpp>
#include <sge/scenic/detail/symbol.hpp>
#include <sge/scenic/render_context/transform_matrix_type_fwd.hpp>
#include <sge/scenic/render_context/fog/optional_properties.hpp>
#include <sge/scenic/render_context/light/sequence.hpp>
#include <sge/scenic/render_context/material/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace scenic
{
namespace render_context
{
class SGE_CORE_DETAIL_CLASS_SYMBOL base
{
FCPPT_NONCOPYABLE(
	base);
public:
	virtual void
	transform(
		sge::scenic::render_context::transform_matrix_type,
		sge::renderer::matrix4 const &) = 0;

	virtual void
	material(
		sge::scenic::render_context::material::object const &) = 0;

	virtual void
	lights(
		sge::scenic::render_context::light::sequence const &) = 0;

	virtual void
	vertex_buffer(
		sge::renderer::vertex::buffer const &) = 0;

	virtual void
	fog(
		sge::scenic::render_context::fog::optional_properties const &) = 0;

	virtual
	void
	render(
		sge::renderer::index::buffer const &,
		sge::scenic::index_buffer_range const &) = 0;

	virtual
	sge::renderer::target::base &
	target() = 0;

	virtual
	~base() = 0;
protected:
	base();
};
}
}
}

#endif
