//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_DETAIL_PROCESS_IS_SAME_GEOMETRY_OPTIONS_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_PROCESS_IS_SAME_GEOMETRY_OPTIONS_HPP_INCLUDED

#include <sge/sprite/process/geometry_options_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::sprite::detail::process
{

template <
    sge::sprite::process::geometry_options Options1,
    sge::sprite::process::geometry_options Options2>
using is_same_geometry_options = std::integral_constant<bool, Options1 == Options2>;

}

#endif
