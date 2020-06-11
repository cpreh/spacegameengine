//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_VIEWPORT_CENTER_ON_RESIZE_HPP_INCLUDED
#define SGE_VIEWPORT_CENTER_ON_RESIZE_HPP_INCLUDED

#include <sge/viewport/resize_callback.hpp>
#include <sge/viewport/detail/symbol.hpp>
#include <sge/window/dim_fwd.hpp>


namespace sge
{
namespace viewport
{

SGE_VIEWPORT_DETAIL_SYMBOL
sge::viewport::resize_callback
center_on_resize(
	sge::window::dim const &
);

}
}

#endif
