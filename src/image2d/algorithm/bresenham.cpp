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
#include <sge/image2d/dim.hpp>
#include <sge/image2d/view/size.hpp>
#include <sge/image2d/vector_fwd.hpp>
#include <sge/image2d/algorithm/bresenham.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/src/image2d/algorithm/bresenham_visitor.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/assert/pre_message.hpp>
#include <fcppt/text.hpp>

void
sge::image2d::algorithm::bresenham(
	sge::image2d::view::object const &_dest,
	sge::image2d::vector const &_pos1,
	sge::image2d::vector const &_pos2,
	sge::image::color::any::object const &_color1,
	sge::image::color::any::object const &_color2
)
{
	sge::image2d::dim const dim(sge::image2d::view::size(_dest));

	FCPPT_ASSERT_PRE_MESSAGE(
		_pos1[0] < dim.w() &&
		_pos2[0] < dim.w(),
		FCPPT_TEXT("max width exceeded"));
	FCPPT_ASSERT_PRE_MESSAGE(
		_pos1[1] < dim.h() &&
		_pos2[1] < dim.h(),
		FCPPT_TEXT("max height exceeded"));
	fcppt::variant::apply_unary(
		sge::image2d::algorithm::bresenham_visitor(
			_pos1,
			_pos2,
			_color1,
			_color2
		),
		_dest.get()
	);
}
