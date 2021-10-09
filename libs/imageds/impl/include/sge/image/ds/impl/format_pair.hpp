//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_DS_IMPL_FORMAT_PAIR_HPP_INCLUDED
#define SGE_IMAGE_DS_IMPL_FORMAT_PAIR_HPP_INCLUDED

#include <sge/image/ds/format.hpp>
#include <sge/image/impl/format_pair.hpp>

namespace sge::image::ds::impl
{

template <sge::image::ds::format Dynamic, typename Static>
using format_pair = sge::image::impl::format_pair<sge::image::ds::format, Dynamic, Static>;

}

#endif
