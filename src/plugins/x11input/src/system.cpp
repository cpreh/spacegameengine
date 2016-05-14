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


#include <sge/input/capabilities.hpp>
#include <sge/input/capabilities_field.hpp>
#include <sge/input/exception.hpp>
#include <sge/input/processor.hpp>
#include <sge/input/processor_unique_ptr.hpp>
#include <sge/input/system.hpp>
#include <sge/window/object.hpp>
#include <sge/window/system_fwd.hpp>
#include <sge/x11input/lc_ctype.hpp>
#include <sge/x11input/logger.hpp>
#include <sge/x11input/processor.hpp>
#include <sge/x11input/scoped_locale.hpp>
#include <sge/x11input/system.hpp>
#include <sge/x11input/xi_opcode.hpp>
#include <sge/x11input/xi_version.hpp>
#include <awl/backends/x11/system/event/opcode.hpp>
#include <awl/backends/x11/window/object.hpp>
#include <awl/window/object.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/Xlib.h>
#include <string>
#include <fcppt/config/external_end.hpp>


sge::x11input::system::system()
:
	sge::input::system()
{
}

sge::x11input::system::~system()
{
}

sge::input::processor_unique_ptr
sge::x11input::system::create_processor(
	sge::window::object const &_window,
	sge::window::system const &_window_system
)
{
	awl::backends::x11::window::object const &x11_window(
		fcppt::cast::dynamic<
			awl::backends::x11::window::object const &
		>(
			_window.awl_object()
		)
	);

	awl::backends::x11::system::event::opcode const opcode(
		fcppt::optional::to_exception(
			sge::x11input::xi_opcode(
				x11_window.display()
			),
			[]{
				return
					sge::input::exception{
						FCPPT_TEXT("X Input extension not available! Please install libXi!")
					};
			}
		)
	);

	// The first supported version we ask for and that is supported will be used
	if(
		!sge::x11input::xi_version(
			x11_window.display(),
			2,
			1
		)
	)
		throw
			sge::input::exception{
				FCPPT_TEXT("The X server doesn't support XI2.1!")
			};

	fcppt::optional::maybe(
		sge::x11input::lc_ctype(),
		[]{
			FCPPT_LOG_WARNING(
				sge::x11input::logger(),
				fcppt::log::_
					<< FCPPT_TEXT("LC_CTYPE is not set.")
					<< FCPPT_TEXT(" Character conversion of X11 will not work properly!")
			);
		},
		[](
			std::string const &_locale_name
		)
		{
			sge::x11input::scoped_locale const temp_locale(
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
		}
	);

	return
		fcppt::unique_ptr_to_base<
			sge::input::processor
		>(
			fcppt::make_unique_ptr<
				sge::x11input::processor
			>(
				_window,
				_window_system,
				opcode
			)
		);
}

sge::input::capabilities_field
sge::x11input::system::capabilities() const
{
	return
		sge::input::capabilities_field{
			sge::input::capabilities::cursor,
			sge::input::capabilities::focus,
			sge::input::capabilities::keyboard,
			sge::input::capabilities::mouse
		};
}
