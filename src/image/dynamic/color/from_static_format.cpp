/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "from_static_format.hpp"
#include "alpha8_format.hpp"
#include "gray8_format.hpp"
#include "ag8_format.hpp"
#include "ga8_format.hpp"
#include "rgb8_format.hpp"
#include "rgba8_format.hpp"
#include "argb8_format.hpp"
#include "bgra8_format.hpp"
#include "rgb32f_format.hpp"
#include "rgba32f_format.hpp"
#include "argb32f_format.hpp"
#include "bgra32f_format.hpp"

sge::image::dynamic::color::c8_1_format const *
sge::image::dynamic::color::from_static_format(
	image::color::alpha8_format const &
)
{
	return &dynamic::color::alpha8_format;
}

sge::image::dynamic::color::c8_1_format const *
sge::image::dynamic::color::from_static_format(
	image::color::gray8_format const &
)
{
	return &dynamic::color::gray8_format;
}

sge::image::dynamic::color::c8_2_format const *
sge::image::dynamic::color::from_static_format(
	image::color::ag8_format const &
)
{
	return &dynamic::color::ag8_format;
}

sge::image::dynamic::color::c8_2_format const *
sge::image::dynamic::color::from_static_format(
	image::color::ga8_format const &
)
{
	return &dynamic::color::ga8_format;
}

sge::image::dynamic::color::c8_3_format const *
sge::image::dynamic::color::from_static_format(
	image::color::rgb8_format const &
)
{
	return &dynamic::color::rgb8_format;
}

sge::image::dynamic::color::c8_4_format const *
sge::image::dynamic::color::from_static_format(
	image::color::rgba8_format const &
)
{
	return &dynamic::color::rgba8_format;
}

sge::image::dynamic::color::c8_4_format const *
sge::image::dynamic::color::from_static_format(
	image::color::argb8_format const &
)
{
	return &dynamic::color::argb8_format;
}

sge::image::dynamic::color::c8_4_format const *
sge::image::dynamic::color::from_static_format(
	image::color::bgra8_format const &
)
{
	return &dynamic::color::bgra8_format;
}

sge::image::dynamic::color::c32f_3_format const *
sge::image::dynamic::color::from_static_format(
	image::color::rgb32f_format const &
)
{
	return &dynamic::color::rgb32f_format;
}

sge::image::dynamic::color::c32f_4_format const *
sge::image::dynamic::color::from_static_format(
	image::color::rgba32f_format const &
)
{
	return &dynamic::color::rgba32f_format;
}

sge::image::dynamic::color::c32f_4_format const *
sge::image::dynamic::color::from_static_format(
	image::color::argb32f_format const &
)
{
	return &dynamic::color::argb32f_format;
}

sge::image::dynamic::color::c32f_4_format const *
sge::image::dynamic::color::from_static_format(
	image::color::bgra32f_format const &
)
{
	return &dynamic::color::bgra32f_format;
}
