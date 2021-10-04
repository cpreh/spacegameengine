//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_CONVERT_RESOURCE_FLAGS_HPP_INCLUDED
#define SGE_OPENGL_CONVERT_RESOURCE_FLAGS_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/renderer/resource_flags_field_fwd.hpp>


namespace sge::opengl::convert
{

GLuint
resource_flags(
	sge::renderer::resource_flags_field const &
);

}

#endif
