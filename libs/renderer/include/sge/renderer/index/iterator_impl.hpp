//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_INDEX_ITERATOR_IMPL_HPP_INCLUDED
#define SGE_RENDERER_INDEX_ITERATOR_IMPL_HPP_INCLUDED

#include <sge/renderer/index/const_proxy_impl.hpp>
#include <sge/renderer/index/iterator_decl.hpp>
#include <sge/renderer/index/proxy_impl.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/preprocessor/ignore_unsafe_buffer_usage.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_IGNORE_UNSAFE_BUFFER_USAGE

template <typename Format, typename Constness>
sge::renderer::index::iterator<Format, Constness>::iterator(pointer const _data) : data_{_data}
{
}

template <typename Format, typename Constness>
typename sge::renderer::index::iterator<Format, Constness>::pointer
sge::renderer::index::iterator<Format, Constness>::data() const
{
  return this->data_;
}

template <typename Format, typename Constness>
sge::renderer::index::iterator<Format, Constness> &
sge::renderer::index::iterator<Format, Constness>::operator+=(difference_type const _diff)
{
  this->data_ += _diff * fcppt::cast::to_signed(sizeof(value_type));

  return *this;
}

template <typename Format, typename Constness>
void sge::renderer::index::iterator<Format, Constness>::increment()
{
  (*this) += 1;
}

template <typename Format, typename Constness>
bool sge::renderer::index::iterator<Format, Constness>::equal(iterator const &_other) const
{
  return this->data_ == _other.data_;
}

template <typename Format, typename Constness>
typename sge::renderer::index::iterator<Format, Constness>::reference
sge::renderer::index::iterator<Format, Constness>::dereference() const
{
  return reference(this->data_);
}

FCPPT_PP_POP_WARNING

#endif
