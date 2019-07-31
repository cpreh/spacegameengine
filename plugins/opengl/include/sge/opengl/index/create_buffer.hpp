//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_INDEX_CREATE_BUFFER_HPP_INCLUDED
#define SGE_OPENGL_INDEX_CREATE_BUFFER_HPP_INCLUDED

#include <sge/opengl/context/object_fwd.hpp>
#include <sge/renderer/index/buffer_parameters_fwd.hpp>
#include <sge/renderer/index/buffer_unique_ptr.hpp>


namespace sge
{
namespace opengl
{
namespace index
{

sge::renderer::index::buffer_unique_ptr
create_buffer(
	sge::opengl::context::object &,
	sge::renderer::index::buffer_parameters const &
);

}
}
}

#endif
