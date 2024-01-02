//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_INPUT_IMPL_INFO_INSTANTIATE_CONTAINER_HPP_INCLUDED
#define SGE_INPUT_IMPL_INFO_INSTANTIATE_CONTAINER_HPP_INCLUDED

#include <sge/core/impl/export_class_instantiation.hpp>
#include <sge/input/impl/info/container_impl.hpp> // IWYU pragma: keep

#define SGE_INPUT_IMPL_INFO_INSTANTIATE_CONTAINER(id_type, info_type) \
  template class SGE_CORE_IMPL_EXPORT_CLASS_INSTANTIATION \
      sge::input::info::container<id_type, info_type>

#endif
