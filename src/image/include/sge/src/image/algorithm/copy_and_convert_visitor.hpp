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


#ifndef SGE_SRC_IMAGE_ALGORITHM_COPY_AND_CONVERT_VISITOR_HPP_INCLUDED
#define SGE_SRC_IMAGE_ALGORITHM_COPY_AND_CONVERT_VISITOR_HPP_INCLUDED

#include <sge/image/mizuiro_color_traits.hpp>
#include <mizuiro/image/algorithm/copy_and_convert.hpp>
#include <mizuiro/image/algorithm/may_overlap.hpp>
#include <mizuiro/image/algorithm/uninitialized.hpp>
#include <fcppt/nonassignable.hpp>


namespace sge
{
namespace image
{
namespace algorithm
{

template<
	typename Converter
>
class copy_and_convert_visitor
{
	FCPPT_NONASSIGNABLE(
		copy_and_convert_visitor
	);
public:
	copy_and_convert_visitor(
		mizuiro::image::algorithm::may_overlap const _overlap,
		mizuiro::image::algorithm::uninitialized const _uninitialized
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

	typedef void result_type;

	template<
		typename Src,
		typename Dest
	>
	result_type
	operator()(
		Src const &_src,
		Dest const &_dest
	) const
	{
		return
			mizuiro::image::algorithm::copy_and_convert<
				Converter
			>(
				_src,
				_dest,
				overlap_,
				uninitialized_
			);
	}
private:
	mizuiro::image::algorithm::may_overlap const overlap_;

	mizuiro::image::algorithm::uninitialized const uninitialized_;
};

}
}
}

#endif
