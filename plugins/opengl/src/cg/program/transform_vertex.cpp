//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cg/program/replace_extra.hpp>
#include <sge/cg/program/replace_extra_callback.hpp>
#include <sge/cg/program/source.hpp>
#include <sge/opengl/cg/program/replace_index.hpp>
#include <sge/opengl/cg/program/transform_vertex.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>


sge::cg::program::source
sge::opengl::cg::program::transform_vertex(
	sge::renderer::vertex::declaration const &,
	sge::cg::program::source const &_source
)
{
	return
		sge::cg::program::replace_extra(
			_source,
			sge::cg::program::replace_extra_callback(
				sge::opengl::cg::program::replace_index
			)
		);
}
