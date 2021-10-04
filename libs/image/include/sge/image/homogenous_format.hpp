//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_HOMOGENOUS_FORMAT_HPP_INCLUDED
#define SGE_IMAGE_HOMOGENOUS_FORMAT_HPP_INCLUDED

#include <mizuiro/color/format/homogenous_static.hpp>


namespace sge::image
{

template<
	typename Channel,
	typename Layout
>
using
homogenous_format
=
mizuiro::color::format::homogenous_static<
	Channel,
	Layout
>;

}

#endif
