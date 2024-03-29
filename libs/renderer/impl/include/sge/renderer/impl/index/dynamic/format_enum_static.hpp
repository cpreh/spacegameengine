//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_IMPL_INDEX_DYNAMIC_FORMAT_ENUM_STATIC_HPP_INCLUDED
#define SGE_RENDERER_IMPL_INDEX_DYNAMIC_FORMAT_ENUM_STATIC_HPP_INCLUDED

#include <sge/renderer/index/format_is_16.hpp>
#include <sge/renderer/index/format_is_32.hpp>
#include <sge/renderer/index/dynamic/format.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::renderer::impl::index::dynamic
{

template <typename Format, typename Enable = void>
struct format_enum_static;

template <typename Format>
struct format_enum_static<
    Format,
    std::enable_if_t<sge::renderer::index::format_is_16<Format>::value>>
    : std::integral_constant<
          sge::renderer::index::dynamic::format,
          sge::renderer::index::dynamic::format::i16>
{
};

template <typename Format>
struct format_enum_static<
    Format,
    std::enable_if_t<sge::renderer::index::format_is_32<Format>::value>>
    : std::integral_constant<
          sge::renderer::index::dynamic::format,
          sge::renderer::index::dynamic::format::i32>
{
};

}

#endif
