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


#ifndef SGE_DINPUT_DEVICE_OBJECT_HPP_INCLUDED
#define SGE_DINPUT_DEVICE_OBJECT_HPP_INCLUDED

#include <sge/dinput/device/object_fwd.hpp>
#include <sge/dinput/device/parameters_fwd.hpp>
#include <sge/dinput/di.hpp>
#include <sge/dinput/dinput_device_scoped_ptr.hpp>
#include <fcppt/com_deleter.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>
#include <fcppt/container/array.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace dinput
{
namespace device
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	virtual void
	dispatch() = 0;

	virtual ~object();

	static std::size_t const buffer_size = 1024;

	bool
	acquire();

	void
	unacquire();
protected:
	explicit object(
		dinput::device::parameters const &
	);

	void
	poll();

	void
	set_data_format(
		LPCDIDATAFORMAT
	);

	void
	set_property(
		REFGUID,
		LPCDIPROPHEADER
	);

	void
	set_event_handle(
		HANDLE
	);

	typedef fcppt::container::array<
		DIDEVICEOBJECTDATA,
		buffer_size
	> input_buffer;

	bool
	get_input(
		input_buffer &,
		DWORD &elements
	);

	void
	enum_objects(
		LPDIENUMDEVICEOBJECTSCALLBACK
	);

	fcppt::string const &
	name() const;
private:
	fcppt::string const name_;

	dinput::dinput_device_scoped_ptr const device_;
};

}
}
}

#endif
