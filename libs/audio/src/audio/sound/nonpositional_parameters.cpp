//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/audio/scalar.hpp>
#include <sge/audio/sound/nonpositional_parameters.hpp>
#include <fcppt/literal.hpp>


sge::audio::sound::nonpositional_parameters::nonpositional_parameters()
:
	gain_(
		fcppt::literal<
			sge::audio::scalar
		>(
			1
		)
	),
	pitch_(
		fcppt::literal<
			sge::audio::scalar
		>(
			1
		)
	)
{
}

sge::audio::scalar
sge::audio::sound::nonpositional_parameters::pitch() const
{
	return
		pitch_;
}

sge::audio::sound::nonpositional_parameters &
sge::audio::sound::nonpositional_parameters::pitch(
	sge::audio::scalar const _pitch
)
{
	pitch_ =
		_pitch;

	return
		*this;
}

sge::audio::scalar
sge::audio::sound::nonpositional_parameters::gain() const
{
	return
		gain_;
}

sge::audio::sound::nonpositional_parameters &
sge::audio::sound::nonpositional_parameters::gain(
	sge::audio::scalar const _gain
)
{
	gain_ =
		_gain;

	return
		*this;
}
