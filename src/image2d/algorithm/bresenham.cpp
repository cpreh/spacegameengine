/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/image/color/any/object_fwd.hpp>
#include <sge/image2d/vector_fwd.hpp>
#include <sge/image2d/algorithm/bresenham.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/src/image2d/algorithm/bresenham_visitor.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/variant/object_impl.hpp>


void
sge::image2d::algorithm::bresenham(
	sge::image2d::view::object const &_dest,
	sge::image2d::vector const &_pos1,
	sge::image2d::vector const &_pos2,
	sge::image::color::any::object const &_color
)
{
	fcppt::variant::apply_unary(
		sge::image2d::algorithm::bresenham_visitor(
			_pos1,
			_pos2,
			_color
		),
		_dest.get()
	);
}
