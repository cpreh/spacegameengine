#ifndef SGE_CEGUI_TO_CEGUI_STRING_HPP_INCLUDED
#define SGE_CEGUI_TO_CEGUI_STRING_HPP_INCLUDED

#include <CEGUI/CEGUIString.h>
#include <sge/charconv/system_ptr.hpp>
#include <fcppt/string.hpp>

namespace sge
{
namespace cegui
{
CEGUI::String const
to_cegui_string(
	fcppt::string const &,
	sge::charconv::system_ptr);
}
}

#endif
