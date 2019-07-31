//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/cg/program/activate.hpp>
#include <sge/d3d9/cg/program/loaded_object.hpp>
#include <sge/renderer/cg/loaded_program.hpp>


void
sge::d3d9::cg::program::activate(
	sge::renderer::cg::loaded_program const &_program
)
{
	dynamic_cast<
		sge::d3d9::cg::program::loaded_object const &
	>(
		_program
	).activate();
}
