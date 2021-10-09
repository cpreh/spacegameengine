//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_PROCESS_DEFAULT_OPTIONS_HPP_INCLUDED
#define SGE_SPRITE_PROCESS_DEFAULT_OPTIONS_HPP_INCLUDED

#include <sge/sprite/process/default_geometry_options.hpp>
#include <sge/sprite/process/options.hpp>

namespace sge::sprite::process
{

template <typename Choices, typename Compare>
using default_options = sge::sprite::process::options<
    sge::sprite::process::default_geometry_options<Choices, Compare>::value>;

}

#endif
