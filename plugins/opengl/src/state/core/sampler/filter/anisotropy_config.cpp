//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/state/core/sampler/filter/anisotropy_config.hpp>
#include <sge/renderer/opengl/glinclude.hpp>

sge::opengl::state::core::sampler::filter::anisotropy_config::anisotropy_config(
    GLenum const _anisotropy_flag, GLenum const _max_anisotropy_flag)
    : anisotropy_flag_(_anisotropy_flag), max_anisotropy_flag_(_max_anisotropy_flag)
{
}

GLenum sge::opengl::state::core::sampler::filter::anisotropy_config::anisotropy_flag() const
{
  return anisotropy_flag_;
}

GLenum sge::opengl::state::core::sampler::filter::anisotropy_config::max_anisotropy_flag() const
{
  return max_anisotropy_flag_;
}
