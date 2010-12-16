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


#include <sge/image2d/view/flipped.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <mizuiro/image/flipped_view.hpp>

namespace
{

template<
	typename View
>
class visitor
{
public:
	typedef View const result_type;

	template<
		typename T
	>
	result_type
	operator()(
		T const &
	) const;
};

}

sge::image2d::view::object const
sge::image2d::view::flipped(
	object const &_view
)
{
	return
		fcppt::variant::apply_unary(
			::visitor<
				view::object
			>(),
			_view
		);
}

sge::image2d::view::const_object const
sge::image2d::view::flipped(
	const_object const &_view
)
{
	return
		fcppt::variant::apply_unary(
			::visitor<
				view::const_object
			>(),
			_view
		);
}

namespace
{

template<
	typename View
>
template<
	typename T
>
typename visitor<View>::result_type
visitor<View>::operator()(
	T const &_view
) const
{
	return
		typename ::visitor<
			View
		>::result_type(
			mizuiro::image::flipped_view(
				_view
			)
		);
}

}
