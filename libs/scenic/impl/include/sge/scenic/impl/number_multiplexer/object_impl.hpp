//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SCENIC_IMPL_NUMBER_MULTIPLEXER_OBJECT_IMPL_HPP_INCLUDED
#define SGE_SCENIC_IMPL_NUMBER_MULTIPLEXER_OBJECT_IMPL_HPP_INCLUDED

#include <sge/scenic/impl/number_multiplexer/object_decl.hpp> // IWYU pragma: export
#include <sge/scenic/impl/number_multiplexer/set_bits.hpp>
#include <fcppt/literal.hpp>

template <typename T>
sge::scenic::impl::number_multiplexer::object<T>::object()
    : value_(fcppt::literal<value_type>(0)), last_bit_set_(fcppt::literal<value_type>(0))
{
}

template <typename T>
sge::scenic::impl::number_multiplexer::object<T>::object(value_type const _value)
    : value_(_value), last_bit_set_(fcppt::literal<value_type>(0))
{
}

template <typename T>
sge::scenic::impl::number_multiplexer::object<T> &
sge::scenic::impl::number_multiplexer::object<T>::append(
    bit_count const &_bit_count, value_type const _value)
{
  value_ = sge::scenic::impl::number_multiplexer::set_bits(
      last_bit_set_, _bit_count.get(), _value, value_);

  last_bit_set_ += _bit_count.get();

  return *this;
}

template <typename T>
typename sge::scenic::impl::number_multiplexer::object<T>::value_type
sge::scenic::impl::number_multiplexer::object<T>::value() const
{
  return value_;
}

#endif
