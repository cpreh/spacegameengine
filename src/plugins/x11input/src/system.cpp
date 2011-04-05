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


#include "../system.hpp"
#include "../optional_opcode.hpp"
#include "../processor.hpp"
#include "../scoped_locale.hpp"
#include "../xi_opcode.hpp"
#include "../xi_version.hpp"
#include <sge/input/exception.hpp>
#include <sge/log/global.hpp>
#include <sge/window/instance.hpp>
#include <awl/backends/x11/window/instance.hpp>
#include <awl/backends/x11/window/instance_shared_ptr.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/polymorphic_pointer_cast.hpp>
#include <fcppt/text.hpp>
#include <X11/Xlib.h>
#include <string>
#include <clocale>
#include <cstdlib>

sge::x11input::system::system()
{
}

sge::x11input::system::~system()
{
}

sge::input::processor_ptr const
sge::x11input::system::create_processor(
	sge::window::instance_ptr const _window
)
{
	awl::backends::x11::window::instance_shared_ptr const x11_window(
		fcppt::polymorphic_pointer_cast<
			awl::backends::x11::window::instance
		>(
			_window->awl_instance()
		)
	);
	
	x11input::optional_opcode const opcode(
		x11input::xi_opcode(
			x11_window->display()
		)
	);

	if(
		!opcode
	)
		throw sge::input::exception(
			FCPPT_TEXT("X Input extension not available! Please install libXi!")
		);

	if(
		!x11input::xi_version(
			x11_window->display(),
			2,
			0
		)
	)
		throw sge::input::exception(
			FCPPT_TEXT("X Input extension is not version 2 or later!")
		);

	if(
		char const *locale_name =
			std::getenv("LC_ALL")
	)
	{
		x11input::scoped_locale const temp_locale(
			locale_name
		);

		if(
			::XSupportsLocale()
			== False
		)
			throw sge::input::exception(
				FCPPT_TEXT("X doesn't support the locale ")
				+ std::string(
					locale_name
				)
			);

		if(
			::XSetLocaleModifiers(
				"" // XMODIFIERS are appended automatically
			)
			== NULL
		)
			throw sge::input::exception(
				FCPPT_TEXT("XSetLocaleModifiers() failed!")
			);
	}
	else
	{
		FCPPT_LOG_WARNING(
			sge::log::global(),
			fcppt::log::_
				<< FCPPT_TEXT("LC_ALL is not set.")
				<< FCPPT_TEXT(" Character conversion of X11 will not work properly!")
		);
	}

	return
		fcppt::make_shared_ptr<
			x11input::processor
		>(
			_window,
			*opcode
		);
}
