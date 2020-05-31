//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/context/core_ref.hpp>
#include <sge/renderer/vertex/const_buffer_ref.hpp>
#include <sge/renderer/vertex/const_buffer_ref_container.hpp>
#include <sge/renderer/vertex/const_declaration_ref.hpp>
#include <sge/renderer/vertex/scoped_buffer.hpp>
#include <sge/renderer/vertex/scoped_declaration_and_buffers.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/algorithm/map.hpp>


sge::renderer::vertex::scoped_declaration_and_buffers::scoped_declaration_and_buffers(
	sge::renderer::context::core_ref const _context,
	sge::renderer::vertex::const_declaration_ref const _vertex_declaration,
	sge::renderer::vertex::const_buffer_ref_container const &_vertex_buffers
)
:
	scoped_declaration_(
		_context,
		_vertex_declaration
	),
	scoped_buffers_(
		fcppt::algorithm::map<
			scoped_buffer_vector
		>(
			_vertex_buffers,
			[
				&_context
			](
				sge::renderer::vertex::const_buffer_ref const _ref
			)
			{
				return
					fcppt::make_unique_ptr<
						sge::renderer::vertex::scoped_buffer
					>(
						_context,
						_ref
					);
			}
		)
	)
{
}

sge::renderer::vertex::scoped_declaration_and_buffers::~scoped_declaration_and_buffers()
= default;
