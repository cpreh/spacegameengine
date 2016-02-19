/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


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
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace openal
{

class source
:
	public sge::audio::sound::positional
{
	FCPPT_NONCOPYABLE(
		source
	);
public:
	source(
		sge::audio::sound::nonpositional_parameters const &,
		sge::openal::buffer_id
	);

	source(
		sge::audio::sound::positional_parameters const &,
		sge::openal::buffer_id
	);

	explicit
	source(
		sge::audio::sound::nonpositional_parameters const &
	);

	explicit
	source(
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

	sge::openal::source_id
	source_id() const;

	sge::audio::sound::repeat
	repeat() const;
private:
	source();

	explicit
	source(
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
}

#endif
