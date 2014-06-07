/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_RENDERER_VERTEX_SCOPED_DECLARATION_AND_BUFFERS_HPP_INCLUDED
#define SGE_RENDERER_VERTEX_SCOPED_DECLARATION_AND_BUFFERS_HPP_INCLUDED

#include <sge/renderer/symbol.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/vertex/const_buffer_ref_container.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <sge/renderer/vertex/scoped_buffer_fwd.hpp>
#include <sge/renderer/vertex/scoped_declaration.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace renderer
{
namespace vertex
{

/**
\brief A scoped vertex declaration and buffers block

Sets a vertex declaration following by one or multiple vertexbuffers in the
constructor and unsets them in the reverse order in the destructor.
*/
class scoped_declaration_and_buffers
{
	FCPPT_NONCOPYABLE(
		scoped_declaration_and_buffers
	);
public:
	/**
	\brief Sets the vertex declaration and buffers

	Sets \a vertex_declaration following by all vertex buffers in \a
	vertex_buffers for \a device.

	\param context The context to set the vertex declaration and buffers
	for

	\param vertex_declaration The vertex declaration to set

	\param vertex_buffers The vertex buffers to set
	*/
	SGE_RENDERER_SYMBOL
	scoped_declaration_and_buffers(
		sge::renderer::context::core &context,
		sge::renderer::vertex::declaration const &vertex_declaration,
		sge::renderer::vertex::const_buffer_ref_container const &vertex_buffers
	);

	/**
	\brief Unsets the vertex buffers following by the vertex declaration
	*/
	SGE_RENDERER_SYMBOL
	~scoped_declaration_and_buffers();
private:
	sge::renderer::vertex::scoped_declaration const scoped_declaration_;

	typedef boost::ptr_vector<
		sge::renderer::vertex::scoped_buffer
	> scoped_buffer_vector;

	scoped_buffer_vector scoped_buffers_;
};

}
}
}

#endif
