//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_DISPLAY_MODE_COMPARISON_HPP_INCLUDED
#define SGE_RENDERER_DISPLAY_MODE_COMPARISON_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/display_mode/object_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace display_mode
{

/**
\brief Compares every member of a display mode using ==

Compares \a mode1 to \a mode2 using == on every member.

\return Whether \a mode1 and \a mode2 are equal
*/
SGE_RENDERER_DETAIL_SYMBOL
bool
operator==(
	sge::renderer::display_mode::object const &mode1,
	sge::renderer::display_mode::object const &mode2
);

/**
\brief Compares every member of a display mode using !=

Compares \a mode1 to \a mode2 using != on every member.

\return Whether \a mode1 and \a mode2 are equal
*/
SGE_RENDERER_DETAIL_SYMBOL
bool
operator!=(
	sge::renderer::display_mode::object const &mode1,
	sge::renderer::display_mode::object const &mode2
);

}
}
}

#endif
