//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_GUI_IMPL_STYLE_OUTER_BORDER_HPP_INCLUDED
#define SGE_GUI_IMPL_STYLE_OUTER_BORDER_HPP_INCLUDED

#include <sge/rucksack/scalar.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::gui::impl::style
{

using outer_border = std::integral_constant<sge::rucksack::scalar, 4>;

}

#endif
