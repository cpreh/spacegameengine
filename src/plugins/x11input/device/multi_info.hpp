/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_X11INPUT_DEVICE_MULTI_INFO_HPP_INCLUDED
#define SGE_X11INPUT_DEVICE_MULTI_INFO_HPP_INCLUDED

#include "info_base.hpp"
#include "id.hpp"
#include <awl/backends/x11/display_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>

namespace sge
{
namespace x11input
{
namespace device
{

class multi_info
{
	FCPPT_NONCOPYABLE(
		multi_info
	);
public:
	typedef info_base::size_type size_type;

	multi_info(
		awl::backends::x11::display &,
		x11input::device::id
	);

	~multi_info();

	XIDeviceInfo const &
	operator[](
		size_type index
	) const;

	size_type
	size() const;
private:
	device::info_base info_base_;
};

}
}
}

#endif
