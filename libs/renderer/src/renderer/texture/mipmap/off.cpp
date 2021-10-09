//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/texture/mipmap/object.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/renderer/texture/mipmap/off_rep.hpp>
#include <sge/renderer/texture/mipmap/variant.hpp>

sge::renderer::texture::mipmap::object sge::renderer::texture::mipmap::off()
{
  return sge::renderer::texture::mipmap::object(
      sge::renderer::texture::mipmap::variant{sge::renderer::texture::mipmap::off_rep()});
}
