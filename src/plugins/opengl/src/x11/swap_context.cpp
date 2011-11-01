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


#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/glx/proc_address.hpp>
#include <sge/opengl/x11/swap_context.hpp>


sge::opengl::x11::swap_context::swap_context(
	opengl::glx::proc_context const &_context
)
:
	swap_interval_(
		reinterpret_cast<
			glx_swap_interval
		>(
			glx::proc_address(
				_context,
				"glXSwapIntervalSGI"
			)
		)
	)
{
}

sge::opengl::x11::swap_context::~swap_context()
{
}

bool
sge::opengl::x11::swap_context::swap_interval_supported() const
{
	return
		swap_interval_ != 0;
}

sge::opengl::x11::swap_context::glx_swap_interval
sge::opengl::x11::swap_context::swap_interval() const
{
	return swap_interval_;
}

sge::opengl::context::id const
sge::opengl::x11::swap_context::static_id(
	sge::opengl::context::make_id()
);
