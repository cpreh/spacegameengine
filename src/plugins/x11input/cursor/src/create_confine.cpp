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


#include "../create_confine.hpp"
#include "../grab/core.hpp"
#include <sge/x11input/config.hpp>
#if defined(SGE_X11INPUT_HAVE_XI_2_1)
#include "../grab/xi2.hpp"
#endif
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>

sge::x11input::cursor::confine_unique_ptr
sge::x11input::cursor::create_confine(
	awl::backends::x11::window::instance &_window,
#if defined(SGE_X11INPUT_HAVE_XI_2_1)
	x11input::device::id const _id,
	bool const _have_xi_2_1
#else
	x11input::device::id,
	bool
#endif
)
{
#if defined(SGE_X11INPUT_HAVE_XI_2_1)
	if(
		_have_xi_2_1
	)
		return
			cursor::confine_unique_ptr(
				fcppt::make_unique_ptr<
					cursor::grab::xi2
				>(
					fcppt::ref(
						_window
					),
					_id
				)
			);
#endif
	
	return
		cursor::confine_unique_ptr(
			fcppt::make_unique_ptr<
				cursor::grab::core
			>(
				fcppt::ref(
					_window
				)
			)
		);
}
