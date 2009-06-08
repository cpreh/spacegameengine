/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_GUI_SKINS_STANDARD_HPP_INCLUDED
#define SGE_GUI_SKINS_STANDARD_HPP_INCLUDED

#include <sge/gui/skins/base.hpp>
#include <sge/font/system_fwd.hpp>
#include <sge/gui/export.hpp>

namespace sge
{
namespace gui
{
namespace skins
{
class standard : public base
{
	public:
	SGE_GUI_SYMBOL standard(
		font::system_ptr);
	SGE_GUI_SYMBOL SGE_GUI_SKIN_DRAW_RETURN(widgets::base) fallback(
		SGE_GUI_SKIN_DRAW_PARAMS(widgets::base));
	SGE_GUI_SKIN_WIDGETS
	SGE_GUI_SYMBOL font_info const standard_font() const;
	private:
	font_info const standard_font_;
};
}
}
}

#endif
