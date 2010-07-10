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


#ifndef SGE_X11_IO_SERVICE_CONTEXT_HPP_INCLUDED
#define SGE_X11_IO_SERVICE_CONTEXT_HPP_INCLUDED

#include <sge/x11/io_service_context_fwd.hpp>
#include <sge/x11/display_ptr.hpp>
#include <sge/x11/window_ptr.hpp>
#include <sge/mainloop/io_service_ptr.hpp>
#include <sge/mainloop/dispatcher_ptr.hpp>
#include <sge/symbol.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace x11
{

class io_service_context
{
	FCPPT_NONCOPYABLE(io_service_context)
public:
	SGE_SYMBOL
	explicit io_service_context(	
		mainloop::io_service_ptr,
		x11::display_ptr,
		x11::window_ptr
	);

	SGE_SYMBOL
	~io_service_context();
private:
	void
	callback();
	
	sge::x11::window_ptr const window_;

	sge::mainloop::dispatcher_ptr const dispatcher_;
};

}
}

#endif
