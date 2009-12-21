/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/config.h>
#include "../create.hpp"
#if defined(SGE_HAVE_XRANDR)
#include "../xrandr_mode.hpp"
#endif
#if defined(SGE_HAVE_XF86_VMODE)
#include "../xf86_vmode.hpp"
#endif
#include <sge/renderer/parameters.hpp>
#include <sge/log/global.hpp>
#include <sge/x11/window.hpp>
#include <sge/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/headers.hpp>

sge::opengl::x11::resolution::auto_ptr
sge::opengl::x11::resolution::create(
	sge::x11::window_ptr const wnd,
	renderer::parameters const &param,
	renderer::adapter_type const adapter)
{
	if(param.wmode() == renderer::window_mode::windowed)
		return auto_ptr();
#if defined(SGE_HAVE_XRANDR)
	try
	{
		return auto_ptr(
			new xrandr_mode(
				param.mode(),
				wnd));
	}
	catch(exception const &e)
	{
		FCPPT_LOG_WARNING(
			log::global(),
			fcppt::log::_ << e.string());
	}
#endif
#if defined(SGE_HAVE_XF86_VMODE)
	try
	{
		return auto_ptr(
			new xf86_vmode(
				param.mode(),
				wnd->display(),
				wnd->screen()));
	}
	catch(exception const &e)
	{
		FCPPT_LOG_WARNING(
			log::global(),
			fcppt::log::_ << e.string());
	}
#endif
	FCPPT_LOG_WARNING(
		log::global(),
		fcppt::log::_
			<< FCPPT_TEXT("sge cannot switch resolutions because ")
			<< FCPPT_TEXT("no known method worked!"));
	return auto_ptr();
}
