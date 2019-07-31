//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cg/string.hpp>
#include <sge/cg/program/extra_index.hpp>
#include <sge/opengl/cg/program/replace_index.hpp>
#include <sge/opengl/vf/extra_index.hpp>
#include <sge/renderer/vf/dynamic/index.hpp>
#include <fcppt/output_to_string.hpp>


sge::cg::string
sge::opengl::cg::program::replace_index(
	sge::cg::program::extra_index const _index
)
{
	return
		"ATTR"
		+
		fcppt::output_to_string<
			sge::cg::string
		>(
			sge::opengl::vf::extra_index(
				sge::renderer::vf::dynamic::index(
					_index.get()
				)
			)
		)
		;
}
