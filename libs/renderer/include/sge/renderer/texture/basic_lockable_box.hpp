//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_TEXTURE_BASIC_LOCKABLE_BOX_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_BASIC_LOCKABLE_BOX_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/image/dim_fwd.hpp>
#include <sge/renderer/buffer/readable_fwd.hpp>
#include <sge/renderer/buffer/writable_fwd.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/texture/base.hpp>
#include <sge/renderer/texture/basic_lockable_box_fwd.hpp> // IWYU pragma: keep
#include <sge/renderer/texture/mipmap/level.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::renderer::texture
{

template <typename Tag>
class SGE_CORE_DETAIL_CLASS_SYMBOL basic_lockable_box : public sge::renderer::texture::base
{
  FCPPT_NONMOVABLE(basic_lockable_box);

protected:
  SGE_RENDERER_DETAIL_SYMBOL
  basic_lockable_box();

public:
  SGE_RENDERER_DETAIL_SYMBOL
  ~basic_lockable_box() override;

  using dim = sge::image::dim<Tag>;

  using const_buffer = sge::renderer::buffer::readable<Tag>;

  using nonconst_buffer = sge::renderer::buffer::writable<Tag>;

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL dim size() const;

  [[nodiscard]] virtual nonconst_buffer &level(sge::renderer::texture::mipmap::level) = 0;

  [[nodiscard]] virtual const_buffer const &level(sge::renderer::texture::mipmap::level) const = 0;
};

}

#endif
