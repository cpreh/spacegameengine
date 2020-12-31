//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/state/ffp/lighting/light/direction.hpp>
#include <sge/renderer/state/ffp/lighting/light/directional.hpp>


sge::renderer::state::ffp::lighting::light::directional::directional(
	sge::renderer::state::ffp::lighting::light::direction const _direction
)
:
	direction_(
		_direction
	)
{
}

sge::renderer::state::ffp::lighting::light::direction const &
sge::renderer::state::ffp::lighting::light::directional::direction() const
{
	return
		direction_;
}
