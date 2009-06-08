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


#include "../mouse_keys.hpp"
#include <sge/text.hpp>

sge::input::key_type const
sge::x11input::mouse_x(
	SGE_TEXT("mouse_x"),
	input::kc::mouse_x_axis);

sge::input::key_type const
sge::x11input::mouse_y(
	SGE_TEXT("mouse_y"),
	input::kc::mouse_y_axis);

sge::input::key_type const
sge::x11input::undefined_mouse_key(
	SGE_TEXT("undefined mouse key"));

sge::input::key_type const
sge::x11input::mouse_l(
	SGE_TEXT("mouse_L"),
	input::kc::mouse_l);

sge::input::key_type const
sge::x11input::mouse_r(
	SGE_TEXT("mouse_R"),
	input::kc::mouse_r);

sge::input::key_type const
sge::x11input::mouse_m(
	SGE_TEXT("mouse_M"),
	input::kc::mouse_m);
