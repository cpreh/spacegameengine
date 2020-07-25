//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/scenic/render_context/light/directional.hpp>
#include <sge/scenic/render_context/light/direction.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::scenic::render_context::light::directional::directional(
	sge::scenic::render_context::light::direction _direction
)
:
	direction_(
		std::move(
			_direction
		)
	)
{
}

sge::scenic::render_context::light::direction const &
sge::scenic::render_context::light::directional::direction() const
{
	return
		direction_;
}
