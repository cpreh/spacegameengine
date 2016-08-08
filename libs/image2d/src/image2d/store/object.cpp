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


#include <sge/image/color/impl/instantiate_format.hpp>
#include <sge/image/impl/store/instantiate_object.hpp>
#include <sge/image2d/store/element.hpp>
#include <sge/image2d/store/elements_wrapper.hpp>
#include <sge/image2d/store/object.hpp>


#define SGE_IMAGE2D_STORE_OBJECT_INSTANTIATE_ARGS ( \
	sge::image2d::store::elements_wrapper, \
	sge::image2d::store::element, \
	sge::image::color \
)

SGE_IMAGE_IMPL_STORE_INSTANTIATE_OBJECT(
	SGE_IMAGE2D_STORE_OBJECT_INSTANTIATE_ARGS,
	SGE_IMAGE_COLOR_IMPL_INSTANTIATE_FORMAT
);

#undef SGE_IMAGE2D_STORE_OBJECT_INSTANTIATE_ARGS
