//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_TEXTURE_CUBE_BASIC_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_CUBE_BASIC_HPP_INCLUDED

#include <sge/opengl/texture/basic.hpp>
#include <sge/opengl/texture/cube_basic_fwd.hpp> // IWYU pragma: export
#include <sge/opengl/texture/cube_types.hpp>
#include <sge/renderer/texture/cube.hpp> // IWYU pragma: keep
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wweak-template-vtables)

extern template class sge::opengl::texture::basic<sge::opengl::texture::cube_types>;

FCPPT_PP_POP_WARNING

#endif
