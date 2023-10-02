//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_COLOR_IMPL_DYNAMIC_FORMAT_OBJECT_IMPL_HPP_INCLUDED
#define SGE_IMAGE_COLOR_IMPL_DYNAMIC_FORMAT_OBJECT_IMPL_HPP_INCLUDED

#include <sge/image/color/impl/dynamic/format/object_base_impl.hpp>
#include <sge/image/color/impl/dynamic/format/object_decl.hpp> // IWYU pragma: export
#include <mizuiro/size_type.hpp>

template <typename Space, typename BaseType, mizuiro::size_type NumChannels>
template <typename Layout>
sge::image::color::impl::dynamic::format::object<Space, BaseType, NumChannels>::object(
    Layout const &_layout, color_format_type const _color_format) noexcept
    : base(_layout), color_format(_color_format)
{
}

namespace sge::image::color::impl::dynamic::format
{
template <typename Space, typename BaseType, mizuiro::size_type NumChannels>
object<Space, BaseType, NumChannels>::~object() = default;
}

#endif
