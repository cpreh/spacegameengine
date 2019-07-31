//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_CONVERT_INTERNAL_FORMAT_FUNCTION_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_CONVERT_INTERNAL_FORMAT_FUNCTION_HPP_INCLUDED

#include <sge/opengl/internal_color_format.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

template<
	typename Format
>
using convert_internal_format_function
=
sge::opengl::internal_color_format
(&)
(
	Format
);

}
}
}

#endif
