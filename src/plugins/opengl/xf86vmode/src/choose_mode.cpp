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


#include "../choose_mode.hpp"
#include "../modes.hpp"
#include "../calc_refresh_rate.hpp"
#include "../resolution.hpp"
#include <sge/renderer/display_mode.hpp>
#include <sge/exception.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/text.hpp>

sge::opengl::xf86vmode::resolution_ptr const
sge::opengl::xf86vmode::choose_mode(
	renderer::display_mode const &pmode,
	modes const &m)
{
	int best = -1;
	for(modes::size_type i = 1; i < m.size(); ++i)
	{
		XF86VidModeModeInfo const &mode = m[i];
		unsigned const rate = calc_refresh_rate(mode);

		if(
			mode.hdisplay == pmode.size().w() &&
			mode.vdisplay == pmode.size().h() &&
			rate  >= pmode.refresh_rate() &&
			(best == -1 || rate >= calc_refresh_rate(m[best]))
		)
			best = static_cast<int>(i);
	}

	if(best == -1)
		throw exception(
			FCPPT_TEXT("No matching resolution found in xf86vmode!"));
	return
		resolution_ptr(
			fcppt::make_shared_ptr<
				resolution
			>(
				m.display(),
				m.screen(),
				m[best],
				m[0]
			)
		);
}
