//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_IMPL_INDEX_DYNAMIC_BASIC_VIEW_IMPL_HPP_INCLUDED
#define SGE_RENDERER_IMPL_INDEX_DYNAMIC_BASIC_VIEW_IMPL_HPP_INCLUDED

#include <sge/renderer/size_type.hpp>
#include <sge/renderer/index/dynamic/basic_view.hpp>
#include <sge/renderer/index/dynamic/format.hpp>

template <bool IsConst>
sge::renderer::index::dynamic::basic_view<IsConst>::basic_view(
    pointer const _data, size_type const _size, sge::renderer::index::dynamic::format const _format)
    : data_(_data), size_(_size), format_(_format)
{
}

template <bool IsConst>
typename sge::renderer::index::dynamic::basic_view<IsConst>::pointer
sge::renderer::index::dynamic::basic_view<IsConst>::data() const
{
  return data_;
}

template <bool IsConst>
sge::renderer::size_type sge::renderer::index::dynamic::basic_view<IsConst>::size() const
{
  return size_;
}

template <bool IsConst>
sge::renderer::index::dynamic::format
sge::renderer::index::dynamic::basic_view<IsConst>::format() const
{
  return format_;
}

#endif
