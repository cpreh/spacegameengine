//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/scenic/render_context/light/directional.hpp>

sge::scenic::render_context::light::directional::directional(
	sge::scenic::render_context::light::direction const &_direction)
:
	direction_(
		_direction)
{
}

sge::scenic::render_context::light::direction const &
sge::scenic::render_context::light::directional::direction() const
{
	return
		direction_;
}
