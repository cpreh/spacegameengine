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


#ifndef SGE_IMAGE2D_STORE_OBJECT_HPP_INCLUDED
#define SGE_IMAGE2D_STORE_OBJECT_HPP_INCLUDED

#include <sge/image/color/traits/format_fwd.hpp>
#include <sge/image/color/traits/static_formats.hpp>
#include <sge/image/store/declare_object.hpp>
#include <sge/image2d/tag.hpp>
#include <sge/image2d/store/a8.hpp>
#include <sge/image2d/store/l8.hpp>
#include <sge/image2d/store/r32f.hpp>
#include <sge/image2d/store/la8.hpp>
#include <sge/image2d/store/rgb8.hpp>
#include <sge/image2d/store/bgr8.hpp>
#include <sge/image2d/store/rgba8.hpp>
#include <sge/image2d/store/rgbx8.hpp>
#include <sge/image2d/store/bgra8.hpp>
#include <sge/image2d/store/bgrx8.hpp>
#include <sge/image2d/store/rgb32f.hpp>
#include <sge/image2d/store/bgr32f.hpp>
#include <sge/image2d/store/rgba32f.hpp>
#include <sge/image2d/store/bgra32f.hpp>
#include <sge/image2d/store/srgb8.hpp>
#include <sge/image2d/store/srgba8.hpp>
#include <sge/image2d/store/sbgr8.hpp>
#include <sge/image2d/store/sbgra8.hpp>
#include <sge/image2d/store/object_fwd.hpp>
#include <sge/image2d/traits/color_tag.hpp>
#include <sge/image2d/traits/dimension.hpp>


SGE_IMAGE_STORE_DECLARE_OBJECT(
	sge::image2d::tag
);

#endif
