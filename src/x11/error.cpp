/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/x11/error.hpp>

namespace
{

sge::x11::optional_error last_error_;

int error_handler(
	Display *,
	XErrorEvent *);

class init {
public:
	init();
} init_;

}

sge::x11::optional_error const
sge::x11::last_error()
{
	optional_error const ret(
		last_error_);
	last_error_.reset();
	return ret;
}

namespace
{

int error_handler(
	Display *,
	XErrorEvent *const ev)
{
	last_error_ = *ev;
	return 0; // TODO: what should we return?
}

init::init()
{
	XSetErrorHandler(
		error_handler);
}

}
