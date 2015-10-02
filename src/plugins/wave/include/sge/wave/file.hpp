/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_WAVE_FILE_HPP_INCLUDED
#define SGE_WAVE_FILE_HPP_INCLUDED

#include <sge/audio/file.hpp>
#include <sge/media/optional_name.hpp>
#include <sge/media/stream_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/logic/tribool.hpp>
#include <streambuf>
#include <string>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace wave
{

class file
:
	public sge::audio::file
{
	FCPPT_NONCOPYABLE(
		file
	);
public:
	file(
		sge::media::stream_unique_ptr &&,
		sge::media::optional_name const &
	);

	sge::audio::sample_count
	bits_per_sample() const
	override;

	sge::audio::sample_count
	sample_rate() const
	override;

	sge::audio::channel_type
	channels() const
	override;

	sge::audio::sample_count
	expected_package_size() const
	override;

	void
	reset()
	override;

	sge::audio::sample_count
	read(
		sge::audio::sample_count,
		sge::audio::sample_container &
	)
	override;

	sge::audio::sample_count
	read_all(
		sge::audio::sample_container &
	)
	override;
private:
	sge::media::optional_name const filename_;

	boost::logic::tribool swap_;

	sge::media::stream_unique_ptr const file_;

	std::streampos data_segment_;

	sge::audio::sample_count
		samples_,
		samples_read_;

	sge::audio::channel_type channels_;

	sge::audio::sample_count sample_rate_;

	sge::audio::sample_count bits_per_sample_;

	void
	read_riff();

	void
	read_wave();

	void
	ignore_chunks_until(
		std::string const &
	);

	std::string
	extract_header(
		fcppt::string const &
	);

	template<
		typename T
	>
	T
	extract_primitive(
		fcppt::string const &
	);
};

}
}

#endif
