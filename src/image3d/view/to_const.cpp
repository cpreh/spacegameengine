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


#include "../../image/view/to_const_impl.hpp"
#include <sge/image3d/view/to_const.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/export_symbol.hpp>

template
FCPPT_EXPORT_SYMBOL
sge::image3d::view::const_object const
sge::image::view::to_const<
	sge::image3d::view::const_object,
	sge::image3d::view::object
>(
	sge::image3d::view::object const &
);

sge::image3d::view::const_object const
sge::image3d::view::to_const(
	object const &_view
)
{
	return
		sge::image::view::to_const<
			sge::image3d::view::const_object
		>(
			_view
		);
}
