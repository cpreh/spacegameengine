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


#include <sge/src/image/dynamic/color/available_channels.hpp>
#include <sge/src/image/dynamic/color/c8_2_format.hpp>
#include <sge/src/image/dynamic/color/la8_format.hpp>
#include <fcppt/assign/make_array.hpp>


sge::image::dynamic::color::c8_2_format const
sge::image::dynamic::color::la8_format(
	fcppt::assign::make_array<
		sge::image::dynamic::color::available_channels::type
	>
	(
		sge::image::dynamic::color::available_channels::luminance
	)
	(
		sge::image::dynamic::color::available_channels::alpha
	)
);
