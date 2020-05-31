//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/context/core.hpp>
#include <sge/renderer/context/core_ref.hpp>
#include <sge/renderer/vertex/const_optional_declaration_ref.hpp>
#include <sge/renderer/vertex/const_declaration_ref.hpp>
#include <sge/renderer/vertex/scoped_declaration.hpp>


sge::renderer::vertex::scoped_declaration::scoped_declaration(
	sge::renderer::context::core_ref const _context,
	sge::renderer::vertex::const_declaration_ref const _declaration
)
:
	context_(
		_context
	)
{
	context_.get().vertex_declaration(
		sge::renderer::vertex::const_optional_declaration_ref(
			_declaration
		)
	);
}

sge::renderer::vertex::scoped_declaration::~scoped_declaration()
{
	context_.get().vertex_declaration(
		sge::renderer::vertex::const_optional_declaration_ref()
	);
}
