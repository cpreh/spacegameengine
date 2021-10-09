//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_IMPL_FORMAT_MAP_HPP_INCLUDED
#define SGE_IMAGE_IMPL_FORMAT_MAP_HPP_INCLUDED

#include <fcppt/mpl/map/object.hpp>

namespace sge::image::impl
{

template <typename... Args>
using format_map = fcppt::mpl::map::object<Args...>;

}

#endif
