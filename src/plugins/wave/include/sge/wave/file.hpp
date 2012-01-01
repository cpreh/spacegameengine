/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/audio/optional_path.hpp>
#include <sge/wave/stream_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/io/cifstream.hpp>
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
	public audio::file
{
FCPPT_NONCOPYABLE(
	file);
public:
	explicit
	file(
		stream_ptr,
		audio::optional_path const &);

	audio::sample_count
	bits_per_sample() const;

	audio::sample_count
	sample_rate() const;

	audio::channel_type
	channels() const;

	audio::sample_count
	samples() const;

	audio::sample_count
	expected_package_size() const;

	void
	reset();

	audio::sample_count
	read(
		audio::sample_count,
		audio::sample_container &);

	audio::sample_count
	read_all(
		audio::sample_container &);
private:
	sge::audio::optional_path filename_;
	boost::logic::tribool swap_;
	stream_ptr file_;
	std::streampos data_segment;
	audio::sample_count
		samples_,
		samples_read_;
	audio::channel_type channels_;
	audio::sample_count sample_rate_;
	audio::sample_count bits_per_sample_;

	// Interne Funktionen
	void read_riff();
	void read_wave();
	void ignore_chunks_until(std::string const &);

	std::string const extract_header(fcppt::string const &_desc);

	template<typename T>
	T extract_primitive(fcppt::string const &_desc);
};

}
}

#endif
