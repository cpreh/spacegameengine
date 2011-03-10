#ifndef SGE_CEGUI_FROM_CEGUI_STRING_HPP_INCLUDED
#define SGE_CEGUI_FROM_CEGUI_STRING_HPP_INCLUDED

#include <sge/cegui/symbol.hpp>
#include <sge/charconv/system_ptr.hpp>
#include <CEGUI/CEGUIString.h>
#include <fcppt/string.hpp>

namespace sge
{
namespace cegui
{
SGE_CEGUI_SYMBOL fcppt::string const
from_cegui_string(
	CEGUI::String const &,
	sge::charconv::system_ptr);
}
}

#endif
