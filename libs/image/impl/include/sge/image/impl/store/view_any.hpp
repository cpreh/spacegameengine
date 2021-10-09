//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_IMPL_STORE_VIEW_ANY_HPP_INCLUDED
#define SGE_IMAGE_IMPL_STORE_VIEW_ANY_HPP_INCLUDED

#include <fcppt/reference_impl.hpp>
#include <fcppt/variant/apply.hpp>

namespace sge::image::impl::store
{

template <typename Result, typename Store>
Result view_any(fcppt::reference<Store> const _store)
{
  return fcppt::variant::apply(
      [](auto &_store_inner) { return Result(_store_inner.wrapped_view()); }, _store.get().get());
}

}

#endif
