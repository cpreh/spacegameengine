//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_COLOR_IS_CONVERTIBLE_V_HPP_INCLUDED
#define SGE_IMAGE_COLOR_IS_CONVERTIBLE_V_HPP_INCLUDED

#include <sge/image/color/is_convertible.hpp>

namespace sge::image::color
{

template <typename SourceFormat, typename DestFormat>
// NOLINTNEXTLINE(modernize-type-traits)
inline constexpr bool is_convertible_v = sge::image::color::is_convertible<SourceFormat, DestFormat>::value;

}

#endif
