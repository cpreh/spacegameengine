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


#include <sge/opengl/check_state.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/texture/multi_context.hpp>
#include <sge/opengl/texture/funcs/set_client_level.hpp>
#include <sge/opengl/vf/actor_parameters.hpp>
#include <sge/opengl/vf/client_state_combiner.hpp>
#include <sge/opengl/vf/convert_element_type.hpp>
#include <sge/opengl/vf/texpos_actor.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/vf/vertex_size.hpp>
#include <sge/renderer/vf/dynamic/ordered_element.hpp>
#include <sge/renderer/vf/dynamic/vector.hpp>
#include <fcppt/format.hpp>
#include <fcppt/text.hpp>


sge::opengl::vf::texpos_actor::texpos_actor(
	vf::actor_parameters const &_param,
	renderer::vf::dynamic::texpos const &_element
)
:
	vf::pointer_actor(
		_param
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
		renderer::stage(
			static_cast<
				renderer::stage::value_type
			>(
				_element.index()
			)
		)
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
		&& index_.get() != 0
	)
		throw renderer::exception(
			FCPPT_TEXT("multiple texture coordinates are not supported!")
		);
	else if(
		index_
		>=
		renderer::stage(
			static_cast<
				renderer::stage::value_type
			>(
				texture_context.max_level()
			)
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
sge::opengl::vf::texpos_actor::operator()(
	vf::client_state_combiner &_combiner,
	vf::pointer const _src
) const
{
	_combiner.enable_texture(
		index_
	);

	opengl::texture::funcs::set_client_level(
		context_,
		sge::renderer::stage(
			index_
		)
	);

	::glTexCoordPointer(
		elements_,
		format_,
		static_cast<
			GLsizei
		>(
			this->stride()
		),
		_src
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glTexCoordPointer failed"),
		sge::renderer::exception
	)
}

void
sge::opengl::vf::texpos_actor::unuse(
	vf::client_state_combiner &_combiner
) const
{
	_combiner.disable_texture(
		index_
	);
}
