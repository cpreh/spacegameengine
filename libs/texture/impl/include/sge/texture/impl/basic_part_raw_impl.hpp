//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_TEXTURE_IMPL_BASIC_PART_RAW_IMPL_HPP_INCLUDED
#define SGE_TEXTURE_IMPL_BASIC_PART_RAW_IMPL_HPP_INCLUDED

#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/texture/basic_part_raw.hpp>
#include <sge/texture/part.hpp>
#include <sge/texture/sub_data.hpp>
#include <sge/texture/impl/dereference_basic_part.hpp>
#include <fcppt/math/box/comparison.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

template <typename Ref>
sge::texture::basic_part_raw<Ref>::basic_part_raw(ref_type _texture)
    : sge::texture::part(), texture_(std::forward<ref_type>(_texture)), area_()
{
}

FCPPT_PP_POP_WARNING

template <typename Ref>
sge::texture::basic_part_raw<Ref>::basic_part_raw(
    ref_type _texture, sge::renderer::lock_rect const &_lock_rect)
    : texture_(std::forward<ref_type>(_texture)), area_(_lock_rect)
{
}

namespace sge::texture
{
template <typename Ref>
basic_part_raw<Ref>::~basic_part_raw() = default;
}

template <typename Ref>
void sge::texture::basic_part_raw<Ref>::data(
    sge::image2d::view::const_object const &_src,
    sge::image::algorithm::uninitialized const _uninitialized)
{
  sge::texture::sub_data(this->texture(), _src, this->area().pos(), _uninitialized);
}

template <typename Ref>
sge::renderer::lock_rect sge::texture::basic_part_raw<Ref>::area() const
{
  return fcppt::optional::from(
      area_,
      [this]
      {
        return sge::renderer::lock_rect{
            fcppt::math::vector::null<sge::renderer::lock_rect::vector>(), this->texture().size()};
      });
}

template <typename Ref>
sge::renderer::texture::planar &sge::texture::basic_part_raw<Ref>::texture() const
{
  return sge::texture::impl::dereference_basic_part(texture_);
}

template <typename Ref>
bool sge::texture::basic_part_raw<Ref>::repeatable() const
{
  // FIXME: Test if the areas are the same as well
  return !area_.has_value();
}

#endif
