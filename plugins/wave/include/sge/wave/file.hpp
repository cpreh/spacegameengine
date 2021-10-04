//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_WAVE_FILE_HPP_INCLUDED
#define SGE_WAVE_FILE_HPP_INCLUDED

#include <sge/audio/bits_per_sample.hpp>
#include <sge/audio/channel_count.hpp>
#include <sge/audio/file.hpp>
#include <sge/audio/sample_buffer_fwd.hpp>
#include <sge/audio/sample_container_fwd.hpp>
#include <sge/audio/sample_count.hpp>
#include <sge/audio/sample_rate.hpp>
#include <sge/media/optional_name.hpp>
#include <sge/media/stream_unique_ptr.hpp>
#include <sge/wave/info.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/reference_fwd.hpp>
#include <fcppt/log/object_reference.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ios>
#include <fcppt/config/external_end.hpp>


namespace sge::wave
{

class file
:
	public sge::audio::file
{
	FCPPT_NONMOVABLE(
		file
	);
public:
	file(
		fcppt::log::object_reference,
		sge::media::stream_unique_ptr &&,
		sge::wave::info const &,
		sge::media::optional_name &&
	);

	~file()
	override;

	[[nodiscard]]
	sge::audio::bits_per_sample
	bits_per_sample() const
	override;

	[[nodiscard]]
	sge::audio::sample_rate
	sample_rate() const
	override;

	[[nodiscard]]
	sge::audio::channel_count
	channels() const
	override;

	[[nodiscard]]
	sge::audio::sample_count
	expected_package_size() const
	override;

	void
	reset()
	override;

	[[nodiscard]]
	sge::audio::sample_count
	read(
		sge::audio::sample_count,
		fcppt::reference<
			sge::audio::sample_buffer
		>
	)
	override;

	[[nodiscard]]
	sge::audio::sample_container
	read_all()
	override;
private:
	fcppt::log::object_reference const log_;

	sge::media::optional_name const name_;

	sge::wave::info const info_;

	sge::media::stream_unique_ptr const file_;

	std::streampos data_segment_;

	sge::audio::sample_count samples_read_;
};

}

#endif
