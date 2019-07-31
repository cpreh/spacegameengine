//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_BUFFER_OPTIONAL_ID_FWD_HPP_INCLUDED
#define SGE_OPENGL_BUFFER_OPTIONAL_ID_FWD_HPP_INCLUDED

#include <sge/opengl/buffer/id.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace buffer
{

typedef
fcppt::optional::object<
	sge::opengl::buffer::id
>
optional_id;

}
}
}

#endif
