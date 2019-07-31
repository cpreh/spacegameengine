//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/texture/base.hpp>
#include <sge/opengl/texture/bind_context.hpp>
#include <sge/opengl/texture/get_stage_id.hpp>
#include <sge/opengl/texture/optional_id.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/optional/map.hpp>


sge::opengl::texture::optional_id
sge::opengl::texture::get_stage_id(
	sge::opengl::context::object &_context,
	sge::renderer::texture::stage const _stage
)
{
	sge::opengl::texture::bind_context const &bind_context(
		sge::opengl::context::use<
			sge::opengl::texture::bind_context
		>(
			_context
		)
	);

	return
		fcppt::optional::map(
			bind_context.stage(
				_stage
			),
			[](
				fcppt::reference<
					sge::opengl::texture::base const
				> const _texture
			)
			{
				return
					_texture.get().id();
			}
		);
}
