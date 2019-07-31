//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/vertex/buffer.hpp>
#include <sge/opengl/vertex/create_buffer.hpp>
#include <sge/opengl/vertex/declaration.hpp>
#include <sge/renderer/vertex/buffer.hpp>
#include <sge/renderer/vertex/buffer_parameters.hpp>
#include <sge/renderer/vertex/buffer_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/cast/static_downcast.hpp>


sge::renderer::vertex::buffer_unique_ptr
sge::opengl::vertex::create_buffer(
	sge::opengl::context::object &_context,
	sge::renderer::vertex::buffer_parameters const &_parameters
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::renderer::vertex::buffer
		>(
			fcppt::make_unique_ptr<
				sge::opengl::vertex::buffer
			>(
				_context,
				_parameters.part(),
				fcppt::cast::static_downcast<
					sge::opengl::vertex::declaration const &
				>(
					_parameters.declaration()
				).format_part(
					_parameters.part()
				),
				_parameters.count(),
				_parameters.flags()
			)
		);
}
