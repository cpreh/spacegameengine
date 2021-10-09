//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/texture/mipmap/auto_generate.hpp>
#include <sge/renderer/texture/mipmap/level_count.hpp>
#include <sge/renderer/texture/mipmap/levels_rep.hpp>

sge::renderer::texture::mipmap::levels_rep::levels_rep(
    sge::renderer::texture::mipmap::level_count const _value,
    sge::renderer::texture::mipmap::auto_generate const _auto_generate)
    : value_(_value), auto_generate_(_auto_generate)
{
}

sge::renderer::texture::mipmap::level_count
sge::renderer::texture::mipmap::levels_rep::value() const
{
  return value_;
}

sge::renderer::texture::mipmap::auto_generate
sge::renderer::texture::mipmap::levels_rep::auto_generate() const
{
  return auto_generate_;
}
