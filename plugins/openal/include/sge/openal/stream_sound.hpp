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


#ifndef SGE_OPENAL_STREAM_SOUND_HPP_INCLUDED
#define SGE_OPENAL_STREAM_SOUND_HPP_INCLUDED

#include <sge/audio/file_fwd.hpp>
#include <sge/audio/sample_count.hpp>
#include <sge/audio/sound/nonpositional_parameters_fwd.hpp>
#include <sge/audio/sound/positional_parameters_fwd.hpp>
#include <sge/openal/al.hpp>
#include <sge/openal/buffer_id.hpp>
#include <sge/openal/multi_buffer_holder.hpp>
#include <sge/openal/source.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/log/object_fwd.hpp>


namespace sge
{
namespace openal
{

class stream_sound
:
	public sge::openal::source
{
	FCPPT_NONCOPYABLE(
		stream_sound
	);
public:
	stream_sound(
		fcppt::log::object &,
		sge::audio::sound::nonpositional_parameters const &,
		sge::audio::file &
	);

	stream_sound(
		fcppt::log::object &,
		sge::audio::sound::positional_parameters const &,
		sge::audio::file &
	);

	~stream_sound()
	override;

	void
	update()
	override;

	void
	do_play()
	override;
private:
	fcppt::log::object &log_;

	sge::audio::file &audio_file_;

	sge::audio::sample_count const buffer_samples_;

	ALenum const format_;

	sge::openal::multi_buffer_holder buffers_;

	bool
	fill_buffer(
		sge::openal::buffer_id
	);

	struct unified_ctor
	{
	};

	template<
		typename Parameters
	>
	stream_sound(
		fcppt::log::object &,
		Parameters const &,
		sge::audio::file &,
		sge::openal::stream_sound::unified_ctor
	);
};

}
}

#endif
