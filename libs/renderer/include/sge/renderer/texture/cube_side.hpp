//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_TEXTURE_CUBE_SIDE_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_CUBE_SIDE_HPP_INCLUDED

#include <sge/renderer/texture/cube_side_fwd.hpp> // IWYU pragma: keep
#include <fcppt/enum/define_max_value.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sge::renderer::texture
{

enum class cube_side : std::uint8_t
{
  front,
  back,
  left,
  right,
  top,
  bottom
};

}

FCPPT_ENUM_DEFINE_MAX_VALUE(sge::renderer::texture::cube_side::bottom);

#endif
