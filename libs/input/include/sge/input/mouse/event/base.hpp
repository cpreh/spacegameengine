//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_INPUT_MOUSE_EVENT_BASE_HPP_INCLUDED
#define SGE_INPUT_MOUSE_EVENT_BASE_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/input/event_base.hpp>
#include <sge/input/detail/symbol.hpp>
#include <sge/input/mouse/shared_ptr.hpp>
#include <sge/input/mouse/event/base_fwd.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::input::mouse::event
{

class SGE_CORE_DETAIL_CLASS_SYMBOL base : public sge::input::event_base
{
  FCPPT_NONMOVABLE(base);

public:
  SGE_INPUT_DETAIL_SYMBOL
  explicit base(sge::input::mouse::shared_ptr);

  SGE_INPUT_DETAIL_SYMBOL
  ~base() override;

  [[nodiscard]] SGE_INPUT_DETAIL_SYMBOL sge::input::mouse::shared_ptr const &mouse() const;

private:
  sge::input::mouse::shared_ptr const mouse_;
};

}

#endif
