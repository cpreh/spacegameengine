#ifndef SGE_GUI_STYLE_CREATE_HPP_INCLUDED
#define SGE_GUI_STYLE_CREATE_HPP_INCLUDED

#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/style/base_unique_ptr.hpp>


namespace sge
{
namespace gui
{
namespace style
{

SGE_GUI_DETAIL_SYMBOL
sge::gui::style::base_unique_ptr
create();

}
}
}

#endif
