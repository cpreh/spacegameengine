/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include <sge/path.hpp>
#include <sge/audio/file.hpp>
#include <sge/audio/exception.hpp>
#include <boost/logic/tribool.hpp>
#include <fstream>
#include <string>
#include <cstddef>

namespace sge
{
namespace wave
{

class file : public audio::file 
{
	const path                 filename_;
	// Ob die Bytes geswappt werden muessen
	boost::logic::tribool      swap_;
	std::ifstream              file_;
	audio::sample_count        samples_,
	                           samples_read_;
	audio::sample_container    buffer_;

	// Ob das Ding geladen wurde
	bool                       loaded_;

	// "Pflichtfelder"
	audio::channel_type        channels_;
	audio::sample_count        sample_rate_;
	audio::sample_count        bits_per_sample_;

	// Interne Funktionen
	void load();
	void read_riff();
	void read_wave();
	void read_data();

	const std::string extract_string(std::size_t _bytes, const std::string &_desc);
	
	template<typename T>
	T extract_primitive(const std::string &_desc);
	
public:
	file(const path &);

	const std::string to_string() const;

	audio::sample_count bits_per_sample() const;
	audio::sample_count sample_rate() const;
	audio::channel_type channels() const;
	audio::sample_count samples() const;
	void reset();

	audio::sample_count read(audio::sample_count,audio::sample_container &);
	audio::sample_count read_all(audio::sample_container &);
};

}
}

#endif
