//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_TEXTURE_MIPMAP_OBJECT_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_MIPMAP_OBJECT_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/texture/mipmap/object_fwd.hpp> // IWYU pragma: keep
#include <sge/renderer/texture/mipmap/variant.hpp>

namespace sge::renderer::texture::mipmap
{

class object
{
public:
  SGE_RENDERER_DETAIL_SYMBOL
  explicit object(sge::renderer::texture::mipmap::variant const &);

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL sge::renderer::texture::mipmap::variant const &
  variant() const;

private:
  sge::renderer::texture::mipmap::variant variant_;
};

}

#endif
