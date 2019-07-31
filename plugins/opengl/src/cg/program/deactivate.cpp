//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/cg/program/deactivate.hpp>
#include <sge/opengl/cg/program/loaded_object.hpp>
#include <sge/renderer/cg/loaded_program_fwd.hpp>

void
sge::opengl::cg::program::deactivate(
	sge::renderer::cg::loaded_program const &_program
)
{
	dynamic_cast<
		sge::opengl::cg::program::loaded_object const &
	>(
		_program
	).deactivate();
}
