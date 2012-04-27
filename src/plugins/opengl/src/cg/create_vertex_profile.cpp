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


#include <sge/cg/vertex_profile.hpp>
#include <sge/cg/vertex_profile_unique_ptr.hpp>
#include <sge/opengl/cg/create_vertex_profile.hpp>
#include <sge/opengl/cg/get_latest_profile.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cgGL.h>
#include <fcppt/config/external_end.hpp>


sge::cg::vertex_profile_unique_ptr
sge::opengl::cg::create_vertex_profile()
{
	return
		sge::cg::vertex_profile_unique_ptr(
			fcppt::make_unique_ptr<
				sge::cg::vertex_profile
			>(
				sge::opengl::cg::get_latest_profile(
					CG_GL_VERTEX
				)
			)
		);
}
