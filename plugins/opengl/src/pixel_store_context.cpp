//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/pixel_store_context.hpp>
#include <sge/opengl/unpack_alignment.hpp>
#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


sge::opengl::pixel_store_context::pixel_store_context()
:
	sge::opengl::context::base(),
	unpack_alignment_(
		4
	)
{
}

sge::opengl::pixel_store_context::~pixel_store_context()
= default;

void
sge::opengl::pixel_store_context::unpack_alignment(
	sge::opengl::unpack_alignment const _unpack_alignment
)
{
	unpack_alignment_ =
		_unpack_alignment;
}

sge::opengl::unpack_alignment
sge::opengl::pixel_store_context::unpack_alignment() const
{
	return
		unpack_alignment_;
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)

sge::opengl::context::id const
sge::opengl::pixel_store_context::static_id(
	sge::opengl::context::make_id()
);

FCPPT_PP_POP_WARNING
