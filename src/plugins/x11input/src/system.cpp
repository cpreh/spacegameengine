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


#include <sge/x11input/system.hpp>
#include <sge/x11input/lc_ctype.hpp>
#include <sge/x11input/optional_opcode.hpp>
#include <sge/x11input/processor.hpp>
#include <sge/x11input/scoped_locale.hpp>
#include <sge/x11input/xi_2_1.hpp>
#include <sge/x11input/xi_opcode.hpp>
#include <sge/x11input/xi_version.hpp>
#include <sge/input/exception.hpp>
#include <sge/log/global.hpp>
#include <sge/window/instance.hpp>
#include <awl/backends/x11/window/instance.hpp>
#include <awl/backends/x11/window/instance_shared_ptr.hpp>
#include <fcppt/log/info.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/polymorphic_pointer_cast.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/Xlib.h>
#include <fcppt/config/external_end.hpp>

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

	// The first supported version we ask for and that is supported will be used
	x11input::xi_2_1 const supports_xi_2_1(
		x11input::xi_version(
			x11_window->display(),
			2,
			1
		)
	);

	if(
		!supports_xi_2_1.get()
		&&
		!x11input::xi_version(
			x11_window->display(),
			2,
			0
		)
	)
		throw sge::input::exception(
			FCPPT_TEXT("The X server doesn't support XI2!")
		);

	if(
		char const *const locale_name =
			x11input::lc_ctype()
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
				+
				fcppt::from_std_string(
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
				<< FCPPT_TEXT("LC_CTYPE is not set.")
				<< FCPPT_TEXT(" Character conversion of X11 will not work properly!")
		);
	}

	FCPPT_LOG_INFO(
		sge::log::global(),
		fcppt::log::_
			<< FCPPT_TEXT("Using XI version ")
			<<
			(
				supports_xi_2_1.get()
				?
					FCPPT_TEXT("2.1")
				:
					FCPPT_TEXT("2.0")
			)
	);

	return
		fcppt::make_shared_ptr<
			x11input::processor
		>(
			_window,
			*opcode,
			supports_xi_2_1
		);
}
