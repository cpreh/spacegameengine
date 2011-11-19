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


#ifndef SGE_RENDERER_SCOPED_VERTEX_DECLARATION_HPP_INCLUDED
#define SGE_RENDERER_SCOPED_VERTEX_DECLARATION_HPP_INCLUDED

#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/symbol.hpp>
#include <sge/renderer/vertex_declaration_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{

/**
 * \brief A scoped vertex declaration block
 *
 * Sets a vertex declaration in the constructor and unsets it in the
 * destructor.
*/
class scoped_vertex_declaration
{
	FCPPT_NONCOPYABLE(
		scoped_vertex_declaration
	);
public:
	/**
	 * \brief Sets a vertex declaration
	 *
	 * Sets \a vertex_declaration for \a device
	 *
	 * \param device The device to set the vertex declaration for
	 *
	 * \param vertex_declaration The vertex declaration to set
	*/
	SGE_RENDERER_SYMBOL
	scoped_vertex_declaration(
		renderer::device &device,
		renderer::vertex_declaration const &vertex_declaration
	);

	/**
	 * \brief Unsets the vertex declaration
	*/
	SGE_RENDERER_SYMBOL
	~scoped_vertex_declaration();
private:
	renderer::device &device_;
};

}
}

#endif
