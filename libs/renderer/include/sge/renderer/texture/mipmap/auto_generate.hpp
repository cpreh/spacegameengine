//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_TEXTURE_MIPMAP_AUTO_GENERATE_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_MIPMAP_AUTO_GENERATE_HPP_INCLUDED

#include <sge/renderer/texture/mipmap/auto_generate_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sge::renderer::texture::mipmap
{

enum class auto_generate : std::uint8_t
{
  yes,
  no
};

}

#endif
