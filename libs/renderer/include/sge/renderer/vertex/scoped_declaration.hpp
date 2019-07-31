//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VERTEX_SCOPED_DECLARATION_HPP_INCLUDED
#define SGE_RENDERER_VERTEX_SCOPED_DECLARATION_HPP_INCLUDED

#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{
namespace vertex
{

/**
\brief A scoped vertex declaration block

Sets a vertex declaration in the constructor and unsets it in the destructor.
*/
class scoped_declaration
{
	FCPPT_NONCOPYABLE(
		scoped_declaration
	);
public:
	/**
	\brief Sets a vertex declaration

	Sets \a vertex_declaration for \a device

	\param context The context to set the vertex declaration for

	\param vertex_declaration The vertex declaration to set
	*/
	SGE_RENDERER_DETAIL_SYMBOL
	scoped_declaration(
		sge::renderer::context::core &context,
		sge::renderer::vertex::declaration const &vertex_declaration
	);

	/**
	\brief Unsets the vertex declaration
	*/
	SGE_RENDERER_DETAIL_SYMBOL
	~scoped_declaration();
private:
	sge::renderer::context::core &context_;
};

}
}
}

#endif
