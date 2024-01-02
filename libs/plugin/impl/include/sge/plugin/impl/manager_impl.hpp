//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PLUGIN_IMPL_MANAGER_IMPL_HPP_INCLUDED
#define SGE_PLUGIN_IMPL_MANAGER_IMPL_HPP_INCLUDED

#include <sge/plugin/collection.hpp>
#include <sge/plugin/manager.hpp>
#include <sge/plugin/detail/traits.hpp>
#include <fcppt/enum/array_impl.hpp> // IWYU pragma: keep

template <typename Type>
sge::plugin::collection<Type> sge::plugin::manager::collection()
{
  return sge::plugin::collection<Type>(
      categories_[sge::plugin::detail::traits<Type>::plugin_type()]);
}

#endif
