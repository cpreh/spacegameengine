//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SCENIC_IMPL_NUMBER_MULTIPLEXER_SET_BITS_HPP_INCLUDED
#define SGE_SCENIC_IMPL_NUMBER_MULTIPLEXER_SET_BITS_HPP_INCLUDED

#include <sge/scenic/impl/number_multiplexer/begin.hpp>
#include <sge/scenic/impl/number_multiplexer/input.hpp>
#include <sge/scenic/impl/number_multiplexer/size.hpp>
#include <sge/scenic/impl/number_multiplexer/value.hpp>
#include <fcppt/strong_typedef_impl.hpp>

namespace sge::scenic::impl::number_multiplexer
{
template <typename T>
T set_bits(
    fcppt::strong_typedef<T, sge::scenic::impl::number_multiplexer::begin> const begin,
    fcppt::strong_typedef<T, sge::scenic::impl::number_multiplexer::size> const size,
    fcppt::strong_typedef<T, sge::scenic::impl::number_multiplexer::value> const value,
    fcppt::strong_typedef<T, sge::scenic::impl::number_multiplexer::input> const input)
{
  T const one{1U};

  T const part{((one << begin.get()) - one) ^ ((one << (begin.get() + size.get())) - one)};

  return (input.get() & ~part) | (value.get() << begin.get());
}
}

#endif
