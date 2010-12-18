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


#include "../../image/view/sub_impl.hpp"
#include <sge/image2d/view/sub.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/variant/object_impl.hpp>

// TODO: create some macros for this
template
FCPPT_EXPORT_SYMBOL
sge::image2d::view::object const
sge::image::view::sub<
	sge::image2d::view::object,
	sge::image2d::rect
>(
	sge::image2d::view::object const &,
	sge::image2d::rect const &
);

template
FCPPT_EXPORT_SYMBOL
sge::image2d::view::const_object const
sge::image::view::sub<
	sge::image2d::view::const_object,
	sge::image2d::rect
>(
	sge::image2d::view::const_object const &,
	sge::image2d::rect const &
);

sge::image2d::view::object const
sge::image2d::view::sub(
	object const &_src,
	image2d::rect const &_rect
)
{
	return
		sge::image::view::sub(
			_src,
			_rect
		);
}

sge::image2d::view::const_object const
sge::image2d::view::sub(
	const_object const &_src,
	image2d::rect const &_rect
)
{
	return
		sge::image::view::sub(
			_src,
			_rect
		);
}
