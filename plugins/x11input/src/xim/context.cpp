//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/exception.hpp>
#include <sge/x11input/xim/context.hpp>
#include <awl/backends/x11/window/object.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/Xlib.h>
#include <fcppt/config/external_end.hpp>


sge::x11input::xim::context::context(
	XIM const _xim,
	awl::backends::x11::window::object const &_window
)
:
	xic_(
		::XCreateIC(
			_xim,
			XNClientWindow,
			_window.get(),
			XNInputStyle,
			XIMPreeditNothing | XIMStatusNothing,
			NULL
		)
	)
{
	if(
		xic_
		==
		nullptr
	)
		throw
			sge::input::exception{
				FCPPT_TEXT("XCreateIC() failed!")
			};
}

sge::x11input::xim::context::~context()
{
	::XDestroyIC(
		xic_
	);
}

XIC
sge::x11input::xim::context::get() const
{
	return
		xic_;
}
