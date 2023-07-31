//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_VF_PROXY_IMPL_HPP_INCLUDED
#define SGE_RENDERER_VF_PROXY_IMPL_HPP_INCLUDED

#include <sge/renderer/vf/proxy_decl.hpp>
#include <sge/renderer/vf/to_packed_type.hpp>
#include <sge/renderer/vf/detail/copy_n.hpp>
#include <sge/renderer/vf/detail/element_index.hpp>
#include <sge/renderer/vf/detail/element_stride.hpp>
#include <sge/renderer/vf/detail/raw_data.hpp>
#include <sge/renderer/vf/detail/read_wrapper_impl.hpp>
#include <fcppt/tag_type.hpp>
#include <fcppt/use.hpp>
#include <fcppt/algorithm/loop.hpp>
#include <fcppt/algorithm/loop_break_mpl.hpp>
#include <fcppt/mpl/list/at.hpp>
#include <fcppt/mpl/set/to_list.hpp>
#include <fcppt/preprocessor/ignore_unsafe_buffer_usage.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/record/label_set.hpp>

template <typename Part, typename Constness>
sge::renderer::vf::proxy<Part, Constness>::proxy(pointer const _data) : data_{_data}
{
}

template <typename Part, typename Constness>
sge::renderer::vf::proxy<Part, Constness> &
sge::renderer::vf::proxy<Part, Constness>::operator=(vertex_type const &_value)
{
  fcppt::algorithm::loop(
      fcppt::mpl::set::to_list<fcppt::record::label_set<typename vertex_type::record_type>>{},
      [&_value, this](auto const &_label_tag)
      {
        FCPPT_USE(_label_tag);

        using label = fcppt::tag_type<decltype(_label_tag)>;

        this->template set<label>(_value.template get<label>());
      });

  return *this;
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_IGNORE_UNSAFE_BUFFER_USAGE

template <typename Part, typename Constness>
template <typename Label>
void sge::renderer::vf::proxy<Part, Constness>::set(
    sge::renderer::vf::label_value_type<Part, Label> const &_value)
{
  using index = sge::renderer::vf::detail::element_index<elements, Label>;

  using element = fcppt::mpl::list::at<elements, index>;

  using offset = fcppt::mpl::list::at<offsets, index>;

  sge::renderer::vf::detail::copy_n(
      sge::renderer::vf::detail::raw_data(_value),
      sge::renderer::vf::detail::element_stride<element>::value,
      this->data_ + offset::value);
}

template <typename Part, typename Constness>
template <typename Label>
sge::renderer::vf::label_value_type<Part, Label>
sge::renderer::vf::proxy<Part, Constness>::get() const
{
  using index = sge::renderer::vf::detail::element_index<elements, Label>;

  using element = fcppt::mpl::list::at<elements, index>;

  using offset = fcppt::mpl::list::at<offsets, index>;

  using packed_type = sge::renderer::vf::to_packed_type<element>;

  sge::renderer::vf::detail::read_wrapper<packed_type> ret{};

  sge::renderer::vf::detail::copy_n(
      this->data_ + offset::value,
      sge::renderer::vf::detail::element_stride<element>::value,
      sge::renderer::vf::detail::raw_data(ret.get()));

  return ret.get();
}

FCPPT_PP_POP_WARNING

#endif
