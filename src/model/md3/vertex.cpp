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


#include <sge/model/md3/load_flags.hpp>
#include <sge/src/model/md3/endian.hpp>
#include <sge/src/model/md3/s16.hpp>
#include <sge/src/model/md3/vertex.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/io/read.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


sge::model::md3::vertex::vertex(
	std::istream &_stream,
	md3::load_flags::type const _flags
)
:
	x_(
		fcppt::io::read<
			md3::s16
		>(
			_stream,
			md3::endian()
		)
	),
	y_(
		fcppt::io::read<
			md3::s16
		>(
			_stream,
			md3::endian()
		)
	),
	z_(
		fcppt::io::read<
			md3::s16
		>(
			_stream,
			md3::endian()
		)
	),
	normal_(
		fcppt::io::read<
			md3::s16
		>(
			_stream,
			md3::endian()
		)
	)
{
	switch(
		_flags
	)
	{
	case md3::load_flags::none:
		return;
	case md3::load_flags::switch_yz:
		// Motivation for this strange stuff:
		//
		// We assume our md3 is aligned with z as the "up" axis. To
		// realign it, we rotate by 90 degrees on the x axis. This
		// corresponds to a rotation matrix:
		//
		//  1  0  0
		//  0  0  1
		//  0 -1  0
		//
		// After that, however, the z axis points to the wrong
		// direction (found empirically). So we rotate by 180 degrees
		// around the y axis, which corresponds to a rotation matrix
		//
		//  -1 0  0
		//  0  1  0
		//  0  0 -1
		//
		// Multiplying those with an arbitrary vector (x,y,z) results in:
		//
		// (-x,z,y)
		x_ =
			static_cast<
				md3::s16
			>(
				-x_
			);

		std::swap(
			y_,
			z_
		);

		return;
	}

	FCPPT_ASSERT_UNREACHABLE;
}

sge::model::md3::s16
sge::model::md3::vertex::x() const
{
	return x_;
}

sge::model::md3::s16
sge::model::md3::vertex::y() const
{
	return y_;
}

sge::model::md3::s16
sge::model::md3::vertex::z() const
{
	return z_;
}

sge::model::md3::s16
sge::model::md3::vertex::normal() const
{
	return normal_;
}
