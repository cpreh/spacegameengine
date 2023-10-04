//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SYSTEMS_IMPL_PLUGIN_PAIR_IMPL_HPP_INCLUDED
#define SGE_SYSTEMS_IMPL_PLUGIN_PAIR_IMPL_HPP_INCLUDED

#include <sge/systems/impl/plugin_pair_decl.hpp> // IWYU pragma: export
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

template <typename System>
sge::systems::impl::plugin_pair<System>::plugin_pair(plugin &&_plugin, system_unique_ptr &&_system)
    : plugin_(std::move(_plugin)), system_(std::move(_system))
{
}

template <typename System>
sge::systems::impl::plugin_pair<System>::plugin_pair(plugin_pair &&) noexcept = default;

template <typename System>
sge::systems::impl::plugin_pair<System> &
sge::systems::impl::plugin_pair<System>::operator=(plugin_pair &&) noexcept = default;

namespace sge::systems::impl
{
template <typename System>
plugin_pair<System>::~plugin_pair() = default;
}

template <typename System>
System &sge::systems::impl::plugin_pair<System>::system() const
{
  return *system_;
}

#endif
