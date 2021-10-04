//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_STRIDE_TO_UNPACK_ALIGNMENT_HPP_INCLUDED
#define SGE_OPENGL_STRIDE_TO_UNPACK_ALIGNMENT_HPP_INCLUDED

#include <sge/image/size_type.hpp>
#include <sge/opengl/unpack_alignment.hpp>


namespace sge::opengl
{

sge::opengl::unpack_alignment
stride_to_unpack_alignment(
	sge::image::size_type stride
);

}

#endif
