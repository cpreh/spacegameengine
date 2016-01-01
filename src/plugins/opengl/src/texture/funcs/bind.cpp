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


#include <sge/opengl/call.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/texture/id.hpp>
#include <sge/opengl/texture/no_id.hpp>
#include <sge/opengl/texture/optional_id.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/opengl/texture/funcs/bind.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/const.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/from.hpp>


void
sge::opengl::texture::funcs::bind(
	sge::opengl::texture::type const _type,
	sge::opengl::texture::optional_id const &_value
)
{
	sge::opengl::call(
		::glBindTexture,
		_type.get(),
		fcppt::optional::from(
			_value,
			fcppt::const_(
				sge::opengl::texture::no_id
			)
		).get()
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glBindTexture failed"),
		sge::renderer::exception
	)
}
