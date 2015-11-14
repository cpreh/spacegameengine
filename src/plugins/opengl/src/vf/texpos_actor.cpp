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
#include <sge/opengl/context/object.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/texture/multi_config.hpp>
#include <sge/opengl/texture/multi_context.hpp>
#include <sge/opengl/texture/funcs/set_client_level.hpp>
#include <sge/opengl/vf/actor_parameters.hpp>
#include <sge/opengl/vf/client_state_combiner.hpp>
#include <sge/opengl/vf/convert_element_type.hpp>
#include <sge/opengl/vf/pointer.hpp>
#include <sge/opengl/vf/texpos_actor.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/vf/vertex_size.hpp>
#include <sge/renderer/vf/dynamic/ordered_element.hpp>
#include <sge/renderer/vf/dynamic/vector.hpp>
#include <fcppt/format.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>


sge::opengl::vf::texpos_actor::texpos_actor(
	sge::opengl::vf::actor_parameters const &_param,
	sge::renderer::vf::dynamic::texpos const &_element
)
:
	sge::opengl::vf::pointer_actor(
		_param
	),
	context_(
		_param.context()
	),
	elements_(
		fcppt::cast::size<
			GLint
		>(
			fcppt::cast::to_signed(
				_element.type().element_count().get()
			)
		)
	),
	format_(
		sge::opengl::vf::convert_element_type(
			_element.type().element_type()
		)
	),
	index_(
		_element.index().get()
	)
{
	fcppt::maybe(
		sge::opengl::context::use<
			sge::opengl::texture::multi_context
		>(
			context_,
			context_.info()
		).config(),
		[
			this
		]{
			if(
				index_.get()
				!=
				0u
			)
				throw
					sge::renderer::exception{
						FCPPT_TEXT("multiple texture coordinates are not supported!")
					};
		},
		[
			this
		](
			sge::opengl::texture::multi_config const &_config
		)
		{
			if(
				index_.get()
				>=
				_config.max_level().get()
			)
				throw
					sge::renderer::exception{
						(
							fcppt::format(
								FCPPT_TEXT("opengl texture coordinates exceeded: Allowed are %1%.")
							)
							%
							_config.max_level()
						).str()
					};
		}
	);
}

sge::opengl::vf::texpos_actor::~texpos_actor()
{
}

void
sge::opengl::vf::texpos_actor::operator()(
	sge::opengl::vf::client_state_combiner &_combiner,
	sge::opengl::vf::pointer const _src
) const
{
	_combiner.enable_texture(
		index_
	);

	sge::opengl::texture::funcs::set_client_level(
		context_,
		index_
	);

	sge::opengl::call(
		::glTexCoordPointer,
		elements_,
		format_,
		fcppt::cast::size<
			GLsizei
		>(
			fcppt::cast::to_signed(
				this->stride().get()
			)
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
	sge::opengl::vf::client_state_combiner &_combiner
) const
{
	_combiner.disable_texture(
		index_
	);
}
