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


#include <sge/image2d/view/checked_sub.hpp>
#include <sge/image2d/view/sub.hpp>
#include <sge/image2d/view/sub_out_of_range.hpp>
#include <sge/image2d/view/dim.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/make_const.hpp>
#include <sge/image2d/rect.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/box/contains.hpp>
#include <fcppt/variant/object_impl.hpp>

namespace
{

void
check_condition(
	sge::image2d::view::const_object const &,
	sge::image2d::rect const &
);

}

sge::image2d::view::object const
sge::image2d::view::checked_sub(
	view::object const &_src,
	image2d::rect const &_rect
)
{
	::check_condition(
		sge::image2d::view::make_const(
			_src
		),
		_rect
	);

	return
		image2d::view::sub(
			_src,
			_rect
		);
}

sge::image2d::view::const_object const
sge::image2d::view::checked_sub(
	view::const_object const &_src,
	image2d::rect const &_rect
)
{
	::check_condition(
		_src,
		_rect
	);

	return
		image2d::view::sub(
			_src,
			_rect
		);
}

namespace
{

void
check_condition(
	sge::image2d::view::const_object const &_src,
	sge::image2d::rect const &_rect
)
{
	sge::image2d::rect const outer(
		sge::image2d::rect::vector::null(),
		sge::image2d::view::dim(
			_src
		)
	);

	if(
		!fcppt::math::box::contains(
			outer,
			_rect
		)
	)
		throw sge::image2d::view::sub_out_of_range(
			outer,
			_rect
		);
}

}
