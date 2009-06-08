/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include <sge/filesystem/path.hpp>
#include <sge/string.hpp>
#include <sge/audio/file.hpp>
#include <boost/logic/tribool.hpp>
#include <boost/filesystem/fstream.hpp>
#include <string>

namespace sge
{
namespace wave
{

class file : public audio::file 
{
public:
	explicit file(
		filesystem::path const &);

	sge::string const to_string() const;

	audio::sample_count bits_per_sample() const { return bits_per_sample_; }
	audio::sample_count sample_rate() const { return sample_rate_; }
	audio::channel_type channels() const { return channels_; }
	audio::sample_count samples() const { return samples_; }
	void reset();

	audio::sample_count read(audio::sample_count,audio::sample_container &);
	audio::sample_count read_all(audio::sample_container &);
private:
	string const                filename_;
	boost::logic::tribool       swap_;
	boost::filesystem::ifstream file_;
	std::streampos              data_segment;
	audio::sample_count         samples_,
	                            samples_read_;
	audio::channel_type         channels_;
	audio::sample_count         sample_rate_;
	audio::sample_count         bits_per_sample_;

	// Interne Funktionen
	void read_riff();
	void read_wave();
	void ignore_chunks_until(std::string const &);

	std::string const extract_header(string const &_desc);
	
	template<typename T>
	T extract_primitive(string const &_desc);
};

}
}

#endif
