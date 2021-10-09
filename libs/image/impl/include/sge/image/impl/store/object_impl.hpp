//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_IMPL_STORE_OBJECT_IMPL_HPP_INCLUDED
#define SGE_IMAGE_IMPL_STORE_OBJECT_IMPL_HPP_INCLUDED

#include <sge/image/mizuiro_color_traits.hpp>
#include <sge/image/impl/view/to_static_format.hpp>
#include <sge/image/store/object.hpp>
#include <sge/image/traits/image/color_tag.hpp>
#include <sge/image/traits/pixel/format_fwd.hpp>
#include <sge/image/view/to_wrapped_type.hpp>
#include <fcppt/no_init.hpp>
#include <fcppt/enum/to_static.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <utility>
#include <fcppt/config/external_end.hpp>

template <typename Tag>
sge::image::store::object<Tag>::object(variant &&_variant) : variant_{std::move(_variant)}
{
}

template <typename Tag>
sge::image::store::object<Tag>::object(
    format const _format, dim const &_size, fcppt::no_init const &)
    : variant_{fcppt::enum_::to_static<
          sge::image::traits::pixel::format<sge::image::traits::image::color_tag<Tag>>>(
          _format,
          [&_size](auto const &_static_format)
          {
            return variant{sge::image::store::basic<sge::image::impl::view::to_static_format<
                Tag,
                typename std::decay<decltype(_static_format)>::type>>(_size, fcppt::no_init{})};
          })}
{
}

template <typename Tag>
sge::image::store::object<Tag>::object(object &&) noexcept = default;

template <typename Tag>
sge::image::store::object<Tag> &
sge::image::store::object<Tag>::operator=(object &&) noexcept = default;

namespace sge::image::store
{
template <typename Tag>
object<Tag>::~object() = default;
}

template <typename Tag>
typename sge::image::store::object<Tag>::variant &sge::image::store::object<Tag>::get()
{
  return variant_;
}

template <typename Tag>
typename sge::image::store::object<Tag>::variant const &sge::image::store::object<Tag>::get() const
{
  return variant_;
}

#endif
