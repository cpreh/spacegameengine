//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_VERTEX_CREATE_DECLARATION_HPP_INCLUDED
#define SGE_OPENGL_VERTEX_CREATE_DECLARATION_HPP_INCLUDED

#include <sge/opengl/context/object_ref.hpp>
#include <sge/renderer/vertex/declaration_parameters_fwd.hpp>
#include <sge/renderer/vertex/declaration_unique_ptr.hpp>
#include <fcppt/log/object_reference.hpp>


namespace sge
{
namespace opengl
{
namespace vertex
{

sge::renderer::vertex::declaration_unique_ptr
create_declaration(
	fcppt::log::object_reference,
	sge::opengl::context::object_ref,
	sge::renderer::vertex::declaration_parameters const &
);

}
}
}

#endif
