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


#ifndef SGE_AUDIO_FILE_HPP_INCLUDED
#define SGE_AUDIO_FILE_HPP_INCLUDED

#include <sge/audio/bits_per_sample.hpp>
#include <sge/audio/channel_count.hpp>
#include <sge/audio/file_fwd.hpp>
#include <sge/audio/sample_container_fwd.hpp>
#include <sge/audio/sample_count.hpp>
#include <sge/audio/sample_rate.hpp>
#include <sge/audio/detail/symbol.hpp>
#include <sge/core/detail/class_symbol.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/preprocessor/warn_unused_result.hpp>


namespace sge
{
namespace audio
{

/**
\brief Interface class for loaded audio files

For a short introduction to file loading, see \ref audio_example.
*/
class SGE_CORE_DETAIL_CLASS_SYMBOL file
{
	FCPPT_NONCOPYABLE(
		file
	);
protected:
	SGE_AUDIO_DETAIL_SYMBOL
	file();
public:
	/**
	\brief Read \a _samples samples from the file, storing them in \a _destination.

	\param _samples Number of samples to read

	\param _destination The container to store the samples in. Samples will be \em appended to the container.

	\return The number of samples actually read. This might differ from \a _samples because EOF was reached (or for some other reason)
	*/
	virtual
	sge::audio::sample_count
	read(
		sge::audio::sample_count _samples,
		sge::audio::sample_container &_destination
	)
	FCPPT_PP_WARN_UNUSED_RESULT
	= 0;

	/**
	\brief Read ALL the samples from the file, storing them in \a _destination.

	\param _destination The container to store the samples in. Samples will be \em appended to the container.

	\return The number of samples read.
	*/
	virtual
	sge::audio::sample_count
	read_all(
		sge::audio::sample_container &_destination
	)
	FCPPT_PP_WARN_UNUSED_RESULT
	= 0;

	/**
	\brief How many samples will sge::audio::file::read probably return?

	The sge::audio::file::read function doesn't, in general, return as many
	samples as the user requests from it. That's because the file might be
	decoded in chunks, rather than single samples. This function returns an
	approximation of the chunk size (if any) of the file.

	You probably won't call this function directly. It is, however,
	important for streaming sounds, as it is a great help for caching.
	*/
	virtual
	sge::audio::sample_count
	expected_package_size() const = 0;

	/// How many channels does this file hold
	virtual
	sge::audio::channel_count
	channels() const = 0;

	/// What's the sample rate (in number of samples) of the file
	virtual
	sge::audio::sample_rate
	sample_rate() const = 0;

	/// How many bits per sample are there
	virtual
	sge::audio::bits_per_sample
	bits_per_sample() const = 0;

	/// Seek to the beginning of the file so you can read it again (for looping streaming sounds)
	virtual
	void
	reset() = 0;

	SGE_AUDIO_DETAIL_SYMBOL
	virtual
	~file() = 0;
};

}
}

#endif
