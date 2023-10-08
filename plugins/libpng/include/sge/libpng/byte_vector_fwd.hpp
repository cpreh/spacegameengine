//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_LIBPNG_BYTE_VECTOR_FWD_HPP_INCLUDED
#define SGE_LIBPNG_BYTE_VECTOR_FWD_HPP_INCLUDED

#include <fcppt/container/raw_vector/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <pngconf.h>
#include <fcppt/config/external_end.hpp>

namespace sge::libpng
{

using byte_vector = fcppt::container::raw_vector::object<png_byte>;

}

#endif
