//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/index/buffer.hpp>
#include <sge/opengl/index/create_buffer.hpp>
#include <sge/renderer/index/buffer.hpp>
#include <sge/renderer/index/buffer_parameters_fwd.hpp>
#include <sge/renderer/index/buffer_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


sge::renderer::index::buffer_unique_ptr
sge::opengl::index::create_buffer(
	sge::opengl::context::object_ref const _context,
	sge::renderer::index::buffer_parameters const &_parameters
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::renderer::index::buffer
		>(
			fcppt::make_unique_ptr<
				sge::opengl::index::buffer
			>(
				_context,
				_parameters
			)
		);
}
