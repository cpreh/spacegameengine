//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
