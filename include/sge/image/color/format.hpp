/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_IMAGE_COLOR_FORMAT_HPP_INCLUDED
#define SGE_IMAGE_COLOR_FORMAT_HPP_INCLUDED

#include <sge/image/color/format_fwd.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace sge
{
namespace image
{
namespace color
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wshadow)

enum class format
{
	a8,
	l8,
	r32f,
	la8,
	rgb8,
	bgr8,
	rgba8,
	rgbx8,
	bgra8,
	bgrx8,
	rgb32f,
	bgr32f,
	rgba32f,
	bgra32f,
	srgb8,
	srgba8,
	sbgr8,
	sbgra8,
	fcppt_maximum = sbgra8
};

FCPPT_PP_POP_WARNING

}
}
}

#endif
