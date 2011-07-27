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


#include "../texpos_actor.hpp"
#include "../actor_parameters.hpp"
#include "../convert_element_type.hpp"
#include "../../check_state.hpp"
#include "../../common.hpp"
#include "../../context/use.hpp"
#include "../../texture/multi_context.hpp"
#include "../../texture/funcs/set_client_level.hpp"
#include <sge/renderer/vf/dynamic/ordered_element.hpp>
#include <sge/renderer/vf/dynamic/vector.hpp>
#include <sge/renderer/vf/vertex_size.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/format.hpp>
#include <fcppt/text.hpp>

sge::opengl::vf::texpos_actor::texpos_actor(
	actor_parameters const &_param,
	renderer::vf::dynamic::texpos const &_element
)
:
	fp_actor(
		_param,
		GL_TEXTURE_COORD_ARRAY
	),
	context_(
		_param.context()
	),
	elements_(
		static_cast<
			GLint
		>(
			_element.type().elements()
		)
	),
	format_(
		vf::convert_element_type(
			_element.type().element_type()
		)
	),
	index_(
		_element.index()
	)
{
	texture::multi_context &texture_context(
		opengl::context::use<
			texture::multi_context
		>(
			context_
		)
	);

	if(
		!texture_context.is_supported()
		&& index_ != 0
	)
		throw renderer::exception(
			FCPPT_TEXT("multiple texture coordinates are not supported!")
		);
	else if(
		index_
		>=
		static_cast<
			renderer::vf::vertex_size
		>(
			texture_context.max_level()
		)
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

sge::opengl::vf::texpos_actor::~texpos_actor()
{
}

void
sge::opengl::vf::texpos_actor::on_use(
	vf::pointer const _src
) const
{
	opengl::texture::funcs::set_client_level(
		context_,
		sge::renderer::stage(
			static_cast<
				sge::renderer::stage::value_type
			>(
				index_
			)
		)
	);

	::glTexCoordPointer(
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
		FCPPT_TEXT("glTexCoordPointer failed"),
		sge::renderer::exception
	)
}
