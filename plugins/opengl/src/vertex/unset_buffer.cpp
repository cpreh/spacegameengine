//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/vertex/buffer.hpp>
#include <sge/opengl/vertex/context.hpp>
#include <sge/opengl/vertex/declaration.hpp>
#include <sge/opengl/vertex/unset_buffer.hpp>
#include <sge/renderer/vertex/buffer.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/cast/static_downcast.hpp>


void
sge::opengl::vertex::unset_buffer(
	sge::opengl::context::object &_context,
	sge::renderer::vertex::buffer const &_buffer
)
{
	sge::opengl::vertex::context &context(
		sge::opengl::context::use<
			sge::opengl::vertex::context
		>(
			_context
		)
	);

	sge::renderer::vf::dynamic::part_index const index(
		_buffer.format_part_index()
	);

	fcppt::cast::static_downcast<
		sge::opengl::vertex::buffer const &
	>(
		_buffer
	).unuse(
		FCPPT_ASSERT_OPTIONAL_ERROR(
			context.vertex_declaration()
		).get().gl_format_part(
			index
		)
	);

	context.vertex_buffer(
		index,
		sge::opengl::vertex::context::optional_buffer()
	);
}
