//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PLUGIN_IMPL_INSTANTIATE_COLLECTION_HPP_INCLUDED
#define SGE_PLUGIN_IMPL_INSTANTIATE_COLLECTION_HPP_INCLUDED

#include <sge/plugin/impl/collection_impl.hpp> // IWYU pragma: keep

#define SGE_PLUGIN_IMPL_INSTANTIATE_COLLECTION(plugin_type) \
  template class sge::plugin::collection<plugin_type>

#endif
