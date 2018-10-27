/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_RENDERER_VERTEX_BUFFER_HPP_INCLUDED
#define SGE_RENDERER_VERTEX_BUFFER_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/vertex/buffer_base.hpp>
#include <sge/renderer/vertex/buffer_fwd.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{
namespace vertex
{

/**
\brief A buffer for storing parts of vertices

\see sge::renderer::vertex::const_scoped_lock
\see sge::renderer::vertex::scoped_lock
\see sge::renderer::vertex::declaration
\see sge::renderer::device::activate_vertex_buffer
\see sge::renderer::device::craete_vertex_buffer
\see sge::renderer::device::deactivate_vertex_buffer
\see sge::renderer::vf::part
*/
class SGE_CORE_DETAIL_CLASS_SYMBOL buffer
:
	public
		sge::renderer::vertex::buffer_base
{
	FCPPT_NONCOPYABLE(
		buffer
	);
protected:
	SGE_RENDERER_DETAIL_SYMBOL
	buffer();
public:
	/**
	\brief Returns the resource flags the buffer has been created with
	*/
	virtual
	sge::renderer::resource_flags_field
	resource_flags() const = 0;

	/**
	\brief Returns the index of the vertex format part the buffer
	represents
	*/
	virtual
	sge::renderer::vf::dynamic::part_index
	format_part_index() const = 0;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::size_type
	linear_size() const;

	SGE_RENDERER_DETAIL_SYMBOL
	virtual
	~buffer();
};

}
}
}

#endif
