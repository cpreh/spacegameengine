//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/context/core.hpp>
#include <sge/renderer/texture/base_fwd.hpp>
#include <sge/renderer/texture/const_optional_base_ref.hpp>
#include <sge/renderer/texture/scoped.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/make_cref.hpp>


sge::renderer::texture::scoped::scoped(
	sge::renderer::context::core &_context,
	sge::renderer::texture::base const &_texture,
	sge::renderer::texture::stage const _stage
)
:
	context_(
		_context
	),
	stage_(
		_stage
	)
{
	context_.texture(
		sge::renderer::texture::const_optional_base_ref(
			fcppt::make_cref(
				_texture
			)
		),
		stage_
	);
}

sge::renderer::texture::scoped::~scoped()
{
	context_.texture(
		sge::renderer::texture::const_optional_base_ref(),
		stage_
	);
}
