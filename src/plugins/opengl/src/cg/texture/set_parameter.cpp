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


#include <sge/cg/check_state.hpp>
#include <sge/cg/parameter/object.hpp>
#include <sge/opengl/cg/texture/set_parameter.hpp>
#include <sge/opengl/texture/no_id.hpp>
#include <sge/opengl/texture/optional_id.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/const.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cgGL.h>
#include <fcppt/config/external_end.hpp>


void
sge::opengl::cg::texture::set_parameter(
	sge::cg::parameter::object const &_parameter,
	sge::opengl::texture::optional_id const &_id
)
{
	::cgGLSetTextureParameter(
		_parameter.get(),
		fcppt::optional::from(
			_id,
			fcppt::const_(
				sge::opengl::texture::no_id
			)
		).get()
	);

	SGE_CG_CHECK_STATE(
		FCPPT_TEXT("cgGLSetTextureParameter failed"),
		sge::renderer::exception
	)
}
