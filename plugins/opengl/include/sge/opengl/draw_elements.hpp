//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_DRAW_ELEMENTS_HPP_INCLUDED
#define SGE_OPENGL_DRAW_ELEMENTS_HPP_INCLUDED

#include <sge/opengl/context/object_fwd.hpp>
#include <sge/renderer/primitive_type_fwd.hpp>
#include <sge/renderer/index/buffer_fwd.hpp>
#include <sge/renderer/index/count.hpp>
#include <sge/renderer/index/first.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <fcppt/log/object_fwd.hpp>


namespace sge::opengl
{

void
draw_elements(
	fcppt::log::object &, // NOLINT(google-runtime-references)
	sge::opengl::context::object &, // NOLINT(google-runtime-references)
	sge::renderer::index::buffer const &,
	sge::renderer::vertex::first,
	sge::renderer::vertex::count,
	sge::renderer::primitive_type,
	sge::renderer::index::first,
	sge::renderer::index::count
);

}

#endif
