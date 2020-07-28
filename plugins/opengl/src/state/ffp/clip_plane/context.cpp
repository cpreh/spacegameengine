//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/state/ffp/clip_plane/context.hpp>
#include <sge/renderer/state/index_count.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


sge::opengl::state::ffp::clip_plane::context::context()
:
	sge::opengl::context::base(),
	indices_(
		0U
	)
{
}

sge::opengl::state::ffp::clip_plane::context::~context()
= default;

sge::renderer::state::index_count
sge::opengl::state::ffp::clip_plane::context::indices() const
{
	return
		indices_;
}

void
sge::opengl::state::ffp::clip_plane::context::indices(
	sge::renderer::state::index_count const _indices
)
{
	indices_ =
		_indices;
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)

sge::opengl::context::id const
sge::opengl::state::ffp::clip_plane::context::static_id(
	sge::opengl::context::make_id()
);

FCPPT_PP_POP_WARNING
