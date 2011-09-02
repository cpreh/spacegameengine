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


#include "../input_context.hpp"
#include <sge/input/exception.hpp>
#include <awl/backends/x11/window/class_hint.hpp>
#include <awl/backends/x11/window/instance.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/Xlib.h>
#include <fcppt/config/external_end.hpp>

sge::x11input::input_context::input_context(
	XIM const _xim,
	awl::backends::x11::window::class_hint const *const _class_hint,
	awl::backends::x11::window::instance &_window
)
:
	xic_(
		_class_hint
		?
			::XCreateIC(
				_xim,
				XNClientWindow,
				_window.get(),
				XNFocusWindow,
				_window.get(),
				XNInputStyle,
				XIMPreeditNothing | XIMStatusNothing,
				XNResourceName,
				_class_hint->res_name().c_str(),
				XNResourceClass,
				_class_hint->res_class().c_str(),
				NULL
			)
		:
			NULL
	)
{
	if(
		!_class_hint
	)
		throw sge::input::exception(
			FCPPT_TEXT("XCreateIC() called without a class hint!")
		);

	if(
		xic_ == NULL
	)
		throw sge::input::exception(
			FCPPT_TEXT("XCreateIC() failed!")
		);
}

sge::x11input::input_context::~input_context()
{
	::XDestroyIC(
		xic_
	);
}

XIC
sge::x11input::input_context::get() const
{
	return xic_;
}
