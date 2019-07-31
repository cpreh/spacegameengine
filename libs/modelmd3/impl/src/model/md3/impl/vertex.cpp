//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/model/md3/load_flags.hpp>
#include <sge/model/md3/load_flags_field.hpp>
#include <sge/model/md3/impl/read_s16.hpp>
#include <sge/model/md3/impl/s16.hpp>
#include <sge/model/md3/impl/vertex.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/container/bitfield/operators.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::model::md3::impl::vertex::vertex(
	std::istream &_stream,
	sge::model::md3::load_flags_field const _flags
)
:
	x_(
		sge::model::md3::impl::read_s16(
			_stream
		)
	),
	y_(
		sge::model::md3::impl::read_s16(
			_stream
		)
	),
	z_(
		sge::model::md3::impl::read_s16(
			_stream
		)
	),
	normal_(
		sge::model::md3::impl::read_s16(
			_stream
		)
	)
{
	if(
		_flags
		&
		sge::model::md3::load_flags::switch_yz
	)
	{
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
			fcppt::cast::size<
				sge::model::md3::impl::s16
			>(
				-x_
			);

		std::swap(
			y_,
			z_
		);
	}
}

sge::model::md3::impl::s16
sge::model::md3::impl::vertex::x() const
{
	return
		x_;
}

sge::model::md3::impl::s16
sge::model::md3::impl::vertex::y() const
{
	return
		y_;
}

sge::model::md3::impl::s16
sge::model::md3::impl::vertex::z() const
{
	return
		z_;
}

sge::model::md3::impl::s16
sge::model::md3::impl::vertex::normal() const
{
	return
		normal_;
}
