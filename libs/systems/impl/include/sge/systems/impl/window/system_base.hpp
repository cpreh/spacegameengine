//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SYSTEMS_IMPL_WINDOW_SYSTEM_BASE_HPP_INCLUDED
#define SGE_SYSTEMS_IMPL_WINDOW_SYSTEM_BASE_HPP_INCLUDED

#include <sge/systems/impl/window/system_base_fwd.hpp>
#include <sge/window/system_fwd.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::systems::impl::window
{

class system_base
{
  FCPPT_NONMOVABLE(system_base);

protected:
  system_base();

public:
  virtual ~system_base();

  [[nodiscard]] virtual sge::window::system &get() = 0;
};

}

#endif
