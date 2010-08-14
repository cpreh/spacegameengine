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


#ifndef SGE_MAINLOOP_ASIO_IO_SERVICE_HPP_INCLUDED
#define SGE_MAINLOOP_ASIO_IO_SERVICE_HPP_INCLUDED

#include <sge/mainloop/io_service.hpp>
#include <sge/mainloop/native_handle.hpp>
#include <sge/mainloop/dispatcher_callback.hpp>
#include <sge/class_symbol.hpp>
#include <sge/symbol.hpp>
#include <boost/asio/io_service.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace mainloop
{
namespace asio
{

class SGE_CLASS_SYMBOL io_service
:
	public mainloop::io_service
{
	FCPPT_NONCOPYABLE(io_service)
public:
	SGE_SYMBOL
	io_service();

	SGE_SYMBOL
	~io_service();

	SGE_SYMBOL
	boost::asio::io_service &
	get();
private:
	void
	run_one();

	void
	run();

	void
	poll();

	void
	stop();

	void
	reset();

	void
	dispatch(
		dispatcher_callback const &
	);

	dispatcher_ptr const
	create_dispatcher(
		native_handle,
		dispatcher_callback const &
	);

	boost::asio::io_service io_service_;
};

}
}
}

#endif
