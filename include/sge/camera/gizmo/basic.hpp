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


#ifndef SGE_CAMERA_GIZMO_BASIC_HPP_INCLUDED
#define SGE_CAMERA_GIZMO_BASIC_HPP_INCLUDED

#include <fcppt/math/size_type.hpp>
#include <fcppt/math/vector/vector.hpp>
#include <boost/array.hpp>

namespace sge
{
namespace camera
{
namespace gizmo
{
template<typename Scalar,fcppt::math::size_type N>
class basic
{
public:
	typedef 
	Scalar 
	scalar;

	typedef typename
	fcppt::math::vector::static_<scalar,N>::type
	vector;

	typedef
	boost::array<vector,3>
	array_type;

	vector const &
	position() const
	{
		return position_;
	}

	vector const &
	right() const
	{
		return array_[0];
	}

	vector const &
	up() const
	{
		return array_[1];
	}

	vector const &
	forward() const
	{
		return array_[2];
	}

	array_type const &
	array() const
	{
		return array_;
	}

	array_type &
	array()
	{
		return array_;
	}

	basic &
	position(
		vector const &p)
	{
		position_ = p;
		return *this;
	}

	basic &
	right(
		vector const &p)
	{
		array_[0] = p;
		return *this;
	}

	basic &
	up(
		vector const &p)
	{
		array_[1] = p;
		return *this;
	}

	basic &
	forward(
		vector const &p)
	{
		array_[2] = p;
		return *this;
	}
private:
	vector position_;
	array_type array_;
};
}
}
}

#endif
