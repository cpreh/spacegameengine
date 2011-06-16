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


#ifndef SGE_IMAGE_VIEW_CHECKED_SUB_ANY_HPP_INCLUDED
#define SGE_IMAGE_VIEW_CHECKED_SUB_ANY_HPP_INCLUDED

#include "checked_sub_condition.hpp"
#include <sge/image/traits/box.hpp>
#include <sge/image/view/sub.hpp>

namespace sge
{
namespace image
{
namespace view
{

template<
	typename Tag,
	typename View
>
View const
checked_sub_any(
	View const &_view,
	typename image::traits::box<
		Tag
	>::type const &_box
)
{
	sge::image::view::checked_sub_condition<
		Tag
	>(
		_view,
		_box
	);

	return
		sge::image::view::sub<
			Tag
		>(
			_view,
			_box
		);
}

}
}
}

#endif
