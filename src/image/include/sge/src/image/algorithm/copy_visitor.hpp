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


#ifndef SGE_SRC_IMAGE_ALGORITHM_COPY_VISITOR_HPP_INCLUDED
#define SGE_SRC_IMAGE_ALGORITHM_COPY_VISITOR_HPP_INCLUDED

#include <sge/image/mizuiro_color.hpp>
#include <sge/image/traits/view_fwd.hpp>
#include <sge/image/view/mizuiro_type.hpp>
#include <sge/image/view/object.hpp>
#include <mizuiro/nonconst_tag.hpp>
#include <mizuiro/image/algorithm/copy.hpp>
#include <mizuiro/image/algorithm/may_overlap.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/variant/get.hpp>


namespace sge
{
namespace image
{
namespace algorithm
{

template<
	typename Tag
>
class copy_visitor
{
	FCPPT_NONASSIGNABLE(
		copy_visitor
	);
public:
	typedef typename sge::image::traits::view<
		Tag
	>::type view;

	copy_visitor(
		view const &_dest,
		mizuiro::image::algorithm::may_overlap const _overlap
	)
	:
		dest_(
			_dest
		),
		overlap_(
			_overlap
		)
	{
	}

	typedef void result_type;

	template<
		typename Src
	>
	result_type
	operator()(
		Src const &_src
	) const
	{
		typedef typename view::variant dest_variant;

		dest_variant const &variant(
			dest_.get()
		);

		return
			mizuiro::image::algorithm::copy(
				_src,
				fcppt::variant::get<
					typename sge::image::view::mizuiro_type<
						typename Src::format,
						mizuiro::nonconst_tag
					>::type
				>(
					variant
				),
				overlap_
			);
	}
private:
	view const &dest_;

	mizuiro::image::algorithm::may_overlap const overlap_;
};

}
}
}

#endif
