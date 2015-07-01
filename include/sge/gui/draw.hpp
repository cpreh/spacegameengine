#ifndef SGE_GUI_DRAW_HPP_INCLUDED
#define SGE_GUI_DRAW_HPP_INCLUDED

#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/background/base_fwd.hpp>
#include <sge/gui/main_area/base_fwd.hpp>
#include <sge/gui/renderer/base_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>


namespace sge
{
namespace gui
{

SGE_GUI_DETAIL_SYMBOL
void
draw(
	sge::gui::renderer::base &,
	sge::renderer::context::ffp &,
	sge::gui::background::base &,
	sge::gui::main_area::base &
);

}
}

#endif
