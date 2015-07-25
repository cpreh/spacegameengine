/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/context/system/base.hpp>
#include <sge/opengl/context/system/id.hpp>
#include <sge/opengl/context/system/make_id.hpp>
#include <sge/opengl/glx/proc_context.hpp>
#include <fcppt/optional_alternative.hpp>
#include <fcppt/optional_from_pointer.hpp>
#include <fcppt/config/external_begin.hpp>
#include <GL/glx.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::glx::proc_context::proc_context()
:
	sge::opengl::context::system::base(),
	get_proc_address_(
		fcppt::optional_alternative(
			fcppt::optional_from_pointer(
				::glXGetProcAddress
			),
			fcppt::optional_from_pointer(
				::glXGetProcAddressARB
			)
		)
	)
{
}

sge::opengl::glx::proc_context::~proc_context()
{
}

sge::opengl::glx::proc_context::optional_proc_address_function const
sge::opengl::glx::proc_context::get_proc_address() const
{
	return
		get_proc_address_;
}

sge::opengl::context::system::id const
sge::opengl::glx::proc_context::static_id(
	sge::opengl::context::system::make_id()
);
