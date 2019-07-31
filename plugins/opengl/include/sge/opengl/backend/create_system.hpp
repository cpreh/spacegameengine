//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_BACKEND_CREATE_SYSTEM_HPP_INCLUDED
#define SGE_OPENGL_BACKEND_CREATE_SYSTEM_HPP_INCLUDED

#include <sge/opengl/backend/system_unique_ptr.hpp>
#include <awl/system/object_fwd.hpp>
#include <fcppt/log/object_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace backend
{

sge::opengl::backend::system_unique_ptr
create_system(
	fcppt::log::object &,
	awl::system::object &
);

}
}
}

#endif
