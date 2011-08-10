/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include <sge/audio/file_fwd.hpp>
#include <sge/audio/channel_type.hpp>
#include <sge/audio/sample_container.hpp>
#include <sge/audio/sample_count.hpp>
#include <sge/audio/symbol.hpp>
#include <sge/class_symbol.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace audio
{

class SGE_CLASS_SYMBOL file
{
	FCPPT_NONCOPYABLE(
		file
	);
protected:
	SGE_AUDIO_SYMBOL explicit
	file();
public:
	virtual sample_count
	read(
		sample_count samples,
		sample_container &) = 0;

	virtual sample_count
	read_all(
		sample_container &) = 0;

	virtual sample_count
	expected_package_size() const = 0;

	virtual channel_type
	channels() const = 0;

	virtual sample_count
	sample_rate() const = 0;

	virtual sample_count
	bits_per_sample() const = 0;

	virtual void
	reset() = 0;

	SGE_AUDIO_SYMBOL
	sample_count
	bytes_per_sample() const;

	SGE_AUDIO_SYMBOL
	virtual ~file();
};

}
}

#endif // AUDIO_FILE_HPP
