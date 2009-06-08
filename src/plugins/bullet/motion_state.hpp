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


#ifndef SGE_BULLET_MOTION_STATE_HPP_INCLUDED
#define SGE_BULLET_MOTION_STATE_HPP_INCLUDED

#include "types.hpp"
#include <bullet/LinearMath/btMotionState.h>
#include <boost/function.hpp>

namespace sge
{
namespace bullet
{
typedef boost::function<void (point const &)> change_callback;

class motion_state : public btMotionState
{
public:
	explicit motion_state(change_callback const &);
	point const pos() const;
	void pos(point const &);
	void getWorldTransform(btTransform &) const;
	void setWorldTransform(btTransform const &);
private:
	btTransform pos_;
	change_callback callback;
};
}
}

#endif
