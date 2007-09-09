/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_GUI_SKIN_HPP_INCLUDED
#define SGE_GUI_SKIN_HPP_INCLUDED

namespace sge
{
namespace gui
{

class skin {
public:
	typedef const char* const name_type;
	static name_type button_name,
	       button_pressed_name,
	       button_hover_name,
	       textedit_name,
	       cursor_name,
	       cursor_pressed_name,
	       textcursor_name,
	       inner_scrollbar_name,
	       left_scrollbutton_name,
	       right_scrollbutton_name,
	       up_scrollbutton_name,
	       down_scrollbutton_name,
	       scrollbar_name,
	       list_background_name,
	       statictext_name,
	       checkbox_name,
	       clickbox_round_pressed_name,
	       clickbox_round_name,
	       clickbox_quad_pressed_name,
	       clickbox_quad_name;
};

}
}

#endif
