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


#ifndef SGE_AUDIO_FILE_HPP_INCLUDED
#define SGE_AUDIO_FILE_HPP_INCLUDED

// C
#include <cstddef>

// C++
#include <vector>
#include <memory>

namespace sge
{
class audio_file
{
	public:
	virtual std::size_t read(std::size_t sample_count,std::vector<unsigned char> &) = 0;
	virtual std::size_t read_all(std::vector<unsigned char> &) = 0;
	virtual int channels() const = 0;
	virtual int sample_rate() const = 0;
	virtual int bits_per_sample() const = 0;
	virtual void reset() = 0;
	virtual ~audio_file() {}
};
}

#endif // AUDIO_FILE_HPP
