//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_TEXTURE_FORMAT_RESULT_IMPL_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_FORMAT_RESULT_IMPL_HPP_INCLUDED

#include <sge/opengl/texture/format_result_decl.hpp> // IWYU pragma: export

template <typename SGEFormat, typename GLFormat>
sge::opengl::texture::format_result<SGEFormat, GLFormat>::format_result(
    SGEFormat const _sge_format, GLFormat const _gl_format)
    : sge_format_{_sge_format}, gl_format_{_gl_format}
{
}

template <typename SGEFormat, typename GLFormat>
SGEFormat sge::opengl::texture::format_result<SGEFormat, GLFormat>::sge_format() const
{
  return sge_format_;
}

template <typename SGEFormat, typename GLFormat>
GLFormat sge::opengl::texture::format_result<SGEFormat, GLFormat>::gl_format() const
{
  return gl_format_;
}

#endif
