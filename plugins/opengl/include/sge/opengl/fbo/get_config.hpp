//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_FBO_GET_CONFIG_HPP_INCLUDED
#define SGE_OPENGL_FBO_GET_CONFIG_HPP_INCLUDED

#include <sge/opengl/fbo/config_fwd.hpp>
#include <sge/opengl/fbo/const_context_ref.hpp>


namespace sge::opengl::fbo
{

sge::opengl::fbo::config const &
get_config(
	sge::opengl::fbo::const_context_ref
);

}

#endif
