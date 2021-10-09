//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_IMPL_VF_DYNAMIC_BASIC_VIEW_IMPL_HPP_INCLUDED
#define SGE_RENDERER_IMPL_VF_DYNAMIC_BASIC_VIEW_IMPL_HPP_INCLUDED

#include <sge/renderer/vf/dynamic/basic_view.hpp>
#include <sge/renderer/vf/dynamic/const_part_ref.hpp>
#include <sge/renderer/vf/dynamic/part_fwd.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>

template <typename Pointer>
sge::renderer::vf::dynamic::basic_view<Pointer>::basic_view(
    pointer const _data,
    size_type const _size,
    sge::renderer::vf::dynamic::const_part_ref const _part,
    sge::renderer::vf::dynamic::part_index const _part_index)
    : data_(_data), size_(_size), part_(_part), part_index_(_part_index)
{
}

template <typename Pointer>
typename sge::renderer::vf::dynamic::basic_view<Pointer>::pointer
sge::renderer::vf::dynamic::basic_view<Pointer>::data() const
{
  return data_;
}

template <typename Pointer>
typename sge::renderer::vf::dynamic::basic_view<Pointer>::size_type
sge::renderer::vf::dynamic::basic_view<Pointer>::size() const
{
  return size_;
}

template <typename Pointer>
sge::renderer::vf::dynamic::part const &
sge::renderer::vf::dynamic::basic_view<Pointer>::part() const
{
  return part_.get();
}

template <typename Pointer>
sge::renderer::vf::dynamic::part_index
sge::renderer::vf::dynamic::basic_view<Pointer>::part_index() const
{
  return part_index_;
}

#endif
