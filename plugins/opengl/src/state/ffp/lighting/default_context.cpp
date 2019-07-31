//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/state/ffp/lighting/default_context.hpp>
#include <sge/opengl/state/ffp/lighting/make_actors.hpp>
#include <sge/opengl/state/ffp/lighting/object.hpp>
#include <sge/renderer/state/ffp/lighting/default.hpp>
#include <sge/renderer/state/ffp/lighting/parameters.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


sge::opengl::state::ffp::lighting::default_context::default_context()
:
	sge::opengl::context::base(),
	default_state_(
		fcppt::make_unique_ptr<
			sge::opengl::state::ffp::lighting::object
		>(
			sge::opengl::state::ffp::lighting::make_actors(
				sge::renderer::state::ffp::lighting::default_()
			)
		)
	)
{
}

sge::opengl::state::ffp::lighting::default_context::~default_context()
{
}

sge::opengl::state::ffp::lighting::object const &
sge::opengl::state::ffp::lighting::default_context::default_state() const
{
	return
		*default_state_;
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)

sge::opengl::context::id const
sge::opengl::state::ffp::lighting::default_context::static_id(
	sge::opengl::context::make_id()
);

FCPPT_PP_POP_WARNING
