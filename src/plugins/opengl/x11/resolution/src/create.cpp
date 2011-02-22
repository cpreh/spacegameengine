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


#include <sge/opengl/config.hpp>
#include "../create.hpp"
#include "../instance.hpp"
#if defined(SGE_OPENGL_HAVE_XRANDR)
#include "../xrandr_mode.hpp"
#endif
#if defined(SGE_OPENGL_HAVE_XF86_VMODE)
#include "../xf86_vmode.hpp"
#endif
#include <sge/renderer/display_mode.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/log/global.hpp>
#include <sge/exception.hpp>
#include <awl/backends/x11/window/instance.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/variant/holds_type.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>

sge::opengl::x11::resolution::unique_ptr
sge::opengl::x11::resolution::create(
	awl::backends::x11::window::instance_ptr const _window,
	renderer::parameters const &_param,
	renderer::adapter const _adapter
)
{
	if(
		!fcppt::variant::holds_type<
			sge::renderer::display_mode
		>(
			_param.screen_mode()
		)
	)
		return resolution::unique_ptr();
	
	sge::renderer::display_mode const display_mode(
		_param.screen_mode().get<
			sge::renderer::display_mode
		>()
	);
#if defined(SGE_OPENGL_HAVE_XRANDR)
	try
	{
		return
			resolution::unique_ptr(
				fcppt::make_unique_ptr<
					resolution::xrandr_mode
				>(
					display_mode,
					_window
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
#if defined(SGE_OPENGL_HAVE_XF86_VMODE)
	try
	{
		return
			resolution::unique_ptr(
				fcppt::make_unique_ptr<
					resolution::xf86_vmode
				>(
					display_mode,
					_window->display(),
					_window->screen()
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
		log::global(),
		fcppt::log::_
			<< FCPPT_TEXT("sge cannot switch resolutions because ")
			<< FCPPT_TEXT("no known method worked!")
	);

	return resolution::unique_ptr();
}
