//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VERTEX_SCOPED_BUFFER_HPP_INCLUDED
#define SGE_RENDERER_VERTEX_SCOPED_BUFFER_HPP_INCLUDED

#include <sge/renderer/context/core_ref.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/vertex/const_buffer_ref.hpp>
#include <sge/renderer/vertex/scoped_buffer_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge::renderer::vertex
{

/**
\brief A scoped vertex buffer block

Sets a vertex buffer in the constructor and unsets it in the destructor.
*/
class scoped_buffer
{
	FCPPT_NONMOVABLE(
		scoped_buffer
	);
public:
	/**
	\brief Sets a vertex buffer

	Sets \a vertex_buffer for \a device

	\param context The context to set the vertex buffer for

	\param vertex_buffer The vertex buffer to set

	\warning The behaviour is undefined if the vertex buffer is already set

	\warning The behaviour is undefined if the corresponding vertex
	declaration is not set
	*/
	SGE_RENDERER_DETAIL_SYMBOL
	scoped_buffer(
		sge::renderer::context::core_ref context,
		sge::renderer::vertex::const_buffer_ref vertex_buffer
	);

	/**
	\brief Unsets the vertex buffer

	\warning The behaviour is undefined if the vertex buffer was already
	unset
	*/
	SGE_RENDERER_DETAIL_SYMBOL
	~scoped_buffer();
private:
	sge::renderer::context::core_ref const context_;

	sge::renderer::vertex::const_buffer_ref const vertex_buffer_;
};

}

#endif
