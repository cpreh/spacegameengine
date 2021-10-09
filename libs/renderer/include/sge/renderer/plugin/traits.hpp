//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_PLUGIN_TRAITS_HPP_INCLUDED
#define SGE_RENDERER_PLUGIN_TRAITS_HPP_INCLUDED

#include <sge/plugin/capabilities_fwd.hpp>
#include <sge/plugin/detail/address_name.hpp>
#include <sge/plugin/detail/traits.hpp>
#include <sge/renderer/core_fwd.hpp>
#include <sge/renderer/core_unique_ptr.hpp>
#include <sge/renderer/detail/symbol.hpp>

namespace sge::plugin::detail
{

template <>
struct traits<sge::renderer::core>
{
  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL static sge::plugin::detail::address_name
  plugin_loader_name();

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL static sge::plugin::capabilities plugin_type();

  using loader_function = sge::renderer::core_unique_ptr();
};

}

#endif
