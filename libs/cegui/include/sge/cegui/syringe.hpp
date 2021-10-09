//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CEGUI_SYRINGE_HPP_INCLUDED
#define SGE_CEGUI_SYRINGE_HPP_INCLUDED

#include <sge/cegui/syringe_fwd.hpp>
#include <sge/cegui/system_ref.hpp>
#include <sge/cegui/detail/symbol.hpp>
#include <sge/input/cursor/position_fwd.hpp>
#include <sge/input/cursor/event/button_fwd.hpp>
#include <sge/input/cursor/event/move_fwd.hpp>
#include <sge/input/cursor/event/scroll_fwd.hpp>
#include <sge/input/focus/event/key_fwd.hpp>
#include <sge/input/focus/event/key_repeat_fwd.hpp>
#include <sge/input/focus/event/text_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/log/context_reference_fwd.hpp>
#include <fcppt/log/object.hpp>

namespace CEGUI
{
class GUIContext;
}

namespace sge::cegui
{

class syringe
{
  FCPPT_NONMOVABLE(syringe);

public:
  SGE_CEGUI_DETAIL_SYMBOL
  syringe(fcppt::log::context_reference, sge::cegui::system_ref);

  SGE_CEGUI_DETAIL_SYMBOL
  ~syringe();

  SGE_CEGUI_DETAIL_SYMBOL
  void inject(sge::input::focus::event::key const &);

  SGE_CEGUI_DETAIL_SYMBOL
  void inject(sge::input::focus::event::key_repeat const &);

  SGE_CEGUI_DETAIL_SYMBOL
  void inject(sge::input::focus::event::text const &);

  SGE_CEGUI_DETAIL_SYMBOL
  void inject(sge::input::cursor::event::button const &);

  SGE_CEGUI_DETAIL_SYMBOL
  void inject(sge::input::cursor::event::move const &);

  SGE_CEGUI_DETAIL_SYMBOL
  void inject(sge::input::cursor::event::scroll const &);

  SGE_CEGUI_DETAIL_SYMBOL
  void inject(sge::input::cursor::position const &);

private:
  CEGUI::GUIContext &gui_context_;

  fcppt::log::object log_;
};

}

#endif
