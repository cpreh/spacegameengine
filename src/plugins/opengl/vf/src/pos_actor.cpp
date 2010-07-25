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


#include "../pos_actor.hpp"
#include "../convert_element_type.hpp"
#include "../../check_state.hpp"
#include <sge/renderer/vf/dynamic/vector.hpp>
#include <sge/renderer/vf/dynamic/pos.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

sge::opengl::vf::pos_actor::pos_actor(
	actor_parameters const &_param,
	renderer::vf::dynamic::pos const &_pos
)
:
	fp_actor(
		_param,
		GL_VERTEX_ARRAY
	),
	format_(
		vf::convert_element_type(
			_pos.type().element_type()
		)
	),
	elements_(
		static_cast<
			GLint
		>(
			_pos.type().elements()
		)
	)
{}

void
sge::opengl::vf::pos_actor::on_use(
	vf::pointer const _src
) const
{
	glVertexPointer(
		elements_,
		format_,
		static_cast<
			GLsizei
		>(
			stride()
		),
		_src
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glVertexPointer failed"),
		sge::renderer::exception
	)
}
