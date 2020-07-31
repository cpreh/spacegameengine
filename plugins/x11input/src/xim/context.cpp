//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/exception.hpp>
#include <sge/x11input/xim/context.hpp>
#include <awl/backends/x11/window/object.hpp>
#include <awl/backends/x11/window/object_ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/Xlib.h>
#include <fcppt/config/external_end.hpp>


sge::x11input::xim::context::context(
	XIM const _xim, // NOLINT(misc-misplaced-const)
	awl::backends::x11::window::object_ref const _window
)
:
	xic_(
		::XCreateIC( // NOLINT(cppcoreguidelines-pro-type-vararg,hicpp-vararg)
			_xim,
			XNClientWindow,
			_window.get().get(),
			XNInputStyle,
			XIMPreeditNothing | XIMStatusNothing, // NOLINT(hicpp-signed-bitwise)
			NULL
		)
	)
{
	if(
		xic_
		==
		nullptr
	)
	{
		throw
			sge::input::exception{
				FCPPT_TEXT("XCreateIC() failed!")
			};
	}
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
