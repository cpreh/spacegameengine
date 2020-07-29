//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cg/program/object_ref.hpp>
#include <sge/opengl/cg/program/load.hpp>
#include <sge/opengl/cg/program/loaded_object.hpp>
#include <sge/renderer/cg/loaded_program.hpp>
#include <sge/renderer/cg/loaded_program_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


sge::renderer::cg::loaded_program_unique_ptr
sge::opengl::cg::program::load(
	sge::cg::program::object_ref const _program
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::renderer::cg::loaded_program
		>(
			fcppt::make_unique_ptr<
				sge::opengl::cg::program::loaded_object
			>(
				_program
			)
		);
}
