//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_VIEWPORT_MAINTAIN_ASPECT_HPP_INCLUDED
#define SGE_VIEWPORT_MAINTAIN_ASPECT_HPP_INCLUDED

#include <sge/viewport/fractional_aspect_fwd.hpp>
#include <sge/viewport/resize_callback.hpp>
#include <sge/viewport/detail/symbol.hpp>

namespace sge::viewport
{

SGE_VIEWPORT_DETAIL_SYMBOL
sge::viewport::resize_callback maintain_aspect(sge::viewport::fractional_aspect const &);

}

#endif
