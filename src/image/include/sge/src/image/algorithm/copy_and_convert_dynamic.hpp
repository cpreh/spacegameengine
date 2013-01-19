/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SRC_IMAGE_ALGORITHM_COPY_AND_CONVERT_DYNAMIC_HPP_INCLUDED
#define SGE_SRC_IMAGE_ALGORITHM_COPY_AND_CONVERT_DYNAMIC_HPP_INCLUDED

#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/traits/color_tag.hpp>
#include <sge/image/traits/const_view_fwd.hpp>
#include <sge/image/traits/view_fwd.hpp>
#include <sge/src/image/traits/dynamic_copy_and_convert.hpp>



namespace sge
{
namespace image
{
namespace algorithm
{

template<
	typename Tag
>
void
copy_and_convert_dynamic(
	typename sge::image::traits::const_view<
		Tag
	>::type const &_src,
	typename sge::image::traits::view<
		Tag
	>::type const &_dest,
	sge::image::algorithm::may_overlap const _overlap
)
{
	sge::image::traits::dynamic_copy_and_convert<
		typename sge::image::traits::color_tag<
			Tag
		>::type
	>:: template execute<
		Tag
	>(
		_src,
		_dest,
		_overlap
	);
}

}
}
}

#endif
