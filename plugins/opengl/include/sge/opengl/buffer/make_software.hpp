//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_BUFFER_MAKE_SOFTWARE_HPP_INCLUDED
#define SGE_OPENGL_BUFFER_MAKE_SOFTWARE_HPP_INCLUDED

#include <sge/opengl/buffer/base.hpp>
#include <sge/opengl/buffer/software.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/container/array/init_move.hpp>


namespace sge
{
namespace opengl
{
namespace buffer
{

template<
	typename Array
>
Array
make_software()
{
	return
		fcppt::container::array::init_move<
			Array
		>(
			[]{
				return
					fcppt::unique_ptr_to_base<
						sge::opengl::buffer::base
					>(
						fcppt::make_unique_ptr<
							sge::opengl::buffer::software
						>()
					);
			}
		);
}

}
}
}

#endif
