/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/input/exception.hpp>
#include <sge/x11input/input_method.hpp>
#include <awl/backends/x11/display.hpp>
#include <awl/backends/x11/window/class_hint.hpp>
#include <awl/backends/x11/window/const_optional_class_hint_ref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/Xlib.h>
#include <fcppt/config/external_end.hpp>


sge::x11input::input_method::input_method(
	awl::backends::x11::display &_display,
	awl::backends::x11::window::const_optional_class_hint_ref const &_class_hint
)
:
	xim_(
		::XOpenIM(
			_display.get(),
			nullptr,
			fcppt::optional::maybe(
				_class_hint,
				[]()
				-> char *
				{
					return
						nullptr;
				},
				[](
					fcppt::reference<
						awl::backends::x11::window::class_hint const
					> const _hint
				)
				{
					return
						const_cast<
							char *
						>(
							_hint.get().res_name().c_str()
						);
				}
			),
			fcppt::optional::maybe(
				_class_hint,
				[]()
				-> char *
				{
					return
						nullptr;
				},
				[](
					fcppt::reference<
						awl::backends::x11::window::class_hint const
					> const _hint
				)
				{
					return
						const_cast<
							char *
						>(
							_hint.get().res_class().c_str()
						);
				}
			)
		)
	)
{
	if(
		xim_
		==
		nullptr
	)
		throw
			sge::input::exception{
				FCPPT_TEXT("XOpenIM() failed!")
			};
}

sge::x11input::input_method::~input_method()
{
	::XCloseIM(
		xim_
	);
}

XIM
sge::x11input::input_method::get() const
{
	return
		xim_;
}
