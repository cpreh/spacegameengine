/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/opengl/config.hpp>
#include <sge/opengl/x11/resolution/create.hpp>
#include <sge/opengl/x11/resolution/object.hpp>
#include <sge/opengl/x11/resolution/object_unique_ptr.hpp>
#if defined(SGE_OPENGL_HAVE_XRANDR)
#include <sge/opengl/x11/resolution/xrandr_mode.hpp>
#endif
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/log/global.hpp>
#include <sge/exception.hpp>
#include <awl/backends/x11/window/object.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>


sge::opengl::x11::resolution::object_unique_ptr
sge::opengl::x11::resolution::create(
	awl::backends::x11::window::object &_window,
	sge::renderer::display_mode::optional_object const &_mode
)
{
	if(
		!_mode
	)
		return sge::opengl::x11::resolution::object_unique_ptr();

#if !defined(SGE_OPENGL_HAVE_XRANDR) && !defined(SGE_OPENGL_HAVE_XF86VMODE)
	FCPPT_LOG_WARNING(
		sge::log::global(),
		fcppt::log::_
			<< FCPPT_TEXT("sge has not been compiled with fullscreen support.")
			<< FCPPT_TEXT(" Use -D ENABLE_XRANDR=ON.")
	);

	return
		sge::opengl::x11::resolution::object_unique_ptr();
#else
#if defined(SGE_OPENGL_HAVE_XRANDR)
	try
	{
		return
			sge::opengl::x11::resolution::object_unique_ptr(
				fcppt::make_unique_ptr<
					sge::opengl::x11::resolution::xrandr_mode
				>(
					*_mode,
					fcppt::ref(
						_window
					)
				)
			);
	}
	catch(
		sge::exception const &_exception
	)
	{
		FCPPT_LOG_WARNING(
			log::global(),
			fcppt::log::_ << _exception.string()
		);
	}
#endif
	FCPPT_LOG_WARNING(
		sge::log::global(),
		fcppt::log::_
			<< FCPPT_TEXT("sge cannot switch resolutions because ")
			<< FCPPT_TEXT("no known method worked!")
	);

	return
		sge::opengl::x11::resolution::object_unique_ptr();
#endif
}
