//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/state/ffp/lighting/light/attenuation.hpp>
#include <sge/renderer/state/ffp/lighting/light/constant_attenuation.hpp>
#include <sge/renderer/state/ffp/lighting/light/linear_attenuation.hpp>
#include <sge/renderer/state/ffp/lighting/light/quadratic_attenuation.hpp>


sge::renderer::state::ffp::lighting::light::attenuation::attenuation(
	sge::renderer::state::ffp::lighting::light::constant_attenuation const _constant,
	sge::renderer::state::ffp::lighting::light::linear_attenuation const _linear,
	sge::renderer::state::ffp::lighting::light::quadratic_attenuation const _quadratic
)
:
	constant_(
		_constant
	),
	linear_(
		_linear
	),
	quadratic_(
		_quadratic
	)
{
}

sge::renderer::state::ffp::lighting::light::constant_attenuation
sge::renderer::state::ffp::lighting::light::attenuation::constant() const
{
	return
		constant_;
}

sge::renderer::state::ffp::lighting::light::linear_attenuation
sge::renderer::state::ffp::lighting::light::attenuation::linear() const
{
	return
		linear_;
}

sge::renderer::state::ffp::lighting::light::quadratic_attenuation
sge::renderer::state::ffp::lighting::light::attenuation::quadratic() const
{
	return
		quadratic_;
}
