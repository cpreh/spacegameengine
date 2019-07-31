//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/state/ffp/sampler/context.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


sge::opengl::state::ffp::sampler::context::context()
:
	sge::opengl::context::base(),
	stages_(
		0u
	)
{
}

sge::opengl::state::ffp::sampler::context::~context()
{
}

sge::renderer::texture::stage
sge::opengl::state::ffp::sampler::context::stages() const
{
	return
		stages_;
}

void
sge::opengl::state::ffp::sampler::context::stages(
	sge::renderer::texture::stage const _stages
)
{
	stages_ =
		_stages;
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)

sge::opengl::context::id const
sge::opengl::state::ffp::sampler::context::static_id(
	sge::opengl::context::make_id()
);

FCPPT_PP_POP_WARNING
