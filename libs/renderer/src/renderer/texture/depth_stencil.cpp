//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/dim2.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/depth_stencil_buffer/surface.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/texture/base.hpp>
#include <sge/renderer/texture/depth_stencil.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>

sge::renderer::texture::depth_stencil::depth_stencil() : sge::renderer::texture::base{} {}

sge::renderer::texture::depth_stencil::~depth_stencil() = default;

sge::renderer::texture::depth_stencil::dim sge::renderer::texture::depth_stencil::size() const
{
  return this->level(sge::renderer::texture::mipmap::level(0U)).size();
}
