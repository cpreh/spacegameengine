//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/cg/loaded_program_fwd.hpp>
#include <sge/renderer/cg/scoped_program.hpp>
#include <sge/renderer/context/core.hpp>


sge::renderer::cg::scoped_program::scoped_program(
	sge::renderer::context::core &_context,
	sge::renderer::cg::loaded_program const &_program
)
:
	context_(
		_context
	),
	program_(
		_program
	)
{
	context_.set_cg_program(
		program_
	);
}

sge::renderer::cg::scoped_program::~scoped_program()
{
	context_.unset_cg_program(
		program_
	);
}
