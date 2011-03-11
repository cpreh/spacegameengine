#ifndef SGE_CEGUI_TO_CEGUI_STRING_HPP_INCLUDED
#define SGE_CEGUI_TO_CEGUI_STRING_HPP_INCLUDED

#include <CEGUI/CEGUIString.h>
#include <sge/charconv/system_ptr.hpp>
#include <sge/cegui/symbol.hpp>
#include <fcppt/string.hpp>

namespace sge
{
namespace cegui
{
SGE_CEGUI_SYMBOL CEGUI::String const
to_cegui_string(
	fcppt::string const &,
	sge::charconv::system_ptr);
}
}

#endif
