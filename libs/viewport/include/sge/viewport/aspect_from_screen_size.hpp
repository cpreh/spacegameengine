//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_VIEWPORT_ASPECT_FROM_SCREEN_SIZE_HPP_INCLUDED
#define SGE_VIEWPORT_ASPECT_FROM_SCREEN_SIZE_HPP_INCLUDED

#include <sge/renderer/screen_size_fwd.hpp>
#include <sge/viewport/fractional_aspect.hpp>
#include <sge/viewport/detail/symbol.hpp>

namespace sge::viewport
{

SGE_VIEWPORT_DETAIL_SYMBOL
sge::viewport::fractional_aspect aspect_from_screen_size(sge::renderer::screen_size const &);

}

#endif
