//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SYSTEMS_IMPL_WINDOW_BASE_HPP_INCLUDED
#define SGE_SYSTEMS_IMPL_WINDOW_BASE_HPP_INCLUDED

#include <sge/systems/impl/window/base_fwd.hpp>
#include <sge/window/object_fwd.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::systems::impl::window
{

class base
{
  FCPPT_NONMOVABLE(base);

protected:
  base();

public:
  virtual ~base();

  [[nodiscard]] virtual sge::window::object &get() const = 0;
};

}

#endif
