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


#include "../texpos_actor.hpp"
#include "../../check_state.hpp"
#include "../../multi_texture_context.hpp"
#include "../../set_client_texture_level.hpp"
#include "../../context/use.hpp"
#include <sge/renderer/vf/dynamic/ordered_element.hpp>
#include <sge/renderer/vf/dynamic/vector.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/exception.hpp>
#include <fcppt/format.hpp>
#include <fcppt/text.hpp>

sge::opengl::vf::texpos_actor::texpos_actor(
	opengl::context::object &_context,
	renderer::vf::dynamic::ordered_element const &_elements,
	renderer::vf::vertex_size const _stride
)
:
	fp_actor(
		_elements,
		_stride,
		GL_TEXTURE_COORD_ARRAY
	),
	context_(
		_context
	),
	elements_(
		static_cast<
			GLint
		>(
			_elements.element().info().get<
				renderer::vf::dynamic::vector
			>().elements()
		)
	)
{
	multi_texture_context &texture_context(
		opengl::context::use<
			multi_texture_context
		>(
			_context
		)
	);

	if(
		!texture_context.is_supported()
		&& index() != 0
	)
		throw renderer::exception(
			FCPPT_TEXT("multiple texture coordinates are not supported!")
		);
	else if(
		index()
		>= texture_context.max_level()
	)
		throw renderer::exception(
			(
				fcppt::format(
					FCPPT_TEXT("opengl texture coordinates exceeded: Allowed are %1%.")
				)
				% texture_context.max_level()
			).str()
		);
}

void
sge::opengl::vf::texpos_actor::on_use() const
{
	opengl::set_client_texture_level(
		context_,
		static_cast<
			renderer::stage_type
		>(
			index()
		)
	);

	glTexCoordPointer(
		elements_,
		format(),
		stride(),
		pointer()
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glTexCoordPointer failed"),
		sge::renderer::exception
	)
}
