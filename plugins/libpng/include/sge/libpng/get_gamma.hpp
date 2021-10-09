//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_LIBPNG_GET_GAMMA_HPP_INCLUDED
#define SGE_LIBPNG_GET_GAMMA_HPP_INCLUDED

#include <sge/libpng/gamma.hpp>
#include <sge/libpng/info_fwd.hpp>
#include <sge/libpng/read_ptr_fwd.hpp>

namespace sge::libpng
{

sge::libpng::gamma get_gamma(sge::libpng::read_ptr const &, sge::libpng::info const &);

}

#endif
