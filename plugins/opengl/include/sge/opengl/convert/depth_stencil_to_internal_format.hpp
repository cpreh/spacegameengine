//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_CONVERT_DEPTH_STENCIL_TO_INTERNAL_FORMAT_HPP_INCLUDED
#define SGE_OPENGL_CONVERT_DEPTH_STENCIL_TO_INTERNAL_FORMAT_HPP_INCLUDED

#include <sge/image/ds/format_fwd.hpp>
#include <sge/opengl/internal_color_format.hpp>


namespace sge
{
namespace opengl
{
namespace convert
{

sge::opengl::internal_color_format
depth_stencil_to_internal_format(
	sge::image::ds::format
);

}
}
}

#endif
