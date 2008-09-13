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


#include <sge/renderer/color_convert.hpp>

template<typename Dest>
Dest const sge::renderer::color_convert(
	any_color const &col)
{
}

#define SGE_INSTANTIATE_COLOR_CONVERT(x)\
template x const sge::renderer::color_convert<x>(\
	sge::renderer::any_color const &);

SGE_INSTANTIATE_COLOR_CONVERT(sge::renderer::rgba8_color)
SGE_INSTANTIATE_COLOR_CONVERT(sge::renderer::argb8_color)
SGE_INSTANTIATE_COLOR_CONVERT(sge::renderer::bgra8_color)
SGE_INSTANTIATE_COLOR_CONVERT(sge::renderer::rgba_f32_color)

#undef SGE_INSTANTIATE_COLOR_CONVERT
