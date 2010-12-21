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


#ifndef SGE_X11INPUT_DEVICE_OBJECT_HPP_INCLUDED
#define SGE_X11INPUT_DEVICE_OBJECT_HPP_INCLUDED

#include "object_fwd.hpp"
#include "id.hpp"
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace x11input
{
namespace device
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	)
protected:
	explicit device(
		object::id const &
	);
public:
	virtual void
	grab() = 0;

	virtual void
	ungrab() = 0;

	virtual ~object();
private:
	device::id const id_;
};

}
}
}

#endif
