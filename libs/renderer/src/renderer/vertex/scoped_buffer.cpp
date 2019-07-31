//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/context/core.hpp>
#include <sge/renderer/vertex/buffer_fwd.hpp>
#include <sge/renderer/vertex/scoped_buffer.hpp>


sge::renderer::vertex::scoped_buffer::scoped_buffer(
	sge::renderer::context::core &_context,
	sge::renderer::vertex::buffer const &_vertex_buffer
)
:
	context_(
		_context
	),
	vertex_buffer_(
		_vertex_buffer
	)
{
	context_.activate_vertex_buffer(
		_vertex_buffer
	);
}

sge::renderer::vertex::scoped_buffer::~scoped_buffer()
{
	context_.deactivate_vertex_buffer(
		vertex_buffer_
	);
}
