//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_DRAW_ARRAYS_HPP_INCLUDED
#define SGE_OPENGL_DRAW_ARRAYS_HPP_INCLUDED

#include <sge/renderer/primitive_type_fwd.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <fcppt/log/object_fwd.hpp>


namespace sge
{
namespace opengl
{

void
draw_arrays(
	fcppt::log::object &,
	sge::renderer::vertex::first,
	sge::renderer::vertex::count,
	sge::renderer::primitive_type
);

}
}

#endif
