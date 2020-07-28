//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_SET_UNPACK_ALIGNMENT_HPP_INCLUDED
#define SGE_OPENGL_SET_UNPACK_ALIGNMENT_HPP_INCLUDED

#include <sge/opengl/unpack_alignment.hpp>
#include <sge/opengl/context/object_fwd.hpp>


namespace sge
{
namespace opengl
{

void
set_unpack_alignment(
	sge::opengl::context::object &, // NOLINT(google-runtime-references)
	sge::opengl::unpack_alignment
);

}
}

#endif
