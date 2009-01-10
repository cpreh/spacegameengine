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


#include <sge/renderer/color_float.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <sge/todo.hpp>

void sge::renderer::check_color_float_channel(
	color_channel_f32 const c)
{
	if(c < static_cast<color_channel_f32>(0)
	|| c > static_cast<color_channel_f32>(1))
		throw exception(
			SGE_TEXT("float color out of range!"));
}

void sge::renderer::check_color_float(
	rgba32f_color const &c)
{
	SGE_TODO("can we do this better?")
	for(unsigned i = 0; i < 4; ++i)
		check_color_float_channel(c[i]);
}
