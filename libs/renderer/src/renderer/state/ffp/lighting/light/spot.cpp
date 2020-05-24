//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/state/ffp/lighting/light/attenuation.hpp>
#include <sge/renderer/state/ffp/lighting/light/cutoff_angle.hpp>
#include <sge/renderer/state/ffp/lighting/light/direction.hpp>
#include <sge/renderer/state/ffp/lighting/light/position.hpp>
#include <sge/renderer/state/ffp/lighting/light/spot.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::renderer::state::ffp::lighting::light::spot::spot(
	sge::renderer::state::ffp::lighting::light::position _position,
	sge::renderer::state::ffp::lighting::light::direction _direction,
	sge::renderer::state::ffp::lighting::light::cutoff_angle const _cutoff_angle,
	sge::renderer::state::ffp::lighting::light::attenuation const &_attenuation
)
:
	position_(
		std::move(
			_position
		)
	),
	direction_(
		std::move(
			_direction
		)
	),
	cutoff_angle_(
		_cutoff_angle
	),
	attenuation_(
		_attenuation
	)
{
}

sge::renderer::state::ffp::lighting::light::position const &
sge::renderer::state::ffp::lighting::light::spot::position() const
{
	return
		position_;
}

sge::renderer::state::ffp::lighting::light::direction const &
sge::renderer::state::ffp::lighting::light::spot::direction() const
{
	return
		direction_;
}

sge::renderer::state::ffp::lighting::light::cutoff_angle
sge::renderer::state::ffp::lighting::light::spot::cutoff_angle() const
{
	return
		cutoff_angle_;
}

sge::renderer::state::ffp::lighting::light::attenuation const &
sge::renderer::state::ffp::lighting::light::spot::attenuation() const
{
	return
		attenuation_;
}
