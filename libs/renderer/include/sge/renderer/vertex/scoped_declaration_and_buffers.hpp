//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_VERTEX_SCOPED_DECLARATION_AND_BUFFERS_HPP_INCLUDED
#define SGE_RENDERER_VERTEX_SCOPED_DECLARATION_AND_BUFFERS_HPP_INCLUDED

#include <sge/renderer/context/core_ref.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/vertex/const_buffer_ref_container.hpp>
#include <sge/renderer/vertex/const_declaration_ref.hpp>
#include <sge/renderer/vertex/scoped_buffer_fwd.hpp>
#include <sge/renderer/vertex/scoped_declaration.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace sge::renderer::vertex
{

/**
\brief A scoped vertex declaration and buffers block

Sets a vertex declaration following by one or multiple vertexbuffers in the
constructor and unsets them in the reverse order in the destructor.
*/
class scoped_declaration_and_buffers
{
  FCPPT_NONMOVABLE(scoped_declaration_and_buffers);

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
  SGE_RENDERER_DETAIL_SYMBOL
  scoped_declaration_and_buffers(
      sge::renderer::context::core_ref context,
      sge::renderer::vertex::const_declaration_ref vertex_declaration,
      sge::renderer::vertex::const_buffer_ref_container const &vertex_buffers);

  /**
	\brief Unsets the vertex buffers following by the vertex declaration
	*/
  SGE_RENDERER_DETAIL_SYMBOL
  ~scoped_declaration_and_buffers();

private:
  sge::renderer::vertex::scoped_declaration const scoped_declaration_;

  using scoped_buffer_ptr = fcppt::unique_ptr<sge::renderer::vertex::scoped_buffer>;

  using scoped_buffer_vector = std::vector<scoped_buffer_ptr>;

  scoped_buffer_vector const scoped_buffers_;
};

}

#endif
