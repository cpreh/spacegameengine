//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_VF_ITERATOR_IMPL_HPP_INCLUDED
#define SGE_RENDERER_VF_ITERATOR_IMPL_HPP_INCLUDED

#include <sge/renderer/vf/iterator_decl.hpp> // IWYU pragma: export
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/iterator/base_impl.hpp> // IWYU pragma: keep
#include <fcppt/preprocessor/ignore_unsafe_buffer_usage.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

template <typename Part, typename Constness>
typename sge::renderer::vf::iterator<Part, Constness>::difference_type
sge::renderer::vf::iterator<Part, Constness>::stride()
{
  return fcppt::cast::to_signed(Part::stride::value);
}

template <typename Part, typename Constness>
sge::renderer::vf::iterator<Part, Constness>::iterator(internal_pointer const _data) : data_(_data)
{
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_IGNORE_UNSAFE_BUFFER_USAGE

template <typename Part, typename Constness>
void sge::renderer::vf::iterator<Part, Constness>::increment()
{
  this->data_ += this->stride();
}

template <typename Part, typename Constness>
bool sge::renderer::vf::iterator<Part, Constness>::equal(iterator const &_other) const
{
  return this->data_ == _other.data_;
}

template <typename Part, typename Constness>
typename sge::renderer::vf::iterator<Part, Constness>::vertex_type
sge::renderer::vf::iterator<Part, Constness>::dereference() const
{
  return vertex_type(this->data_);
}

template <typename Part, typename Constness>
sge::renderer::vf::iterator<Part, Constness> &
sge::renderer::vf::iterator<Part, Constness>::operator+=(difference_type const _diff)
{
  this->data_ += this->stride() * _diff;

  return *this;
}

FCPPT_PP_POP_WARNING

#endif
