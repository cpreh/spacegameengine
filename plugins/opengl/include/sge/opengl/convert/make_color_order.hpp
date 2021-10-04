//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_CONVERT_MAKE_COLOR_ORDER_HPP_INCLUDED
#define SGE_OPENGL_CONVERT_MAKE_COLOR_ORDER_HPP_INCLUDED

#include <sge/opengl/color_order.hpp>
#include <fcppt/cast/to_unsigned.hpp>


namespace sge::opengl::convert
{

template<
	int Format
>
sge::opengl::color_order
make_color_order()
{
	return
		sge::opengl::color_order{
			fcppt::cast::to_unsigned(
				Format
			)
		};
}

}

#endif
