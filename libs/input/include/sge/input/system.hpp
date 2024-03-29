//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_INPUT_SYSTEM_HPP_INCLUDED
#define SGE_INPUT_SYSTEM_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/input/capabilities_field_fwd.hpp>
#include <sge/input/processor_unique_ptr.hpp>
#include <sge/input/system_fwd.hpp> // IWYU pragma: keep
#include <sge/input/detail/symbol.hpp>
#include <sge/window/object_ref.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::input
{

class SGE_CORE_DETAIL_CLASS_SYMBOL system
{
  FCPPT_NONMOVABLE(system);

protected:
  SGE_INPUT_DETAIL_SYMBOL
  system();

public:
  SGE_INPUT_DETAIL_SYMBOL
  virtual ~system();

  [[nodiscard]] virtual sge::input::processor_unique_ptr
      create_processor(sge::window::object_ref) = 0;

  [[nodiscard]] virtual sge::input::capabilities_field capabilities() const = 0;
};

}

#endif
