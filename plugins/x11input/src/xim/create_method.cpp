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
#include <sge/x11input/xim/create_method.hpp>
#include <sge/x11input/xim/lc_ctype.hpp>
#include <sge/x11input/xim/method.hpp>
#include <sge/x11input/xim/method_unique_ptr.hpp>
#include <sge/x11input/xim/scoped_locale.hpp>
#include <awl/backends/x11/display_fwd.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/Xlib.h>
#include <string>
#include <fcppt/config/external_end.hpp>


sge::x11input::xim::method_unique_ptr
sge::x11input::xim::create_method(
	fcppt::log::object &_log,
	awl::backends::x11::display const &_display
)
{
	return
		fcppt::optional::maybe(
			sge::x11input::xim::lc_ctype(),
			[
				&_display,
				&_log
			]{
				FCPPT_LOG_WARNING(
					_log,
					fcppt::log::out
						<< FCPPT_TEXT("LC_CTYPE is not set.")
						<< FCPPT_TEXT(" Character conversion of X11 will not work properly!")
				)

				return
					fcppt::make_unique_ptr<
						sge::x11input::xim::method
					>(
						_display
					);
			},
			[
				&_display
			](
				std::string const &_locale_name
			)
			{
				sge::x11input::xim::scoped_locale const temp_locale(
					_locale_name
				);

				if(
					::XSupportsLocale()
					==
					False
				)
					throw
						sge::input::exception{
							FCPPT_TEXT("X doesn't support the locale ")
							+
							fcppt::from_std_string(
								_locale_name
							)
						};

				if(
					::XSetLocaleModifiers(
						"" // XMODIFIERS are appended automatically
					)
					==
					nullptr
				)
					throw
						sge::input::exception{
							FCPPT_TEXT("XSetLocaleModifiers() failed!")
						};

				return
					fcppt::make_unique_ptr<
						sge::x11input::xim::method
					>(
						_display
					);
			}
		);
}
