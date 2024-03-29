//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_LIBPNG_MAKE_ROW_VECTOR_HPP_INCLUDED
#define SGE_LIBPNG_MAKE_ROW_VECTOR_HPP_INCLUDED

#include <sge/image2d/dim_fwd.hpp>
#include <sge/libpng/bytes_per_pixel.hpp>
#include <sge/libpng/row_vector.hpp>
#include <fcppt/config/external_begin.hpp>
#include <pngconf.h>
#include <fcppt/config/external_end.hpp>

namespace sge::libpng
{

sge::libpng::row_vector
make_row_vector(sge::image2d::dim const &, png_bytep, sge::libpng::bytes_per_pixel);

}

#endif
