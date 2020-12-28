//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/common.hpp>
#include <sge/opengl/buffer/base.hpp>
#include <sge/opengl/buffer/context.hpp>
#include <sge/opengl/buffer/make_hardware.hpp>
#include <sge/opengl/buffer/make_software.hpp>
#include <sge/opengl/buffer/vbo_context.hpp>
#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/context/object.hpp>
#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/context/use.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/array/get.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wold-style-cast)

sge::opengl::buffer::vbo_context::vbo_context(
	sge::opengl::context::object_ref const _context
)
:
	sge::opengl::context::base(),
	buffers_(
		fcppt::optional::maybe( // NOLINT(clang-analyzer-cplusplus.NewDeleteLeaks)
			sge::opengl::context::use<
				sge::opengl::buffer::context
			>(
				_context,
				_context.get().info()
			).hardware_config(),
			[]{
				return
					sge::opengl::buffer::make_software<
						buffer_array
					>();
			},
			[](
				sge::opengl::buffer::hardware_config const &_config
			)
			{
				return
					_config.is_native().get() // NOLINT(clang-analyzer-cplusplus.NewDeleteLeaks)
					? // NOLINT(bugprone-branch-clone)
						sge::opengl::buffer::make_hardware(
							fcppt::make_cref(
								_config
							),
							GL_ELEMENT_ARRAY_BUFFER,
							GL_ARRAY_BUFFER
						)
					:
						sge::opengl::buffer::make_hardware(
							fcppt::make_cref(
								_config
							),
							GL_ELEMENT_ARRAY_BUFFER_ARB,
							GL_ARRAY_BUFFER_ARB
						)
					;
			}
		)
	)
{
}

FCPPT_PP_POP_WARNING

sge::opengl::buffer::vbo_context::~vbo_context()
= default;

sge::opengl::buffer::base &
sge::opengl::buffer::vbo_context::index_buffer() const
{
	return
		*fcppt::array::get<
			0
		>(
			buffers_
		);
}

sge::opengl::buffer::base &
sge::opengl::buffer::vbo_context::vertex_buffer() const
{
	return
		*fcppt::array::get<
			1
		>(
			buffers_
		);
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)

sge::opengl::context::id const
sge::opengl::buffer::vbo_context::static_id(
	sge::opengl::context::make_id()
);

FCPPT_PP_POP_WARNING
