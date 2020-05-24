//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/state/ffp/lighting/light/attenuation.hpp>
#include <sge/renderer/state/ffp/lighting/light/point.hpp>
#include <sge/renderer/state/ffp/lighting/light/position.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::renderer::state::ffp::lighting::light::point::point(
	sge::renderer::state::ffp::lighting::light::position _position,
	sge::renderer::state::ffp::lighting::light::attenuation const &_attenuation
)
:
	position_(
		std::move(
			_position
		)
	),
	attenuation_(
		_attenuation
	)
{
}

sge::renderer::state::ffp::lighting::light::position const &
sge::renderer::state::ffp::lighting::light::point::position() const
{
	return
		position_;
}

sge::renderer::state::ffp::lighting::light::attenuation const &
sge::renderer::state::ffp::lighting::light::point::attenuation() const
{
	return
		attenuation_;
}
