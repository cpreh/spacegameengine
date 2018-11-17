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


#ifndef SGE_IMAGE_COLOR_IMPL_DYNAMIC_ALGORITHM_CAC_VISITOR_HPP_INCLUDED
#define SGE_IMAGE_COLOR_IMPL_DYNAMIC_ALGORITHM_CAC_VISITOR_HPP_INCLUDED

#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image/color/impl/dynamic/algorithm/cac/convert.hpp>
#include <sge/image/color/impl/dynamic/algorithm/cac/copy.hpp>
#include <sge/image/color/impl/dynamic/algorithm/cac/permutate_compare.hpp>
#include <sge/image/color/impl/dynamic/view/color_layout.hpp>
#include <fcppt/not.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace image
{
namespace color
{
namespace impl
{
namespace dynamic
{
namespace algorithm
{
namespace cac
{

class visitor
{
public:
	visitor(
		sge::image::algorithm::may_overlap const _overlap,
		sge::image::algorithm::uninitialized const _uninitialized
	)
	:
		overlap_{
			_overlap
		},
		uninitialized_{
			_uninitialized
		}
	{
	}

	typedef
	void
	result_type;

	template<
		typename Source,
		typename Dest
	>
	std::enable_if_t<
		std::is_same<
			typename Source::format,
			typename Dest::format
		>::value,
		result_type
	>
	operator()(
		Source const &_source,
		Dest const &_dest
	) const
	{
		if(
			sge::image::color::impl::dynamic::algorithm::cac::permutate_compare(
				sge::image::color::impl::dynamic::view::color_layout(
					_source
				),
				sge::image::color::impl::dynamic::view::color_layout(
					_dest
				)
			)
		)
			sge::image::color::impl::dynamic::algorithm::cac::copy(
				_source,
				_dest,
				overlap_,
				uninitialized_
			);
		else
			sge::image::color::impl::dynamic::algorithm::cac::convert(
				_source,
				_dest,
				uninitialized_
			);
	}

	template<
		typename Source,
		typename Dest
	>
	std::enable_if_t<
		fcppt::not_(
			std::is_same<
				typename Source::format,
				typename Dest::format
			>::value
		),
		result_type
	>
	operator()(
		Source const &_source,
		Dest const &_dest
	) const
	{
		sge::image::color::impl::dynamic::algorithm::cac::convert(
			_source,
			_dest,
			uninitialized_
		);
	}
private:
	sge::image::algorithm::may_overlap overlap_;

	sge::image::algorithm::uninitialized uninitialized_;
};

}
}
}
}
}
}
}

#endif
