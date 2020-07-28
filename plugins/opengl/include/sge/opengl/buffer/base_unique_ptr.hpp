//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_BUFFER_BASE_UNIQUE_PTR_HPP_INCLUDED
#define SGE_OPENGL_BUFFER_BASE_UNIQUE_PTR_HPP_INCLUDED

#include <sge/opengl/buffer/base_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sge
{
namespace opengl
{
namespace buffer
{

using
base_unique_ptr
=
fcppt::unique_ptr<
	sge::opengl::buffer::base
>;

}
}
}

#endif
