//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_LIBPNG_BYTES_PER_PIXEL_HPP_INCLUDED
#define SGE_LIBPNG_BYTES_PER_PIXEL_HPP_INCLUDED

#include <sge/image/size_type.hpp>
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/strong_typedef_impl.hpp> // IWYU pragma: keep

namespace sge::libpng
{

FCPPT_DECLARE_STRONG_TYPEDEF(sge::image::size_type, bytes_per_pixel);

}

#endif
