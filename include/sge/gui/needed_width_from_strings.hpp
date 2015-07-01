#ifndef SGE_GUI_NEEDED_WIDTH_FROM_STRINGS_HPP_INCLUDED
#define SGE_GUI_NEEDED_WIDTH_FROM_STRINGS_HPP_INCLUDED

#include <sge/gui/needed_width.hpp>
#include <sge/gui/string_container.hpp>
#include <sge/gui/detail/symbol.hpp>
#include <sge/font/object_fwd.hpp>


namespace sge
{
namespace gui
{

SGE_GUI_DETAIL_SYMBOL
sge::gui::needed_width const
needed_width_from_strings(
	sge::font::object &,
	sge::gui::string_container const &
);

}
}

#endif
