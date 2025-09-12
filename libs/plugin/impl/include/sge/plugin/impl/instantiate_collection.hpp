//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PLUGIN_IMPL_INSTANTIATE_COLLECTION_HPP_INCLUDED
#define SGE_PLUGIN_IMPL_INSTANTIATE_COLLECTION_HPP_INCLUDED

#include <sge/plugin/impl/collection_impl.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <ranges> // IWYU pragma: keep
#include <fcppt/config/external_end.hpp>

#define SGE_PLUGIN_IMPL_INSTANTIATE_COLLECTION(plugin_type) \
  template class sge::plugin::collection<plugin_type>; \
  static_assert(std::ranges::input_range<sge::plugin::collection<plugin_type>>)

#endif
