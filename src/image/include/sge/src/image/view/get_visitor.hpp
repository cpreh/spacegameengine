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


#ifndef SGE_SRC_IMAGE_VIEW_GET_VISITOR_HPP_INCLUDED
#define SGE_SRC_IMAGE_VIEW_GET_VISITOR_HPP_INCLUDED

#include <sge/image/dim.hpp>
#include <sge/image/mizuiro_color.hpp>
#include <sge/src/image/convert_dim.hpp>
#include <fcppt/nonassignable.hpp>


namespace sge
{
namespace image
{
namespace view
{

template<
	typename Result,
	typename Dim
>
class get_visitor
{
	FCPPT_NONASSIGNABLE(
		get_visitor
	);
public:
	typedef Result result_type;

	explicit
	get_visitor(
		Dim const &_index
	)
	:
		index_(
			_index
		)
	{
	}

	template<
		typename Src
	>
	result_type
	operator()(
		Src const &_src
	) const
	{
		return
			Result(
				typename sge::image::mizuiro_color<
					typename Src::format::color_format
				>::type(
					_src[
						sge::image::convert_dim<
							typename Src::dim
						>(
							index_
						)
					]
				)
			);
	}
private:
	Dim const index_;
};

}
}
}

#endif
