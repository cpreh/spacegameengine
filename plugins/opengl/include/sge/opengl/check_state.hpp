//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_CHECK_STATE_HPP_INCLUDED
#define SGE_OPENGL_CHECK_STATE_HPP_INCLUDED

#include <sge/core/check_state.hpp>
#include <sge/opengl/check_state_always.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/error_string.hpp>


#if defined(SGE_OPENGL_CHECK_STATE_ALWAYS)
#define SGE_OPENGL_CHECK_STATE(\
	message,\
	exception\
)\
SGE_CORE_CHECK_STATE(\
	exception,\
	message,\
	GLenum,\
	::glGetError(),\
	GL_NO_ERROR,\
	sge::opengl::error_string\
)
#else
#define SGE_OPENGL_CHECK_STATE(\
	message,\
	exception\
)
#endif

#endif
