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


#ifndef SGE_SRC_IMAGE_ALGORITHM_CLONE_VISITOR_HPP_INCLUDED
#define SGE_SRC_IMAGE_ALGORITHM_CLONE_VISITOR_HPP_INCLUDED

#include <sge/image/store/basic.hpp>
#include <sge/image/traits/store_fwd.hpp>
#include <mizuiro/image/algorithm/clone.hpp>


namespace sge
{
namespace image
{
namespace algorithm
{

template<
	typename Tag
>
struct clone_visitor
{
	typedef
	typename
	sge::image::traits::store<
		Tag
	>::type
	result_type;

	template<
		typename View
	>
	result_type
	operator()(
		View const &_view
	) const
	{
		return
			result_type(
				sge::image::store::basic<
					typename View::format
				>(
					mizuiro::image::algorithm::clone(
						_view
					)
				)
			);
	}
};

}
}
}

#endif
