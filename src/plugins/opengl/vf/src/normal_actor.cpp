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


#include "../normal_actor.hpp"
#include "../convert_element_type.hpp"
#include "../../check_state.hpp"
#include <sge/renderer/vf/dynamic/normal.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

sge::opengl::vf::normal_actor::normal_actor(
	actor_parameters const &_param,
	renderer::vf::dynamic::normal const &_normal
)
:
	fp_actor(
		_param,
		GL_NORMAL_ARRAY
	),
	format_(
		vf::convert_element_type(
			_normal.element_type()
		)
	)
{
}

void
sge::opengl::vf::normal_actor::on_use(
	vf::pointer const _src
) const
{
	glNormalPointer(
		format_,
		static_cast<
			GLsizei
		>(
			stride()
		),
		_src
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glNormalPointer failed"),
		sge::renderer::exception
	)
}
