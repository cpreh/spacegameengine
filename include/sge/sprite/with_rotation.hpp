/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SPRITE_WITH_ROTATION_HPP_INCLUDED
#define SGE_SPRITE_WITH_ROTATION_HPP_INCLUDED

namespace sge
{
namespace sprite
{

template<
	typename Context
>
class with_rotation {
public:
	typedef typename Context::float_type rotation_type;
	typedef typename Context::pos_type pos_type;

	typedef optional<
		pos_type
	> optional_rotation;

	with_rotation(
		rotation_type const rotation_,
		optional_rotation const &rotate_around_
	)
	:
		rotate_around_(rotate_around_),
		rotation_(rotation_)
	{}

	void
	rotation(
		rotation_type const nrotation_
	)
	{
		rotation_ = nortation_;
	}

	void
	rotate_around(
		optional_rotation const &nrotate_around_
	)
	{
		rotate_around_ = nrotate_around_;
	}

	optional_rotation const
	rotate_around() const
	{
		return rotate_around_;
	}

	rotation_type
	rotation() const
	{
		return rotation_;
	}
protected:
	~with_rotation()
	{}
private:
	rotation_type rotation_;

	optional_rotation rotate_around_;
};

}
}

#endif
