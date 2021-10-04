//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENAL_SOURCE_HPP_INCLUDED
#define SGE_OPENAL_SOURCE_HPP_INCLUDED

#include <sge/audio/scalar.hpp>
#include <sge/audio/vector_fwd.hpp>
#include <sge/audio/sound/nonpositional_parameters_fwd.hpp>
#include <sge/audio/sound/optional_direction_fwd.hpp>
#include <sge/audio/sound/play_status_fwd.hpp>
#include <sge/audio/sound/positional.hpp>
#include <sge/audio/sound/positional_parameters_fwd.hpp>
#include <sge/audio/sound/repeat.hpp>
#include <sge/openal/buffer_id.hpp>
#include <sge/openal/source_holder.hpp>
#include <sge/openal/source_id.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/log/object_reference.hpp>


namespace sge::openal
{

class source
:
	public sge::audio::sound::positional
{
	FCPPT_NONMOVABLE(
		source
	);
public:
	source(
		fcppt::log::object_reference,
		sge::audio::sound::nonpositional_parameters const &,
		sge::openal::buffer_id
	);

	source(
		fcppt::log::object_reference,
		sge::audio::sound::positional_parameters const &,
		sge::openal::buffer_id
	);

	source(
		fcppt::log::object_reference,
		sge::audio::sound::nonpositional_parameters const &
	);

	source(
		fcppt::log::object_reference,
		sge::audio::sound::positional_parameters const &
	);

	~source()
	override;

	void
	play(
		sge::audio::sound::repeat
	)
	override;

	void
	toggle_pause()
	override;

	[[nodiscard]]
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
protected:
	virtual
	void
	do_play();

	[[nodiscard]]
	sge::openal::source_id
	source_id() const;

	[[nodiscard]]
	sge::audio::sound::repeat
	repeat() const;
private:
	explicit
	source(
		fcppt::log::object_reference
	);

	source(
		fcppt::log::object_reference,
		sge::openal::buffer_id
	);

	sge::openal::source_holder const source_;

	sge::audio::sound::repeat repeat_;

	void
	init(
		sge::audio::sound::positional_parameters const &
	);

	void
	init(
		sge::audio::sound::nonpositional_parameters const &
	);
};

}

#endif
