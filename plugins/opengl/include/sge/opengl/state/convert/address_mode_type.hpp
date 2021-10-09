//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_STATE_CONVERT_ADDRESS_MODE_TYPE_HPP_INCLUDED
#define SGE_OPENGL_STATE_CONVERT_ADDRESS_MODE_TYPE_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/renderer/state/core/sampler/address/mode_s.hpp>
#include <sge/renderer/state/core/sampler/address/mode_t.hpp>
#include <sge/renderer/state/core/sampler/address/mode_u.hpp>

namespace sge::opengl::state::convert
{

template <typename Mode>
struct address_mode_type;

template <>
struct address_mode_type<sge::renderer::state::core::sampler::address::mode_s>
{
  static GLenum get();
};

template <>
struct address_mode_type<sge::renderer::state::core::sampler::address::mode_t>
{
  static GLenum get();
};

template <>
struct address_mode_type<sge::renderer::state::core::sampler::address::mode_u>
{
  static GLenum get();
};

}

#endif
