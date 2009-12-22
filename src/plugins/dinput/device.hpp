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


#ifndef SGE_DINPUT_DEVICE_HPP_INCLUDED
#define SGE_DINPUT_DEVICE_HPP_INCLUDED

#include "di.hpp"
#include "signal.hpp"
#include <sge/windows/window_fwd.hpp>
#include <sge/input/key_type.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/tr1/array.hpp>
#include <fcppt/noncopyable.hpp>
#include <cstddef>

namespace sge
{
namespace dinput
{

class device {
	FCPPT_NONCOPYABLE(device)
public:
	virtual void dispatch(signal_type &) = 0;
	virtual ~device();

	static std::size_t const buffer_size = 1024;

	void acquire();
	void unacquire();
protected:
	device(
		dinput_ptr di,
		string const &name,
		GUID Guid,
		windows::window_ptr window);

	void poll();
	void set_data_format(
		LPCDIDATAFORMAT lpdf);
	void set_property(
		REFGUID rguidProp,
		LPCDIPROPHEADER pdiph);

	typedef std::tr1::array<
		DIDEVICEOBJECTDATA,
		buffer_size
	> input_buffer;

	bool get_input(
		input_buffer &buf,
		DWORD &elements,
		unsigned d = 0);
	void enum_objects(
		LPDIENUMDEVICEOBJECTSCALLBACK fun);
	string const &name() const;
private:
	void set_cooperative_level(
		HWND hwnd,
		DWORD flags);
	string const name_;
	signal::scoped_connection const activate_connection;
	dinput_device_ptr device_;
};

}
}

#endif
