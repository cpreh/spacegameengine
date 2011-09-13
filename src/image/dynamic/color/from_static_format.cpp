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
#include "a8_format.hpp"
#include "l8_format.hpp"
#include "la8_format.hpp"
#include "rgb8_format.hpp"
#include "bgr8_format.hpp"
#include "rgba8_format.hpp"
#include "rgbx8_format.hpp"
#include "bgra8_format.hpp"
#include "bgrx8_format.hpp"
#include "rgb32f_format.hpp"
#include "bgr32f_format.hpp"
#include "rgba32f_format.hpp"
#include "bgra32f_format.hpp"

#define SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(\
	dformat,\
	sformat\
)\
sge::image::dynamic::color::dformat const * \
sge::image::dynamic::color::from_static_format(\
	sge::image::color::sformat const &\
)\
{\
	return &sge::image::dynamic::color::sformat;\
}

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(\
	c8_1_format,
	a8_format
)

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(\
	c8_1_format,
	l8_format
)

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(\
	c8_2_format,
	la8_format
)

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(\
	c8_3_format,
	rgb8_format
)

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(\
	c8_3_format,
	bgr8_format
)

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(\
	c8_4_format,
	rgba8_format
)

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(\
	c8_4_format,
	rgbx8_format
)

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(\
	c8_4_format,
	bgra8_format
)

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(\
	c8_4_format,
	bgrx8_format
)

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(\
	c32f_3_format,
	rgb32f_format
)

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(\
	c32f_3_format,
	bgr32f_format
)

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(\
	c32f_4_format,
	rgba32f_format
)

SGE_IMAGE_DYNAMIC_COLOR_DEFINE_FUNCTION(\
	c32f_4_format,
	bgra32f_format
)
