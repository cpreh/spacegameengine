/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RENDERER_SCOPED_VERTEX_DECLARATION_AND_BUFFERS_HPP_INCLUDED
#define SGE_RENDERER_SCOPED_VERTEX_DECLARATION_AND_BUFFERS_HPP_INCLUDED

#include <sge/renderer/const_vertex_buffer_ref_container.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/scoped_vertex_buffer_fwd.hpp>
#include <sge/renderer/scoped_vertex_declaration.hpp>
#include <sge/renderer/symbol.hpp>
#include <sge/renderer/vertex_declaration_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace renderer
{

/**
 * \brief A scoped vertex declaration and buffers block
 *
 * Sets a vertex declaration following by one or multiple vertexbuffers in the
 * constructor and unsets them in the reverse order in the destructor.
*/
class scoped_vertex_declaration_and_buffers
{
	FCPPT_NONCOPYABLE(
		scoped_vertex_declaration_and_buffers
	);
public:
	/**
	 * \brief Sets the vertex declaration and buffers
	 *
	 * Sets \a vertex_declaration following by all vertex buffers in \a
	 * vertex_buffers for \a device.
	 *
	 * \param device The device to set the vertex declaration and buffers
	 * for
	 *
	 * \param vertex_declaration The vertex declaration to set
	 *
	 * \param vertex_buffers The vertex buffers to set
	*/
	SGE_RENDERER_SYMBOL
	scoped_vertex_declaration_and_buffers(
		renderer::device &device,
		renderer::vertex_declaration const &vertex_declaration,
		renderer::const_vertex_buffer_ref_container const &vertex_buffers
	);

	/**
	 * \brief Unsets the vertex buffers following by the vertex declaration
	*/
	SGE_RENDERER_SYMBOL
	~scoped_vertex_declaration_and_buffers();
private:
	renderer::scoped_vertex_declaration const scoped_declaration_;

	typedef boost::ptr_vector<
		renderer::scoped_vertex_buffer
	> scoped_vertex_buffer_vector;

	scoped_vertex_buffer_vector scoped_buffers_;
};

}
}

#endif
