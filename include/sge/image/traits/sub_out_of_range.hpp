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


#ifndef SGE_IMAGE_TRAITS_SUB_OUT_OF_RANGE_HPP_INCLUDED
#define SGE_IMAGE_TRAITS_SUB_OUT_OF_RANGE_HPP_INCLUDED

#include <sge/image2d/view/sub_out_of_range.hpp>
#include <sge/image2d/tag.hpp>
#include <sge/image3d/view/sub_out_of_range.hpp>
#include <sge/image3d/tag.hpp>

namespace sge
{
namespace image
{
namespace traits
{

template<
	typename Tag
>
struct sub_out_of_range;

template<>
struct sub_out_of_range<
	image2d::tag
>
{
	typedef image2d::view::sub_out_of_range type;
};

template<>
struct sub_out_of_range<
	image3d::tag
>
{
	typedef image3d::view::sub_out_of_range type;
};

}
}
}

#endif
