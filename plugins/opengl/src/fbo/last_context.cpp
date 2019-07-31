//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/fbo/id.hpp>
#include <sge/opengl/fbo/last_context.hpp>
#include <sge/opengl/fbo/no_buffer.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


sge::opengl::fbo::last_context::last_context()
:
	sge::opengl::context::base(),
	last_buffer_(
		sge::opengl::fbo::no_buffer()
	)
{
}

sge::opengl::fbo::last_context::~last_context()
{
}

sge::opengl::fbo::id
sge::opengl::fbo::last_context::last_buffer() const
{
	return
		last_buffer_;
}

void
sge::opengl::fbo::last_context::last_buffer(
	sge::opengl::fbo::id const _last_buffer
)
{
	last_buffer_ =
		_last_buffer;
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)

sge::opengl::context::id const
sge::opengl::fbo::last_context::static_id(
	sge::opengl::context::make_id()
);

FCPPT_PP_POP_WARNING
