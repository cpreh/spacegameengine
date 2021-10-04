//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_CG_PROFILE_CONVERT_SHADER_TYPE_HPP_INCLUDED
#define SGE_OPENGL_CG_PROFILE_CONVERT_SHADER_TYPE_HPP_INCLUDED

#include <sge/cg/profile/shader_type_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cgGL.h>
#include <fcppt/config/external_end.hpp>


namespace sge::opengl::cg::profile
{

CGGLenum
convert_shader_type(
	sge::cg::profile::shader_type
);

}

#endif
