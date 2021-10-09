//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CEGUI_TOOLBOX_SCOPED_GUI_SHEET_HPP_INCLUDED
#define SGE_CEGUI_TOOLBOX_SCOPED_GUI_SHEET_HPP_INCLUDED

#include <sge/cegui/system_ref.hpp>
#include <sge/cegui/detail/symbol.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/reference_fwd.hpp>

namespace CEGUI
{
class Window;
}

namespace sge::cegui::toolbox
{

class scoped_gui_sheet
{
  FCPPT_NONMOVABLE(scoped_gui_sheet);

public:
  SGE_CEGUI_DETAIL_SYMBOL
  scoped_gui_sheet(sge::cegui::system_ref, fcppt::reference<CEGUI::Window>);

  SGE_CEGUI_DETAIL_SYMBOL
  ~scoped_gui_sheet();

private:
  sge::cegui::system_ref const system_;
};

}

#endif
