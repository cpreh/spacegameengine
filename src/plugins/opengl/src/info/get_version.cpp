/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/common.hpp>
#include <sge/opengl/get_string.hpp>
#include <sge/opengl/backend/current_fwd.hpp>
#include <sge/opengl/info/get_version.hpp>
#include <sge/opengl/info/major_version.hpp>
#include <sge/opengl/info/minor_version.hpp>
#include <sge/opengl/info/version.hpp>
#include <sge/opengl/info/version_type.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/expect.hpp>
#include <fcppt/config/external_begin.hpp>
#include <sstream>
#include <fcppt/config/external_end.hpp>


sge::opengl::info::version
sge::opengl::info::get_version(
	sge::opengl::backend::current const &
)
{
	std::istringstream input(
		sge::opengl::get_string(
			GL_VERSION
		)
	);

	sge::opengl::info::version_type major;

	sge::opengl::info::version_type minor;

	input >> major;

	fcppt::io::expect(
		input,
		'.'
	);

	input >> minor;

	if(
		!input
	)
		throw
			sge::renderer::exception{
				FCPPT_TEXT("Getting GL_VERSION failed")
			};

	return
		sge::opengl::info::version{
			sge::opengl::info::major_version{
				major
			},
			sge::opengl::info::minor_version{
				minor
			}
		};
}
