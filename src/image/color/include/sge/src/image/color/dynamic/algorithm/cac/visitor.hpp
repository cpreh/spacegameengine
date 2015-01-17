/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SRC_IMAGE_COLOR_DYNAMIC_ALGORITHM_CAC_VISITOR_HPP_INCLUDED
#define SGE_SRC_IMAGE_COLOR_DYNAMIC_ALGORITHM_CAC_VISITOR_HPP_INCLUDED

#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/src/image/color/dynamic/algorithm/cac/convert.hpp>
#include <sge/src/image/color/dynamic/algorithm/cac/copy.hpp>
#include <sge/src/image/color/dynamic/algorithm/cac/permutate_compare.hpp>
#include <sge/src/image/color/dynamic/view/color_layout.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace image
{
namespace color
{
namespace dynamic
{
namespace algorithm
{
namespace cac
{

class visitor
{
	FCPPT_NONASSIGNABLE(
		visitor
	);
public:
	explicit
	visitor(
		sge::image::algorithm::may_overlap const _overlap
	)
	:
		overlap_(
			_overlap
		)
	{
	}

	typedef void result_type;

	template<
		typename Source,
		typename Dest
	>
	typename boost::enable_if<
		std::is_same<
			typename Source::format,
			typename Dest::format
		>,
		result_type
	>::type
	operator()(
		Source const &_source,
		Dest const &_dest
	) const
	{
		if(
			sge::image::color::dynamic::algorithm::cac::permutate_compare(
				sge::image::color::dynamic::view::color_layout(
					_source
				),
				sge::image::color::dynamic::view::color_layout(
					_dest
				)
			)
		)
			sge::image::color::dynamic::algorithm::cac::copy(
				_source,
				_dest,
				overlap_
			);
		else
			sge::image::color::dynamic::algorithm::cac::convert(
				_source,
				_dest
			);
	}

	template<
		typename Source,
		typename Dest
	>
	typename boost::disable_if<
		std::is_same<
			typename Source::format,
			typename Dest::format
		>,
		result_type
	>::type
	operator()(
		Source const &_source,
		Dest const &_dest
	) const
	{
		sge::image::color::dynamic::algorithm::cac::convert(
			_source,
			_dest
		);
	}
private:
	sge::image::algorithm::may_overlap const overlap_;
};

}
}
}
}
}
}

#endif
