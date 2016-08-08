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


#ifndef SGE_IMAGE_IMPL_ALGORITHM_COMPARE_VISITOR_HPP_INCLUDED
#define SGE_IMAGE_IMPL_ALGORITHM_COMPARE_VISITOR_HPP_INCLUDED

#include <sge/image/impl/algorithm/compare_element.hpp>
#include <mizuiro/color/make_compare_function.hpp>
#include <mizuiro/image/algorithm/compare.hpp>


namespace sge
{
namespace image
{
namespace impl
{
namespace algorithm
{

struct compare_visitor
{
	typedef
	bool
	result_type;

	template<
		typename View1,
		typename View2
	>
	result_type
	operator()(
		View1 const &,
		View2 const &
	) const
	{
		return
			false;
	}

	template<
		typename View
	>
	result_type
	operator()(
		View const &_view1,
		View const &_view2
	) const
	{
		return
			mizuiro::image::algorithm::compare(
				_view1,
				_view2,
				mizuiro::color::make_compare_function(
					sge::image::algorithm::compare_element()
				)
			);
	}
};

}
}
}
}

#endif
