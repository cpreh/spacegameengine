//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_MAKE_VERTEX_FORMAT_HPP_INCLUDED
#define SGE_SPRITE_MAKE_VERTEX_FORMAT_HPP_INCLUDED

#include <sge/renderer/vf/dynamic/format.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/sprite/vertex_format.hpp>
#include <sge/sprite/config/is_choices.hpp>

namespace sge::sprite
{

template <typename Choices>
inline sge::renderer::vf::dynamic::format make_vertex_format()
{
  static_assert(sge::sprite::config::is_choices<Choices>::value, "Choices must be a sprite choice");

  return sge::renderer::vf::dynamic::make_format<sge::sprite::vertex_format<Choices>>();
}

}

#endif
