//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_TEXTURE_CAPABILITIES_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_CAPABILITIES_HPP_INCLUDED

#include <sge/renderer/texture/capabilities_fwd.hpp> // IWYU pragma: keep
#include <fcppt/enum/define_max_value.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sge::renderer::texture
{

enum class capabilities : std::uint8_t
{
  render_target
};

}

FCPPT_ENUM_DEFINE_MAX_VALUE(sge::renderer::texture::capabilities::render_target);

#endif
