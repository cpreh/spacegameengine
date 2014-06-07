/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SRC_IMAGE_COLOR_TRAITS_DYNAMIC_COPY_AND_CONVERT_HPP_INCLUDED
#define SGE_SRC_IMAGE_COLOR_TRAITS_DYNAMIC_COPY_AND_CONVERT_HPP_INCLUDED

#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/color/tag.hpp>
#include <sge/image/traits/const_view_fwd.hpp>
#include <sge/image/traits/view_fwd.hpp>
#include <sge/src/image/color/dynamic/algorithm/copy_and_convert.hpp>
#include <sge/src/image/traits/dynamic_copy_and_convert.hpp>


namespace sge
{
namespace image
{
namespace traits
{

template<>
struct dynamic_copy_and_convert<
	sge::image::color::tag
>
{
	template<
		typename Tag
	>
	static
	void
	execute(
		typename sge::image::traits::const_view<
			Tag
		>::type const &_src,
		typename sge::image::traits::view<
			Tag
		>::type const &_dest,
		sge::image::algorithm::may_overlap const _overlap
	)
	{
		sge::image::color::dynamic::algorithm::copy_and_convert<
			Tag
		>(
			_src,
			_dest,
			_overlap
		);
	}
};

}
}
}

#endif
