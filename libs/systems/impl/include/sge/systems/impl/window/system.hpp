//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SYSTEMS_IMPL_WINDOW_SYSTEM_HPP_INCLUDED
#define SGE_SYSTEMS_IMPL_WINDOW_SYSTEM_HPP_INCLUDED

#include <sge/systems/window_fwd.hpp>
#include <sge/systems/impl/window/system_base_unique_ptr.hpp>
#include <sge/systems/impl/window/system_fwd.hpp>
#include <sge/window/system_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/log/context_reference_fwd.hpp>

namespace sge::systems::impl::window
{

class system
{
  FCPPT_NONMOVABLE(system);

public:
  system(fcppt::log::context_reference, sge::systems::window const &);

  ~system();

  [[nodiscard]] sge::window::system &get() const;

private:
  sge::systems::impl::window::system_base_unique_ptr const base_;
};

}

#endif
