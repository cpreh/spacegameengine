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


#ifndef SGE_IMAGE_DYNAMIC_ALGORITHM_CAC_VISITOR_HPP_INCLUDED
#define SGE_IMAGE_DYNAMIC_ALGORITHM_CAC_VISITOR_HPP_INCLUDED

#include "permutate_compare.hpp"
#include "../../view/color_layout.hpp"
#include "convert.hpp"
#include "copy.hpp"
#include <sge/image/algorithm/may_overlap.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace image
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
	explicit visitor(
		image::algorithm::may_overlap::type const _overlap
	)
	:
		overlap_(_overlap)
	{
	}

	typedef void result_type;

	template<
		typename Source,
		typename Dest
	>
	typename boost::enable_if<
		boost::is_same<
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
			cac::permuate_compare(
				view::color_layout(
					_source
				),
				view::color_layout(
					_dest
				)
			)
		)
			cac::copy(
				_source,
				_dest,
				overlap_
			);
		else
			cac::convert(
				_source,
				_dest
			);
	}

	template<
		typename Source,
		typename Dest
	>
	typename boost::disable_if<
		boost::is_same<
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
		cac::convert(
			_source,
			_dest
		);
	}
private:
	image::algorithm::may_overlap::type const overlap_;
};

}
}
}
}
}

#endif
