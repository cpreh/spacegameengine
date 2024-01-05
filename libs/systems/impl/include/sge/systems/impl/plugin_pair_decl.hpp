//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SYSTEMS_IMPL_PLUGIN_PAIR_DECL_HPP_INCLUDED
#define SGE_SYSTEMS_IMPL_PLUGIN_PAIR_DECL_HPP_INCLUDED

#include <sge/plugin/object.hpp>
#include <sge/systems/impl/plugin_pair_fwd.hpp> // IWYU pragma: keep
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>

namespace sge::systems::impl
{

template <typename System>
class plugin_pair
{
  FCPPT_NONCOPYABLE(plugin_pair);

public:
  using plugin = sge::plugin::object<System>;

  using system_unique_ptr = fcppt::unique_ptr<System>;

  plugin_pair(plugin &&, system_unique_ptr &&);

  plugin_pair(plugin_pair &&) noexcept;

  plugin_pair &operator=(plugin_pair &&) noexcept;

  ~plugin_pair();

  [[nodiscard]] System &system() const;

private:
  plugin plugin_;

  system_unique_ptr system_;
};

}

#endif
