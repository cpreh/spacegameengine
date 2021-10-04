//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_HETEROGENOUS_FORMAT_HPP_INCLUDED
#define SGE_IMAGE_HETEROGENOUS_FORMAT_HPP_INCLUDED

#include <mizuiro/color/format/heterogenous_static.hpp>


namespace sge::image
{

template<
	typename Sizes,
	typename Layout
>
using
heterogenous_format
=
mizuiro::color::format::heterogenous_static<
	Sizes,
	Layout
>;

}

#endif
