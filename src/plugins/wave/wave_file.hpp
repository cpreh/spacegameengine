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
#include <sge/audio/loader/audio_file.hpp>
#include <sge/audio/audio_exception.hpp>
#include <boost/logic/tribool.hpp>
#include <fstream>
#include <string>
#include <cstddef>

namespace sge
{
class wave_file : public audio_file 
{
	const path                 filename_;
	// Ob die Bytes geswappt werden muessen
	boost::logic::tribool      swap_;
	std::ifstream              file_;
	sample_type                samples_,
	                           samples_read_;
	raw_array_type             buffer_;

	// Ob das Ding geladen wurde
	bool                       loaded_;

	// "Pflichtfelder"
	channel_type               channels_;
	sample_type                sample_rate_;
	sample_type                bits_per_sample_;

	// Interne Funktionen
	void load();
	void read_riff();
	void read_wave();
	void read_data();

	std::string extract_string(std::size_t _bytes, const std::string &_desc);
	
	template<typename T>
	T extract_primitive(const std::string &_desc);
	
	public:
	wave_file(const path &);

	std::string to_string() const;

	sample_type bits_per_sample() const;
	sample_type sample_rate() const;
	channel_type channels() const;
	sample_type samples() const;
	void reset();

	sample_type read(sample_type, raw_array_type &);
	sample_type read_all(raw_array_type &);
};
}

#endif // WAVE_FILE_HPP
