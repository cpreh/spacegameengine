//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_VF_VIEW_IMPL_HPP_INCLUDED
#define SGE_RENDERER_VF_VIEW_IMPL_HPP_INCLUDED

#include <sge/renderer/vf/iterator_impl.hpp> // IWYU pragma: keep
#include <sge/renderer/vf/view_decl.hpp> // IWYU pragma: export
#include <sge/renderer/vf/dynamic/basic_view.hpp>
#include <fcppt/preprocessor/ignore_unsafe_buffer_usage.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

template <typename Part, typename Constness>
sge::renderer::vf::view<Part, Constness>::view(dynamic_view_type const &_view)
    : data_(_view.data()), size_(_view.size())
{
}

template <typename Part, typename Constness>
template <typename OtherView>
sge::renderer::vf::view<Part, Constness>::view(
    sge::renderer::vf::dynamic::basic_view<OtherView> const &_view)
    : data_(_view.data()), size_(_view.size())
{
}

template <typename Part, typename Constness>
typename sge::renderer::vf::view<Part, Constness>::iterator
sge::renderer::vf::view<Part, Constness>::begin() const
{
  return iterator(data_);
}

template <typename Part, typename Constness>
typename sge::renderer::vf::view<Part, Constness>::iterator
sge::renderer::vf::view<Part, Constness>::end() const
{
FCPPT_PP_PUSH_WARNING
FCPPT_PP_IGNORE_UNSAFE_BUFFER_USAGE

  return iterator(data_ + size_.get());

FCPPT_PP_POP_WARNING
}

#endif
