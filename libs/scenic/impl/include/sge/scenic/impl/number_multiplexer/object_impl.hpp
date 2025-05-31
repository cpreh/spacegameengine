//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SCENIC_IMPL_NUMBER_MULTIPLEXER_OBJECT_IMPL_HPP_INCLUDED
#define SGE_SCENIC_IMPL_NUMBER_MULTIPLEXER_OBJECT_IMPL_HPP_INCLUDED

#include <sge/scenic/impl/number_multiplexer/begin.hpp>
#include <sge/scenic/impl/number_multiplexer/input.hpp>
#include <sge/scenic/impl/number_multiplexer/object_decl.hpp> // IWYU pragma: export
#include <sge/scenic/impl/number_multiplexer/set_bits.hpp>
#include <sge/scenic/impl/number_multiplexer/size.hpp>
#include <sge/scenic/impl/number_multiplexer/value.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_strong_typedef.hpp>

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
      fcppt::make_strong_typedef<sge::scenic::impl::number_multiplexer::begin>(last_bit_set_),
      fcppt::make_strong_typedef<sge::scenic::impl::number_multiplexer::size>(_bit_count.get()),
      fcppt::make_strong_typedef<sge::scenic::impl::number_multiplexer::value>(_value),
      fcppt::make_strong_typedef<sge::scenic::impl::number_multiplexer::input>(value_));

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
