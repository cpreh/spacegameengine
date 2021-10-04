//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_LIBPNG_FROM_SGE_FORMAT_HPP_INCLUDED
#define SGE_LIBPNG_FROM_SGE_FORMAT_HPP_INCLUDED

#include <sge/image/color/format_fwd.hpp>
#include <sge/libpng/optional_format.hpp>


namespace sge::libpng
{

sge::libpng::optional_format
from_sge_format(
	sge::image::color::format
);

}

#endif
