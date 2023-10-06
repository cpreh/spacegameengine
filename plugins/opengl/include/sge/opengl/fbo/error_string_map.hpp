//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_FBO_ERROR_STRING_MAP_HPP_INCLUDED
#define SGE_OPENGL_FBO_ERROR_STRING_MAP_HPP_INCLUDED

#include <sge/renderer/opengl/glinclude.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>

namespace sge::opengl::fbo
{

using error_string_map = std::map<GLenum, fcppt::string>;

}

#endif
