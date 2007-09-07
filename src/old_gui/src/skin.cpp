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


#include "../skin.hpp"

#define DEFINE_SKIN_NAME(x) sge::gui::skin::name_type sge::gui::skin:: x##_name = #x;

DEFINE_SKIN_NAME(button)
DEFINE_SKIN_NAME(button_pressed)
DEFINE_SKIN_NAME(button_hover)
DEFINE_SKIN_NAME(textedit)
DEFINE_SKIN_NAME(cursor)
DEFINE_SKIN_NAME(cursor_pressed)
DEFINE_SKIN_NAME(textcursor)
DEFINE_SKIN_NAME(scrollbar)
DEFINE_SKIN_NAME(inner_scrollbar)
DEFINE_SKIN_NAME(left_scrollbutton)
DEFINE_SKIN_NAME(right_scrollbutton)
DEFINE_SKIN_NAME(up_scrollbutton)
DEFINE_SKIN_NAME(down_scrollbutton)
DEFINE_SKIN_NAME(list_background)
DEFINE_SKIN_NAME(statictext)
DEFINE_SKIN_NAME(checkbox)
DEFINE_SKIN_NAME(clickbox_round_pressed)
DEFINE_SKIN_NAME(clickbox_round)
DEFINE_SKIN_NAME(clickbox_quad_pressed)
DEFINE_SKIN_NAME(clickbox_quad)

#undef DEFINE_SKIN_NAME
