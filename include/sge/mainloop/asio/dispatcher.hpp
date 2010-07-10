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


#ifndef SGE_MAINLOOP_ASIO_DISPATCHER_HPP_INCLUDED
#define SGE_MAINLOOP_ASIO_DISPATCHER_HPP_INCLUDED

#include <sge/mainloop/dispatcher.hpp>
#include <sge/mainloop/dispatcher_callback.hpp>
#include <sge/mainloop/native_handle.hpp>
#include <sge/symbol.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/noncopyable.hpp>
#include <boost/asio/posix/stream_descriptor.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/system/error_code.hpp>

namespace sge
{
namespace mainloop
{
namespace asio
{

class dispatcher
:
	public mainloop::dispatcher
{
	FCPPT_NONCOPYABLE(dispatcher)
public:
	SGE_SYMBOL
	explicit dispatcher(	
		boost::asio::io_service &,
		mainloop::native_handle,
		mainloop::dispatcher_callback const &
	);

	SGE_SYMBOL
	~dispatcher();
private:
	void
	register_handler();

	void
	callback(
		boost::system::error_code const &
	);

	boost::asio::posix::stream_descriptor stream_wrapper_;

	dispatcher_callback const callback_;
};

}
}
}

#endif
