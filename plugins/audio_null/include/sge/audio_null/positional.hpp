//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_AUDIO_NULL_POSITIONAL_HPP_INCLUDED
#define SGE_AUDIO_NULL_POSITIONAL_HPP_INCLUDED

#include <sge/audio/scalar.hpp>
#include <sge/audio/vector_fwd.hpp>
#include <sge/audio/sound/optional_direction_fwd.hpp>
#include <sge/audio/sound/play_status_fwd.hpp>
#include <sge/audio/sound/positional.hpp>
#include <sge/audio/sound/repeat_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace audio_null
{

class positional
:
	public sge::audio::sound::positional
{
	FCPPT_NONCOPYABLE(
		positional
	);
public:
	positional();

	~positional()
	override;
private:
	void
	play(
		sge::audio::sound::repeat
	)
	override;

	void
	toggle_pause()
	override;

	sge::audio::sound::play_status
	status() const
	override;

	void
	stop()
	override;

	void
	update()
	override;

	void
	position(
		sge::audio::vector const &
	)
	override;

	void
	linear_velocity(
		sge::audio::vector const &
	)
	override;

	void
	gain(
		sge::audio::scalar
	)
	override;

	void
	pitch(
		sge::audio::scalar
	)
	override;

	void
	rolloff_factor(
		sge::audio::scalar
	)
	override;

	void
	reference_distance(
		sge::audio::scalar
	)
	override;

	void
	max_distance(
		sge::audio::scalar
	)
	override;

	void
	direction(
		sge::audio::sound::optional_direction const &
	)
	override;

	void
	inner_cone_angle(
		sge::audio::scalar
	)
	override;

	void
	outer_cone_angle(
		sge::audio::scalar
	)
	override;

	void
	outer_cone_gain(
		sge::audio::scalar
	)
	override;
};

}
}

#endif
