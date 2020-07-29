//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
#include <sge/opengl/vf/client_state_combiner_ref.hpp>
#include <sge/opengl/vf/convert_element_type.hpp>
#include <sge/opengl/vf/pointer.hpp>
#include <sge/opengl/vf/texpos_actor.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/vf/vertex_size.hpp>
#include <sge/renderer/vf/dynamic/ordered_element.hpp>
#include <sge/renderer/vf/dynamic/vector.hpp>
#include <fcppt/format.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/log/object_reference.hpp>
#include <fcppt/optional/maybe.hpp>


sge::opengl::vf::texpos_actor::texpos_actor(
	fcppt::log::object_reference const _log,
	sge::opengl::vf::actor_parameters const &_param,
	sge::renderer::vf::dynamic::texpos const &_element
)
:
	sge::opengl::vf::pointer_actor(
		_param
	),
	log_{
		_log
	},
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
	fcppt::optional::maybe(
		sge::opengl::context::use<
			sge::opengl::texture::multi_context
		>(
			context_,
			context_.get().info()
		).config(),
		[
			this
		]{
			if(
				index_.get()
				!=
				0U
			)
			{
				throw
					sge::renderer::exception{
						FCPPT_TEXT("multiple texture coordinates are not supported!")
					};
			}
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
			{
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
		}
	);
}

sge::opengl::vf::texpos_actor::~texpos_actor()
= default;

void
sge::opengl::vf::texpos_actor::operator()(
	sge::opengl::vf::client_state_combiner_ref const _combiner,
	sge::opengl::vf::pointer const _src
) const
{
	_combiner.get().enable_texture(
		index_
	);

	sge::opengl::texture::funcs::set_client_level(
		log_.get(),
		context_.get(),
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
	sge::opengl::vf::client_state_combiner_ref const _combiner
) const
{
	_combiner.get().disable_texture(
		index_
	);
}
