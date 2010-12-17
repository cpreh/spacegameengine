/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_IMAGE_VIEW_SUB_VISITOR_HPP_INCLUDED
#define SGE_IMAGE_VIEW_SUB_VISITOR_HPP_INCLUDED

#include "../convert_dim.hpp"
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/nonassignable.hpp>
#include <mizuiro/image/sub_view.hpp>

namespace sge
{
namespace image
{
namespace view
{

template<
	typename Result,
	typename Box
>
class sub_visitor
{
	FCPPT_NONASSIGNABLE(
		sub_visitor
	)
public:
	typedef Result result_type;

	explicit sub_visitor(
		Box const &_box
	)
	:
		box_(_box)
	{
	}

	template<
		typename T
	>
	result_type const
	operator()(
		T const &_view
	) const
	{
		return
			mizuiro::image::sub_view(
				_view,
				typename T::bound_type(
					sge::image::convert_dim<
						typename T::bound_type::dim_type
					>(
						box_.pos()
					),
					sge::image::convert_dim<
						typename T::bound_type::dim_type
					>(
						box_.dimension()
					)
				)
			);
	}
private:
	Box const box_;
};

}
}
}

#endif
